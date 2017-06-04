#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <WorkstationBox.h>
#include "qextserial.h"

class Widget : public QWidget
{
    Q_OBJECT

    QextSerial *m_SerialPort;
    WorkstationBox m_Workstation[8];
    bool initUI();
public:
    explicit Widget(QWidget *parent = 0);
    
signals:
    
public slots:
    void getCallingfrom(char id, char number);
    void getBackfrom(char id ,char number);
    void updataToOthers();
    
};

#endif // WIDGET_H
