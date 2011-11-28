#include <QtGui/QApplication>
#include <QTextCodec>
#include <QPlastiqueStyle>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
