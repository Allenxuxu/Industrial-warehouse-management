#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include "qextserial.h"

class Workstation : public QDialog
{
    Q_OBJECT

    char station_number;
    QLabel label;
    QextSerial* m_SerialPort;
    QPushButton ledBtn;
    QPushButton stateBtn;
    QPushButton btn[9];
    QGridLayout glayout;
    QHBoxLayout hlayout;
    Workstation(char number,QDialog *parent = 0);
    bool initUI();
    bool Construct();
public:
    static Workstation* NewWorkstation(char number);
    void upDataToUI();

    ~Workstation();
private slots:
    void upDataToDb(QList<QByteArray> array);
    void onGetBack(char num);
    void DONE();
    void Calling();
    void dataErr();


};

#endif // WORKSTATION_H
