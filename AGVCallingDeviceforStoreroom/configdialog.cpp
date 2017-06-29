#include "ConfigDialog.h"
#include <QGridLayout>
#include <QVBoxLayout>
ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent)
{
    initUI();
    m_id = 0;
    for(int i = 0;i<8;i++)
    {
        connect(&m_pushBtn[i],SIGNAL(clicked()),this,SLOT(onBtnClicked()));
    }

    connect(&m_CloseBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(&m_OKBtn,SIGNAL(clicked()),this,SLOT(onOkBtnClicked()));
}

int ConfigDialog::getID()
{
    return m_id;
}

void ConfigDialog::onBtnClicked()
{
    m_OKBtn.setEnabled(true);
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    m_textEdit.setText(btn->text());
}

void ConfigDialog::onOkBtnClicked()
{
    m_id = m_textEdit.text().toInt();
    done(1);
}

void ConfigDialog::initUI()
{
   setWindowFlags(Qt::FramelessWindowHint);
   setWindowTitle(tr("请选择工位置号："));
   m_OKBtn.setEnabled(false);
   m_textEdit.setReadOnly(true);
   QGridLayout* glayout = new QGridLayout();
   QVBoxLayout* vlayout = new QVBoxLayout(this);
   for(int i=0;i<8;i++)
   {
       m_pushBtn[i].setText(QString::number(i+1));
       glayout->addWidget(&m_pushBtn[i],i/4,i%4);
   }
   m_CloseBtn.setText(tr("取消"));
   m_OKBtn.setText(tr("确认"));
   glayout->addWidget(&m_CloseBtn,2,0);
   glayout->addWidget(&m_OKBtn,2,3);

   vlayout->addWidget(&m_textEdit);
   vlayout->addSpacing(20);
   vlayout->addLayout(glayout);

}
