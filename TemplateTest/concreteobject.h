#ifndef CONCRETEOBJECT_H
#define CONCRETEOBJECT_H


#include "baseobject.h"
#include "Registor.hpp"
#include <QDebug>
class ConcreteObject : public BaseObject
{
    Q_OBJECT
public:
    explicit ConcreteObject(QObject *parent = nullptr);
    void debug()override;
signals:

};
REGISTER_OBJECT(ConcreteObject,BaseObject)
#endif // CONCRETEOBJECT_H
