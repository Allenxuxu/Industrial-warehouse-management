#include "qextserial.h"
#include <QByteArray>
#include <QDebug>
#include <QStringList>
QextSerial::QextSerial(const QString &portname,char stationNumber,QObject *parent) :
    QObject(parent)
{

    m_station_number = stationNumber;
    m_portname = portname;
    PackMessage();
}

bool QextSerial::Construct()
{
    bool ret = true;
    m_port = new QextSerialPort(m_portname,QextSerialPort::EventDriven);
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
        /*    if(!(m_port->lineStatus() & LS_DSR))
            {
                qDebug()<< "warning: device is not turned on";
            }
            */
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

QextSerial *QextSerial::NewQextSerial(const QString &portname, char stationNumber)
{
    QextSerial* ret = new QextSerial(portname,stationNumber);

    if(!(ret && ret->Construct()))
    {
       delete ret;
       ret = NULL;
    }
    return ret;
}

QextSerial::~QextSerial()
{ 

    if(m_port != NULL)
    {
        m_port->close();
        delete m_port;
        m_port = NULL;

    }
    qDebug()<<"~QextSerial()";
}

void QextSerial::onSend(QByteArray messary)
{
    m_port->write(messary);
}

void QextSerial::onPutchar()
{

    const QByteArray message(1,m_station_number);
    m_port->write(message);
}

void QextSerial::onReadyRead()
{
        char lrc;
         QByteArray temp = m_port->readAll();
         if(!temp.isEmpty())
         {
            bytearray.append(temp);
            if(bytearray.contains('#'))
            {

                if(bytearray.data()[0] == 0x55)
                {
                    if(bytearray.data()[1] == 0x01)
                    {
                        switch (bytearray.data()[2])
                        {
                        case 'u':
                            bytearray.chop(1);
                            lrc = LRC(bytearray.mid(3).data(),bytearray.size()-4);
                            if(bytearray.right(1).data()[0] == lrc)
                            {
                                bytearray.chop(1);
                                qDebug()<< bytearray.mid(3).split(',');
                                emit upData(bytearray.mid(3).split(','));
                            }
                            else
                            {
                                emit dataerror();
                            }
                            break;
                        case 'g':
                            qDebug()<<"bytearrt number:"<< QString::number(bytearray.data()[3]);
                            emit getBack( bytearray.data()[3]);
                            break;
                        }
                    }
                    bytearray.clear();
                }
                else
                {
                    bytearray.clear();
                }
            }
         }

}

void QextSerial::onDsrChanged(bool status)
{
    qDebug()<<"onDsrChanged";
}

char QextSerial::LRC(const char* src, int len)
{
    char lrc = 0;
    for(int i = 0;i<len;i++)
    {
        lrc += src[i];
    }
    lrc = (~lrc)+1;
    return lrc;
}

void QextSerial::PackMessage()
{

}

int QextSerial::readn(char *buf, int count)
{
        int count_left = count;
        int nread = -1;
        char* read_buf = buf;
        while (count_left > 0)
        {
            if ((nread = m_port->read( read_buf, count_left))< 0)
            {
                    return -1;
            }
            else if (nread == 0)
            {
                return (count - count_left);
            }
                read_buf   += nread;
                count_left -= nread;
        }
        return count;
}

void QextSerial::Unpack()
{
    QString data(m_newData);
    QStringList slist = data.split(",");
    for(int i=0; i<slist.size(); i++)
    {
        qDebug()<<"slist";
       qDebug()<<QString(slist.at(i).data());
    }
}

