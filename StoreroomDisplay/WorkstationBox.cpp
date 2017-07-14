#include "WorkstationBox.h"
#include <QGridLayout>
#include "ModifyDataDialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
WorkstationBox::WorkstationBox(int id,QGroupBox *parent) :
    QGroupBox(parent)
{
     m_messageStatus =true;
     m_id = id;
     initUI();
     connect(&m_updateBtn,SIGNAL(clicked()),this,SLOT(updateDB()));
     connect(&m_updateToother,SIGNAL(clicked()),this,SLOT(sendNewInfo()));

     for(int i=0; i<9; i++)
     {
         connect(&m_materielBtn[i],SIGNAL(clicked()),this,SLOT(Reply()));
     }
}


void WorkstationBox::initUI()
{
    setFont(QFont("wqy-microhei", 25, QFont::Bold));

    setTitle(QString::number(m_id)+QString(" 号工位"));
    for(int i=0; i<9;i++)
    {

        m_materielBtn[i].setStyleSheet("QPushButton{border:0px;}");
        m_materielBtn[i].setIcon(QPixmap(":res/icon/green.png"));
        m_materielBtn[i].setIconSize(QSize(20,20));
        m_materielBtn[i].setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_materielEdit[i].setStyleSheet("border:2px solid gray;");
        m_materielEdit[i].setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
    QGridLayout* glayout = new QGridLayout();
    for(int i=0; i<9;i++)
    {
        glayout->addWidget(&m_materielBtn[i],i,0);
        glayout->addWidget(&m_materielEdit[i],i,1);
    }
    m_updateBtn.setText("修改");
    m_updateBtn.setStyleSheet("QPushButton{"
                              "border:3px solid black;"
                              "background-color:white;"
                              "border-radius:15px}");
    m_updateToother.setText("更新");
    m_updateToother.setStyleSheet("QPushButton{"
                              "border:3px solid black;"
                              "background-color:white;"
                              "border-radius:8px}");
    glayout->addWidget(&m_updateToother,7,3);
    glayout->addWidget(&m_updateBtn,8,3);
    glayout->setColumnStretch(0,1);
    glayout->setColumnStretch(1,8);
    glayout->setVerticalSpacing(15);
    setLayout(glayout);

    updateInterface();
}

void WorkstationBox::updateInterface()
{
    QSqlQuery query;
    query.exec("select * from  site"+QString::number(m_id));
    for(int i=0; i<9; i++)
    {
        query.seek(i);
        m_materielEdit[i].setText(query.value(1).toString());
    }
}

QByteArray WorkstationBox::packingMessages(char type, QByteArray data)
{
    QByteArray array;
    array.append('U');
    array.append(static_cast<char>(0));
    array.append(static_cast<char>(m_id));
    array.append(type);
    array.append(data);
    array.append(LRC(data.data(),data.size()));
    array.append('#');
    return array;
}

void WorkstationBox::sendNewInfo()
{
    QSqlQuery query;
    QByteArray array;

    query.exec("select * from  site"+QString::number(m_id));
    for(int i=0; i<9; i++)
    {
        query.seek(i);
        array.append(query.value(1).toString().toAscii());
        array.append(",");
    }
    array.chop(1);
    emit updateStationInfo(packingMessages(MessageType_updateInfo,array));
    m_updateToother.setStyleSheet("QPushButton{"
                              "border:3px solid black;"
                              "background-color:yellow;"
                              "border-radius:8px}");
}

void WorkstationBox::updateInfoErr()
{
    QMessageBox::critical(this,tr("信息同步失败"),tr("工位同步信息失败，请手动跟新!"));
    //sendNewInfo();//重发
}

void WorkstationBox::updateDB()
{
    ModifyDataDialog w(m_id);
    w.exec();
    updateInterface();
}

void WorkstationBox::btnToRed(char number)
{
    m_materielBtn[static_cast<int>(number)-1].setIcon(QPixmap(":res/icon/red.png"));
}

void WorkstationBox::btnToGreen(char number)
{
    m_materielBtn[static_cast<int>(number)-1].setIcon(QPixmap(":res/icon/green.png"));
}

void WorkstationBox::onrecvSucess(char number)
{
    QByteArray array;
    array.append(number);
    emit notifPerRecvSucess(packingMessages(MessageType_recvSucess,array));
}

void WorkstationBox::onPerGetinfo()
{
    m_updateToother.setStyleSheet("QPushButton{"
                              "border:3px solid black;"
                              "background-color:white;"
                              "border-radius:8px}");
    onupdateSucess();
}

void WorkstationBox::Reply()
{
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    for(int i=0; i<9; i++)
    {
        if(btn == &m_materielBtn[i])
        {

            QByteArray array;
            array.append(i+1);
            emit getRequest(packingMessages(MessageType_recvReply,array));
            break;
        }
    }
    btn->setIcon(QPixmap(":res/icon/Yellow.png"));
}

void WorkstationBox::onupdateSucess()
{
    if(m_messageStatus)
    {
        m_messageStatus = false;
        QMessageBox::information(this,tr("提示"),tr("更新成功!"));
        m_messageStatus = true;
    }
}
