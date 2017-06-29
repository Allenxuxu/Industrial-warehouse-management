#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QByteArray>
#include <QLabel>
#include "SerialPort.h"
#include <QList>
class Workstation : public QDialog
{
    Q_OBJECT
   enum
   {
       MessageType_dataErr = 'e',
       MessageType_calling = 'c',
       MessageType_recvReply = 'g'
   }MessageType;

   SerialPort* m_SerialPort;
   int  m_station_number;

   QPushButton m_quickBtn;
   QPushButton m_stateBtn;
   QPushButton m_btn[9];

    Workstation(int station_number,QDialog *parent = 0);
    void initUI();
    bool construct();
    QByteArray packingMessages(char type, char data=0);
    void updateDB(QList<QByteArray> array);
    void receReply(char i);
public:
    static Workstation* NewWorkstation(int station_number);
    ~Workstation();
signals:
    void sendMessage(QByteArray message);
    void checksumErr(QByteArray message);
public slots:
    void updateToBtn();
    void onBtnCalling();
    void ParseMessage(QByteArray& message);
};

#endif // WORKSTATION_H
