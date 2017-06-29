#ifndef MODIFYDATADIALOG_H
#define MODIFYDATADIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QTableView>
#include <QtSql/QSqlTableModel>

class ModifyDataDialog : public QDialog
{
    Q_OBJECT

    QPushButton m_okBtn;
    QPushButton m_cancleBen;
    QTableView *m_tableView;
    QSqlTableModel *m_model;
public:
    ModifyDataDialog(int id,QWidget *parent = 0);
    ~ModifyDataDialog();
signals:
    
public slots:
    void onOk_clicked();
    void onCancle_clicked();

};

#endif // MODIFYDATADIALOG_H
