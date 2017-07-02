#include "widget.h"
#include <QGridLayout>
#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initUI();

   m_SerialPort = SerialPort::NewQextSerial();
   if(!m_SerialPort)
   {
       qDebug()<< "fail open serial port";

   }
   connect(m_SerialPort,SIGNAL(RecePacket(QByteArray&)),this,SLOT(ParseMessage(QByteArray&)));

    for(int i=0; i<8; i++)
    {
        connect(m_Workstation[i],SIGNAL(updateStationInfo(QByteArray)),m_SerialPort,SLOT(sendData(QByteArray)));
        connect(m_Workstation[i],SIGNAL(getRequest(QByteArray)),m_SerialPort,SLOT(sendData(QByteArray)));
    }
    connect(this,SIGNAL(dataErr(char)),this,SLOT(sendDataErr(char)));
    connect(this,SIGNAL(calling(char,char)),this,SLOT(getcalling(char,char)));
}

Widget::~Widget()
{
    delete m_SerialPort;
    for(int i=0; i<8; i++)
        delete m_Workstation[i];
}

void Widget::sendDataErr(char id)
{
    m_Workstation[static_cast<int>(id)-1]->updateInfoErr();
}

void Widget::getcalling(char id, char number)
{
    m_Workstation[static_cast<int>(id-1)]->getCalling(number);
}

bool Widget::initUI()
{
    bool ret = true;
    for(int i=0; i<8; i++)
    {
        m_Workstation[i] = new WorkstationBox(i+1);
        if(m_Workstation[i] == NULL)
        {
            ret = false;
            return ret;
        }
    }
    QGridLayout* glayout = new QGridLayout();
    for(int i=0; i<8; i++)
    {
        glayout->addWidget(m_Workstation[i],i/4,i%4);
    }
    glayout->setSpacing(20);
    setLayout(glayout);
    setWindowFlags(Qt::FramelessWindowHint);
    resize(QApplication::desktop()->width(),QApplication::desktop()->height());
    return ret;
}

void Widget::ParseMessage(QByteArray &message)
{

    if(message.data()[1] != 0x00)
    {
        if(message.data()[2] == 0x00)
        {
            char lrc;
            switch (message.data()[3])
            {
            case 'g':

                break;
            case 'c':

                message.chop(1);
                lrc = LRC(message.mid(4).data(),message.size()-5);
                if(message.right(1).data()[0] == lrc)
                {
                    emit calling(message.data()[1],message.data()[4]);
                }
                break;
            case 'e':
                emit dataErr(message.data()[1]);
                break;
            }
        }
    }
}
