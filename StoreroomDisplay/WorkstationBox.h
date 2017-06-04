#ifndef WORKSTATIONBOX_H
#define WORKSTATIONBOX_H


#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>

class WorkstationBox : public QGroupBox
{
    Q_OBJECT
    int m_id;
    QLineEdit m_materielEdit[9];
    QPushButton m_materielBtn[9];
    QPushButton m_updateBtn;
    QPushButton m_updateToother;
    bool initUI();
    char LRC(const char* src, int len);
public:
    explicit WorkstationBox(QGroupBox *parent = 0);

    void ongetCalling(char number);
    void ongetReply(char number);


signals:
    void sendMessage(QByteArray message);
public slots:
    void packingMessages();
    void setId(int id);
    void onclicked();
    void updatData();
    void refreshInterface();

};

#endif // WORKSTATIONBOX_H
