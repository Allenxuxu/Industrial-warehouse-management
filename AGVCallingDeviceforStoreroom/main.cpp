#include <QtGui/QApplication>
#include "widget.h"
#include "ConnectSQL.h"
#include <QTextCodec>
#include <QFontDatabase>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QFontDatabase::addApplicationFont(":image/wqy-microhei.ttf");
    createConnection();
    Widget w;
    w.setFont(QFont("wqy-microhei",30,QFont::Normal));
    w.show();
    
    return a.exec();
}
