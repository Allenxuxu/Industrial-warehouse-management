#include "widget.h"
#include <QGridLayout>
#include "ConfigDialog.h"
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QtGui/QApplication>
#include <QDesktopWidget>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initUI();

    connect(&m_configBtn,SIGNAL(clicked()),this,SLOT(configStationNum()));
    connect(&m_openCallingBtn,SIGNAL(clicked()),this,SLOT(openCallingDev()));
}

Widget::~Widget()
{
    
}

void Widget::configStationNum()
{
    ConfigDialog ConfigDlg;
    if(1 == ConfigDlg.exec())
    {
        QFile file(QDir::currentPath()+ "/station_number.txt");
        if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
                QTextStream out(&file);
                out << ConfigDlg.getID();
                file.close();
        }
    }
}

void Widget::initUI()
{
   setWindowFlags(Qt::FramelessWindowHint);
   QGridLayout* gLayout = new QGridLayout(this);
   m_configBtn.setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
   m_configBtn.setIcon(QIcon(":image/Work_256px_1077397_easyicon.net.png"));
   m_configBtn.setIconSize(QSize(150,150));

   m_configBtn.setText(tr("配置工位号"));
   m_configBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

   m_openCallingBtn.setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
   m_openCallingBtn.setIcon(QIcon(":image/Processing_203px_1200028_easyicon.net.png"));
   m_openCallingBtn.setIconSize(QSize(150,150));

   m_openCallingBtn.setText(tr("打开呼叫器"));
   m_openCallingBtn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


   gLayout->addWidget(&m_configBtn,0,0);
   gLayout->addWidget(&m_openCallingBtn,0,1);

   resize(QApplication::desktop()->width(),QApplication::desktop()->height());
}

void Widget::openCallingDev()
{
    QFile file(QDir::currentPath()+ "/station_number.txt");
    if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QTextStream in(&file);
        while( !in.atEnd() )
        {
            m_station_number = in.readAll().toInt();
            m_workstation =  Workstation:: NewWorkstation(m_station_number);
            if(m_workstation!= NULL)
            {
                m_workstation->exec();
                delete m_workstation;
            }
        }
        file.close();
    }
}
