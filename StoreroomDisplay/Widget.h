#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include "SerialPort.h"
#include "WorkstationBox.h"

class Widget : public QWidget
{
    Q_OBJECT
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

    SerialPort *m_SerialPort;
    WorkstationBox* m_Workstation[8];

    bool initUI();

signals:
    void calling(char id,char number);
    void dataErr(char id);
public:
    Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void sendDataErr(char id);
    void getcalling(char id,char number);
    void ParseMessage(QByteArray &message);
};

#endif // WIDGET_H
