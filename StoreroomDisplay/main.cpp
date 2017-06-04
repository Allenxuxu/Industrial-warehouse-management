#include <QtGui/QApplication>
#include "Widget.h"
#include <QFontDatabase>
#include <QTextCodec>
#include "ConnectSQl.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //QFontDatabase::addApplicationFont(":res/icon/wqy-microhei.ttf");

    createConnection(); //打开数据库
    Widget w;
    w.setWindowFlags(Qt::WindowCloseButtonHint);
    w.setFont(QFont("wqy-microhei",10,QFont::Normal));
    w.setWindowTitle("我是人");
    w.show();
    
    return a.exec();
}
