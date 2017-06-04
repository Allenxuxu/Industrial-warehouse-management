#include "DataDialog.h"
#include <QMessageBox>
#include <QDebug>
#include "ConnectSQl.h"
DataDialog::DataDialog(int id,QWidget *parent)
    : QDialog(parent),m_okBtn("ok",this),m_cancleBen("cancel",this)
{
        model = new QSqlTableModel(this);

        model->setTable("site"+QString::number(id));
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        tableView = new QTableView(this);
        tableView->setMinimumSize(240,300);
        tableView->setModel(model);
        tableView->setColumnHidden(0, true);

        m_cancleBen.move(10,310);
        m_okBtn.move(160,310);

        connect(&m_okBtn,SIGNAL(clicked()),this,SLOT(onOk_clicked()));
}

DataDialog::~DataDialog()
{
    
}

void DataDialog::onOk_clicked()
{
    model->database().transaction();
        if (model->submitAll())
        {
           if(model->database().commit() == true)
           {
                close();
           }
        }
        else
        {
           model->database().rollback();
        }
}

void DataDialog::onCancle_clicked()
{
    model->revertAll();

}

void DataDialog::ondelte_progress()
{

}

void DataDialog::ondelte()
{

}
