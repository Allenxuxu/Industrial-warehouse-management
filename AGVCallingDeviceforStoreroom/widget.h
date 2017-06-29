#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QToolButton>
#include "Workstation.h"
class Widget : public QWidget
{
    Q_OBJECT
    char m_station_number;
    Workstation* m_workstation;
    QToolButton m_configBtn;
    QToolButton m_openCallingBtn;


    void initUI();
public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected slots:
    void configStationNum();
    void openCallingDev();
};

#endif // WIDGET_H
