#ifndef CONNECTSQL_H
#define CONNECTSQL_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("site.db");
    if (!db.open())
    {
       QMessageBox::critical(0, "Cannot open database","Unable to establisha database connection.", QMessageBox::Cancel);
       return false;
    }
    qDebug()<< "open database.";
    QSqlQuery query;
    for(int i=1; i<=8; i++)
    {
        QString tablename = "site"+QString::number(i);
        query.exec(QString("create table "+ tablename + " (id int primary key, name vchar)"));
        for(int x=1; x<=9; x++)
        query.exec(QString("insert into  "+ tablename + "  values ("+QString::number(x)+",NULL)"));
    }


    return true;
}

#endif // CONNECTSQL_H
