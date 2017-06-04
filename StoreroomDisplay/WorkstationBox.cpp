#include "WorkstationBox.h"
#include <QGridLayout>
#include <QPixmap>
#include <QIcon>
#include <QDebug>
#include <QTextCodec>
#include <QFontDatabase>
#include "DataDialog.h"
WorkstationBox::WorkstationBox(QGroupBox *parent) :
    QGroupBox(parent)
{
    initUI();
    connect(&m_updateBtn,SIGNAL(clicked()),this,SLOT(updatData()));
    connect(&m_updateToother,SIGNAL(clicked()),this,SLOT(packingMessages()));
    for(int i=0; i<9; i++)
    {
        connect(&m_materielBtn[i],SIGNAL(clicked()),this,SLOT(onclicked()));
    }
}

void WorkstationBox::setId(int id)
{
    m_id = id;
    refreshInterface();
}

void WorkstationBox::onclicked()
{
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    for(int i=0; i<9; i++)
    {
        if(btn == &m_materielBtn[i])
        {

            QByteArray array;
            array.append("U");
            array.append((char)0);
            array.append("g");
            char ii = static_cast<char>( i);
             qDebug()<< "pushbitn :"<< QString::number(ii);
            array.append(ii);
            array.append('2');
            array.append("#");
            emit sendMessage(array);
            break;
        }
    }
    btn->setIcon(QPixmap(":res/icon/green.png"));
}

void WorkstationBox::ongetCalling(char number)
{    
        qDebug()<< " WorkstationBox::ongetCalling()";
        m_materielBtn[(int)number].setIcon(QPixmap(":res/icon/red.png"));
}

void WorkstationBox::ongetReply(char number)
{
        qDebug()<< " WorkstationBox::ongetReply()";
        m_materielBtn[(int)number].setIcon(QPixmap(":res/icon/green.png"));
}

void WorkstationBox::updatData()
{
    DataDialog w(m_id);
    w.exec();
    refreshInterface();
}

void WorkstationBox::refreshInterface()
{
    QSqlQuery query;
    query.exec("select * from  site"+QString::number(m_id));
    for(int i=0; i<9; i++)
    {
        query.seek(i);
        m_materielEdit[i].setText(query.value(1).toString());
    }
    packingMessages();
}

void WorkstationBox::packingMessages()
{
    QSqlQuery query;
    QByteArray message;
    QByteArray array;

    message.append("U");
    message.append((char)0);
    message.append("u");
    query.exec("select * from  site"+QString::number(m_id));
    for(int i=0; i<9; i++)
    {
        query.seek(i);
        array.append(query.value(1).toString().toAscii());
        array.append(",");
    }
    array.chop(1);
    char lrc = LRC(array.data(),array.size());
    message.append(array);
    message.append(lrc);
    message.append("#");

    emit sendMessage(message);
}

bool WorkstationBox::initUI()
{
    bool ret = true;
    for(int i=0; i<9;i++)
    {

        m_materielBtn[i].setStyleSheet("QPushButton{border:0px;}");
        m_materielBtn[i].setIcon(QPixmap(":res/icon/green.png"));
        m_materielBtn[i].setIconSize(QSize(20,20));
        m_materielBtn[i].setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_materielEdit[i].setReadOnly(true);
    }
    QGridLayout* glayout = new QGridLayout();
    for(int i=0; i<9;i++)
    {
        glayout->addWidget(&m_materielBtn[i],i,0);
        glayout->addWidget(&m_materielEdit[i],i,1);
    }
    m_updateBtn.setText("Modify data");
    m_updateToother.setText("Update to Station");
    glayout->addWidget(&m_updateToother,7,3);
    glayout->addWidget(&m_updateBtn,8,3);
    glayout->setColumnStretch(0,1);
    glayout->setColumnStretch(1,8);
    glayout->setVerticalSpacing(20);
    setLayout(glayout);
    return ret;
}
char WorkstationBox::LRC(const char* src, int len)
{
    char lrc = 0;
    for(int i = 0;i<len;i++)
    {
        lrc += src[i];
    }
    lrc = (~lrc)+1;
    return lrc;
}
