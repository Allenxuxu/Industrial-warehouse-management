#ifndef DATADIALOG_H
#define DATADIALOG_H

#include <QtGui/QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QPushButton>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>


class DataDialog : public QDialog
{
    Q_OBJECT
    QPushButton m_okBtn;
    QPushButton m_cancleBen;
    QTableView *tableView;
    QSqlTableModel *model;

public:
    DataDialog(int id,QWidget *parent = 0);
    ~DataDialog();

public slots:
    void onOk_clicked();
    void onCancle_clicked();
    void ondelte_progress();
    void ondelte();
};

#endif // DATADIALOG_H
