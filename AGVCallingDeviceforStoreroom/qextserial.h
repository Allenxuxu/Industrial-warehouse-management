#ifndef QEXTSERIAL_H
#define QEXTSERIAL_H

#include <QObject>
#include <QString>
#include <QList>
#include <QByteArray>
#include "qextserialport.h"

class QextSerial : public QObject
{
    Q_OBJECT
    QByteArray bytearray;
    char m_station_number;
    char m_newData[1024];
    QString m_portname;
    quint8 m_message[6];
    QextSerialPort *m_port;
    char LRC(const char* src,int len);
    void PackMessage();

    QextSerial(const QString &portname,char stationNumber,QObject *parent = 0);
    bool Construct();
    int readn(char *buf, int count);
    void Unpack();
public:
    static QextSerial* NewQextSerial(const QString &portname,char stationNumber);
    ~QextSerial();
    void onSend(QByteArray messary);
    void onPutchar();
signals:
    void upData(QList<QByteArray> array);
    void getBack(char number);
    void dataerror();
private  slots:

    void onReadyRead();
    void onDsrChanged(bool status);
    
};

#endif // QEXTSERIAL_H
