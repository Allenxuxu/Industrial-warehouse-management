#include "workstation.h"
#include <QDebug>
#include <QString>
#include <QIcon>
#include <QPixmap>
#include <QBitmap>
#include <QDesktopWidget>
#include <QtGui/QApplication>
#include <QTextCodec>
#include <QSqlQuery>
Workstation::Workstation( char number,QDialog *parent) :
    QDialog(parent)
{  
    station_number = number;
    initUI();
    connect(&ledBtn,SIGNAL(clicked()),this,SLOT(DONE()));
    for(int i=0; i<9; i++)
    {
        connect(&btn[i],SIGNAL(clicked()),this,SLOT(Calling()));
    }

}

bool Workstation::initUI()
{
    bool ret = true;
    setWindowFlags(Qt::FramelessWindowHint);
    label.setText(tr("AGV呼叫器"));
    label.setFont(QFont("wqy-microhei", 30, QFont::Black));

    ledBtn.setStyleSheet("QPushButton{border:0px;}");
    ledBtn.setIcon(QPixmap("image/arrow_left.png"));
    ledBtn.setIconSize(QSize(25,25));
    ledBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    stateBtn.setEnabled(false);
    stateBtn.setStyleSheet("QPushButton{border:0px;}");
    stateBtn.setText(QString::number(station_number)+"号工位");
    stateBtn.setFont(QFont("wqy-microhei", 20, QFont::Bold));
    stateBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    for(int i=0; i<9; i++)
    {
        btn[i].setStyleSheet("background-color:green");
        glayout.addWidget(&btn[i],i/3,i%3,Qt::AlignJustify);
    }
    upDataToUI();

    hlayout.addWidget(&ledBtn,1,Qt::AlignLeft);
    hlayout.addWidget(&label,4,Qt::AlignJustify);
    hlayout.addWidget(&stateBtn,1,Qt::AlignRight);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addLayout(&hlayout);
    vlayout->addLayout(&glayout);
    vlayout->setStretchFactor(&hlayout,1);
    vlayout->setStretchFactor(&glayout,6);
    setLayout(vlayout);

    this->setAttribute(Qt::WA_ShowModal,true);
    //resize(QApplication::desktop()->width(),QApplication::desktop()->height());
    return ret;
}

bool Workstation::Construct()
{
    bool ret = true;
    m_SerialPort = QextSerial::NewQextSerial("/dev/ttyS2",station_number);
    if(!m_SerialPort)
    {
        qDebug()<< "fail open serial port";
        ret = false;
    }
    else
    {

        connect(m_SerialPort,SIGNAL(upData(QList<QByteArray>)),this,SLOT(upDataToDb(QList<QByteArray>)));
        connect(m_SerialPort,SIGNAL(getBack(char)),this,SLOT(onGetBack(char)));
        connect(m_SerialPort,SIGNAL(dataerror()),this,SLOT(dataErr()));
    }

    return ret;
}

Workstation::~Workstation()
{    
    delete m_SerialPort;
    qDebug()<< "~Workstation()";
}



void Workstation::onGetBack(char num)
{
    qDebug()<<"number" << QString::number(num);
    btn[(int)num].setStyleSheet("background-color:green");
}

void Workstation::DONE()
{
    done(11);
}

void Workstation::Calling()
{
    QPushButton* Sender = dynamic_cast<QPushButton*>(sender());
    for(int i=0; i<9; i++)
    {
        if(Sender == &btn[i])
        {
            QByteArray array;
            array.append("U");
            array.append(station_number);
            array.append("c");
            char ii = static_cast<char>( i);
            array.append(ii);
            array.append('2');
            array.append("#");
            m_SerialPort->onSend(array);
            btn[i].setStyleSheet("background-color:red");
            break;
        }
    }
}

void Workstation::dataErr()
{
    qDebug()<<"data error";
    QByteArray array;
    array.append("U");
    array.append(station_number);
    array.append("e");
    array.append("2");
    array.append('2');
    array.append("#");
    m_SerialPort->onSend(array);
}

Workstation *Workstation::NewWorkstation(char number)
{
    Workstation* ret = new Workstation(number);

    if(!(ret && ret->Construct()) )
    {
       delete ret;
       ret = NULL;
    }
    qDebug()<< ret;
    return ret;
}

void Workstation::upDataToUI()
{

    QSqlQuery query;
    query.exec("select * from  site");
    for(int i=0; i<9; i++)
    {
        query.seek(i);
        btn[i].setText(query.value(1).toString());
    }
}

void Workstation::upDataToDb(QList<QByteArray> array)
{
    QSqlQuery query;
    for(int i=0; i<9; i++)
    {
        qDebug()<< QString(array[i]);
        query.exec("update site set name=\" "+ QString(array[i]) + " \"where id=\" "+ QString::number(i+1)+ "\"");

    }
    sleep(1);
    upDataToUI();
}

