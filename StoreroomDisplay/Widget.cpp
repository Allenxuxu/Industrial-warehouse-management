#include "Widget.h"
#include <QGridLayout>
#include <QtGui/QApplication>
#include <QDesktopWidget>

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    initUI();

    m_SerialPort = QextSerial::NewQextSerial("/dev/ttyS1",0);
   if(!m_SerialPort)
   {
       qDebug()<< "fail open serial port";

   }
   else
   {
       connect(m_SerialPort,SIGNAL(getBack(char,char)),this,SLOT(getBackfrom(char,char)));
       connect(m_SerialPort,SIGNAL(getCalling(char,char)),this,SLOT(getCallingfrom(char,char)));

       for(int i=0; i<8; i++)
       {

           connect(&m_Workstation[i],SIGNAL(sendMessage(QByteArray)),m_SerialPort,SLOT(onSend(QByteArray)));
       }
   }
}

void Widget::getCallingfrom(char id, char number)
{
    qDebug()<< (int) id;
    qDebug()<< (int) number;
    if(id>0 && id<9 && number>=0 && number<=8)
    {
        m_Workstation[id-1].ongetCalling( number);
    }
}

bool Widget::initUI()
{
    int ret = true;
    QGridLayout* glayout = new QGridLayout(this);
    for(int i=0; i<8; i++)
    {
        glayout->addWidget(&m_Workstation[i],i/4,i%4);
        m_Workstation[i].setId(i+1);
    }
    glayout->setSpacing(20);
    setLayout(glayout);

    resize(QApplication::desktop()->width(),QApplication::desktop()->height());
    return ret;
}

void Widget::getBackfrom(char id, char number)
{
    m_Workstation[id-1].ongetReply(number);
}

void Widget::updataToOthers()
{
}
