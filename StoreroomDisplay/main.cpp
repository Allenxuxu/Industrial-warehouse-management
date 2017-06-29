#include <QtGui/QApplication>
#include "widget.h"
#include <QFontDatabase>
#include <QTextCodec>
#include <QFont>
#include "ConnectSQl.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QFontDatabase::addApplicationFont(":res/icon/wqy-microhei.ttf");
    createConnection();
    Widget w;
    w.setFont(QFont("wqy-microhei",10,QFont::Normal));
    w.show();
    
    return a.exec();
}
