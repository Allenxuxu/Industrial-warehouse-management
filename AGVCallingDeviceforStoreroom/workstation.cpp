#include "Workstation.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSqlQuery>
#include <QVariant>
#include <QByteArray>
#include "LRCcheck.h"
#include <QDebug>
#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QSizePolicy>
Workstation::Workstation(int station_number,QDialog *parent) :
    QDialog(parent)
{
    m_station_number = station_number;
    initUI();
    for(int i=0; i<9; i++)
    {
        connect(&m_btn[i],SIGNAL(clicked()),this,SLOT(onBtnCalling()));
    }
}

void Workstation::initUI()
{
    setWindowFlags(Qt::FramelessWindowHint);

    QGridLayout* glayout = new QGridLayout();
    QHBoxLayout* hlayout = new QHBoxLayout();



    m_stateBtn.setEnabled(false);
    m_stateBtn.setStyleSheet("QPushButton{border:3px solid black;border-radius:8px;color:red}");
    m_stateBtn.setText(QString::number(m_station_number)+"\n号");
    m_stateBtn.setFont(QFont("wqy-microhei", 40, QFont::Bold));

    m_stateBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    for(int i=0; i<9; i++)
    {
       m_btn[i].setStyleSheet("background-color:green;");
       m_btn[i].setFixedSize(130,80);
       glayout->addWidget(&m_btn[i],i/3,i%3,Qt::AlignAbsolute);
    }
    glayout->setHorizontalSpacing(10);
    glayout->setVerticalSpacing(10);
    hlayout->addLayout(glayout);
    hlayout->addWidget(&m_stateBtn);
    hlayout->setStretchFactor(hlayout,2);
    hlayout->setStretchFactor(glayout,5);
    setLayout(hlayout);

    this->setAttribute(Qt::WA_ShowModal,true);
    //resize(QApplication::desktop()->width(),QApplication::desktop()->height());
    updateToBtn();
}

bool Workstation::construct()
{
    bool ret = true;
    m_SerialPort = SerialPort::NewQextSerial();
    if(!m_SerialPort)
    {
        qDebug()<< "fail open serial port";
        ret = false;
    }
    else
    {
        connect(m_SerialPort,SIGNAL(RecePacket(QByteArray&)),this,SLOT(ParseMessage(QByteArray&)));
        connect(this,SIGNAL(sendMessage(QByteArray)),m_SerialPort,SLOT(sendData(QByteArray)));
    }

    return ret;
}

void Workstation::updateToBtn()
{
   QSqlQuery query;
   query.exec("select * from  site");
   for(int i=0; i<9; i++)
   {
       query.seek(i);
       m_btn[i].setText(query.value(1).toString());
       qDebug()<< query.value(1).toString();
   }
}

void Workstation::onBtnCalling()
{
    QPushButton* Sender = dynamic_cast<QPushButton*>(sender());
   for(int i=0; i<9; i++)
   {
       if(Sender == &m_btn[i])
       {
           emit sendMessage(packingMessages(MessageType_calling,static_cast<char>(i+1)));

           m_btn[i].setStyleSheet("background-color:red");
           break;
       }
   }
}

void Workstation::ParseMessage(QByteArray &message)
{

    if(message.data()[1] == 0x00)
    {
        if(message.data()[2] == static_cast<char>(m_station_number))
        {
            char lrc;
            switch (message.data()[3])
            {
            case 'u':
                message.chop(1);
                lrc = LRC(message.mid(4).data(),message.size()-5);
                if(message.right(1).data()[0] == lrc)
                {
                    message.chop(1);
                    qDebug()<< message.mid(4).split(',');
                    updateDB(message.mid(4).split(','));


                }
                else
                {
                    emit checksumErr(packingMessages(MessageType_dataErr));
                }
                break;
            case 'g':
                receReply(message.data()[4]);
                break;
            }
        }
    }
}


QByteArray Workstation::packingMessages(char type, char data)
{
    QByteArray array;
    array.append('U');
    array.append(static_cast<char>(m_station_number));
    array.append(static_cast<char>(0));
    array.append(type);
    array.append(data);
    array.append(LRC(&data,1));
    array.append("#");
    return array;
}

void Workstation::updateDB(QList<QByteArray> array)
{
   QSqlQuery query;
   for(int i=0; i<9; i++)
   {
       qDebug()<< QString(array[i]);
       qDebug()<< query.exec("update site set name=\" "+ QString(array[i]) + " \"where id=\" "+ QString::number(i+1)+ "\"");
   }

   updateToBtn();
}

void Workstation::receReply(char i)
{
    m_btn[static_cast<int>(i)-1].setStyleSheet("background-color:green");
}

Workstation *Workstation::NewWorkstation(int station_number)
{
    Workstation* ret = new Workstation(station_number);

    if(!(ret && ret->construct()) )
    {
       delete ret;
       ret = NULL;
    }
    qDebug()<< ret;
    return ret;
}

Workstation::~Workstation()
{
    delete m_SerialPort;
}


