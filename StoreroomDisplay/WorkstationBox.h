#ifndef WORKSTATIONBOX_H
#define WORKSTATIONBOX_H

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QByteArray>

class WorkstationBox : public QGroupBox
{
    Q_OBJECT
    enum
    {
        MessageType_dataErr = 'e',
        MessageType_calling = 'c',
        MessageType_recvReply = 'g',
        MessageType_updateInfo = 'u',
        MessageType_recvSucess = 's',
        MessageType_quitCall = 'q'
    }MessageType;
    char LRC(const char* src, int len)
    {
        char lrc = 0;
        for(int i = 0;i<len;i++)
        {
            lrc += src[i];
        }
        lrc = (~lrc)+1;
        return lrc;
    }

    char m_messageStatus;
    int m_id;
    QLabel m_materielEdit[9];
    QPushButton m_materielBtn[9];
    QPushButton m_updateBtn;
    QPushButton m_updateToother;
    void initUI();
    void updateInterface();
    QByteArray packingMessages(char type,QByteArray data);

public:
    WorkstationBox(int id,QGroupBox *parent = 0);
    void updateInfoErr();
    void btnToRed(char number);
    void btnToGreen(char number);
    void onrecvSucess(char number);
    void onPerGetinfo();
signals:
    void updateStationInfo(QByteArray array);
    void getRequest(QByteArray array);
    void notifPerRecvSucess(QByteArray array);
public slots:
    void Reply();

    void onupdateSucess();
    void updateDB();
    void sendNewInfo();
    
};

#endif // WORKSTATIONBOX_H
