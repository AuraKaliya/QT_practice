#include "componentobject.h"

#include <QJsonObject>
#include <QMetaProperty>
#include <QVariant>

ComponentObject::ComponentObject(QObject *parent)
    : QObject{parent}
{

}

void ComponentObject::tick()
{

}

//void ComponentObject::initProperty(QJsonObject jsonObj)
//{
//    QVector<QPair<QString,QVariant> > var;
//    const QMetaObject* p=metaObject();
//    bool flag=true;
//    int i=0;
//    while(flag)
//    {
//        QMetaProperty property =p->property(i++);
//        if(property.isValid())
//        {
//            var.append(QPair<QString,QVariant>(property.name(),QVariant(property.read(this))));

//        }
//    }

//}

//QJsonObject ComponentObject::getProperty()
//{

//}

void ComponentObject::bindToGameObject(GameObject *go)
{

}

bool ComponentObject::waitForSignal(QObject *obj, const char *signal, const unsigned int ms)
{

    bool result =true;
    QEventLoop loop;
    connect(obj,signal,&loop,SLOT(quit()));

    QTimer timer;
    timer.setSingleShot(true);

    connect(&timer,&QTimer::timeout,[&loop,&result]{
        result=false;
        qDebug()<<"ComponentObject::waitForSignal: TIMEOUT!";
        loop.quit();
    });
    timer.start(ms);

    loop.exec();
    timer.stop();

    return result;
}

int ComponentObject::waitForIntSignal(QObject *obj,  const char *signal, const unsigned int ms)
{
    m_result =0;
    connect(obj,signal,this,SLOT(solveIntSignal(int)));

    QTimer timer;
    timer.setSingleShot(true);

    connect(&timer,&QTimer::timeout,[this]{
        m_result=-1;
        qDebug()<<"ComponentObject::waitForSignal: TIMEOUT!";
        m_loop.quit();
    });
    timer.start(ms);

    m_loop.exec();
    timer.stop();

    return m_result;
}

void ComponentObject::solveIntSignal(int number)
{
    qDebug()<<"####ComponentObject::solveIntSignal: "<<number;
    if(m_loop.isRunning())
    {
        m_result=number;
        m_loop.quit();
    }
}
