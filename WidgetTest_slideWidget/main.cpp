#include "widget.h"

#include <QApplication>

#include "testwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Widget w;
    TestWidget w2;
    w2.show();
   // w.show();
    return a.exec();
}
