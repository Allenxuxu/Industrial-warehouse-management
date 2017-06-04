#ifndef QEXTSERIAL_H
#define QEXTSERIAL_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include "qextserialport.h"

class QextSerial : public QObject
{
    Q_OBJECT
    char m_station_number;
    QByteArray bytearray;
    QString m_portname;
    char m_message[1024];
    QextSerialPort *m_port;
    char LRC(const char* src,int len);
    void PackMessage();
    int readn(char* buf,int count);

    QextSerial(const QString &portname,char stationNumber,QObject *parent = 0);
    bool Construct();
public:
    static QextSerial* NewQextSerial(const QString &portname,char stationNumber);
    ~QextSerial();

    void onPutchar();
signals:
    void getBack(char id,char number);
    void getCalling(char id,char number);
    void perDataError();
private  slots:
    void onSend(QByteArray message);
    void onReadyRead();
    void onDsrChanged(bool status);
    void retransmission();
    
};

#endif // QEXTSERIAL_H
