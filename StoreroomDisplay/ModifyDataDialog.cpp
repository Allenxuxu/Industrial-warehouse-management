#include "ModifyDataDialog.h"
#include "ConnectSQl.h"

ModifyDataDialog::ModifyDataDialog(int id,QWidget *parent) :
    QDialog(parent),m_okBtn(tr("确定"),this), m_cancleBen(tr("取消"),this)
{
    setWindowTitle(QString("双击选中单元格修改"));
    setFixedSize(250,345);
    m_model = new QSqlTableModel(this);
    m_model->setTable("site"+QString::number(id));
    m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->select();
    m_tableView = new QTableView(this);
    m_tableView->setMinimumSize(250,300);
    m_tableView->setModel(m_model);
    m_tableView->setColumnHidden(0, true);

    m_cancleBen.move(10,310);
    m_okBtn.move(160,310);

    connect(&m_okBtn,SIGNAL(clicked()),this,SLOT(onOk_clicked()));
    connect(&m_cancleBen,SIGNAL(clicked()),this,SLOT(onCancle_clicked()));
}

ModifyDataDialog::~ModifyDataDialog()
{

}

void ModifyDataDialog::onOk_clicked()
{
    m_model->database().transaction();
    if (m_model->submitAll())
    {
       if(m_model->database().commit() == true)
       {
            close();
       }
    }
    else
    {
       m_model->database().rollback();
    }
}

void ModifyDataDialog::onCancle_clicked()
{
    m_model->revertAll();
    done(1);
}
