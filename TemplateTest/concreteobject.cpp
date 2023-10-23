#include "concreteobject.h"

ConcreteObject::ConcreteObject(QObject *parent)
    : BaseObject{parent}
{

}

void ConcreteObject::debug()
{
    qDebug()<<"2333333333333333333333333333";
    qDebug()<<"2333333333333333333333333333";
    qDebug()<<"2333333333333333333333333333";
    qDebug()<<"2333333333333333333333333333";
    qDebug()<<"2333333333333333333333333333";
}
