#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "qextserialport.h"
#include <QObject>
#include <QByteArray>
class SerialPort : public QObject
{
    Q_OBJECT
    QextSerialPort *m_port;
    QByteArray m_readBuffer;

    explicit SerialPort(QObject *parent = 0);
    bool construct();

public:
    static SerialPort* NewQextSerial();
    ~SerialPort();
signals:
    void RecePacket(QByteArray& message);
public slots:
    void onReadyRead();
    void onDsrChanged(bool status);
    void sendData(QByteArray array) const;
};

#endif // SERIALPORT_H
