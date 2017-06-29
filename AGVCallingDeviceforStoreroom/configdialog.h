#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>

#include <QDialog>

class ConfigDialog : public QDialog
{
    Q_OBJECT
    int m_id;
    QLineEdit m_textEdit;
    QPushButton m_pushBtn[8];
    QPushButton m_OKBtn;
    QPushButton m_CloseBtn;
    void initUI();
public:
    explicit ConfigDialog(QWidget *parent = 0);
    int getID();
public slots:
    void onBtnClicked();
    void onOkBtnClicked();
    
};

#endif // CONFIGDIALOG_H
