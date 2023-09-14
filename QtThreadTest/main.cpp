#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //qRegisterMetaType<QVector<int>>("QVector<int>");
    //当Qt不支持元数据对象时，用该函数进行注册。
    /*
      qRegisterMetaType是Qt中的一个函数，它可以用来注册自定义的数据类型，使得它们可以在Qt的元对象系统中使用
      ，例如在信号和槽的通讯机制中传递参数。
      qRegisterMetaType的作用是告诉Qt如何构造、析构、拷贝和比较这个类型的对象，以便在元对象系统中使用它们。
      元对象系统是Qt提供的一种反射机制，它可以在运行时获取对象的类名、属性、信号、槽等信息，并进行动态调用。
      元对象系统的核心类是QMetaObject，它描述了一个QObject类或者其子类的元信息。
      你可以通过Q_OBJECT宏来为你的类生成元对象信息，并通过metaObject()函数来访问它。
    */
    Widget w;
    w.show();
    return a.exec();
}
