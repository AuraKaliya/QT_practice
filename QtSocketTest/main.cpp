#include "mainwindow.h"

#include <QApplication>
#pragma execution_character_set("utf-8")
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    MainWindow w2;
    w2.show();
    return a.exec();
}
