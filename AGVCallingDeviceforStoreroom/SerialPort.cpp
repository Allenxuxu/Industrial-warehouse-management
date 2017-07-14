#include "SerialPort.h"
#include <QDebug>
SerialPort::SerialPort(QObject *parent) :
    QObject(parent)
{
}

bool SerialPort::construct()
{
    bool ret = true;
    m_port = new QextSerialPort("/dev/ttymxc7",QextSerialPort::EventDriven);
    if(m_port != NULL)
    {
        m_port->setBaudRate(BAUD9600);
        m_port->setDataBits(DATA_8);
        m_port->setStopBits(STOP_1);
        m_port->setParity(PAR_NONE);
        m_port->setFlowControl(FLOW_OFF);
        if(true == m_port->open(QIODevice::ReadWrite))
        {
            qDebug()<< "serial port  oK";
            connect(m_port,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
            connect(m_port,SIGNAL(dsrChanged(bool)),this,SLOT(onDsrChanged(bool)));
        }
        else
        {
            qDebug()<< "device failed to open:" << m_port->errorString();
            ret = false;
            delete m_port;
            m_port = NULL;
        }
    }
    else
    {
        ret = false;
    }
    return ret;
}

SerialPort *SerialPort::NewQextSerial()
{
    SerialPort* ret = new SerialPort();
    if(!(ret && ret->construct()))
    {
       delete ret;
       ret = NULL;
    }
    return ret;
}

SerialPort::~SerialPort()
{
    delete m_port;
}

void SerialPort::onReadyRead()
{
    QByteArray temp = m_port->readAll();
    if( !temp.isEmpty())
    {
        m_readBuffer.append(temp);
        if(m_readBuffer.endsWith('#'))
        {
            if(m_readBuffer.data()[0] == 'U')
            {
                emit RecePacket(m_readBuffer);
            }
            m_readBuffer.clear();
        }
    }
}

void SerialPort::onDsrChanged(bool status)
{
    qDebug() << "serial port status:" << status;
}

void SerialPort::sendData(QByteArray array) const
{
    m_port->write(array);
}


