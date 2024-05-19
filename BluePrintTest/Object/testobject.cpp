#include "testobject.h"

TestObject::TestObject(QObject *parent)
    : QObject{parent},m_objId(10086),m_value(50)
{
    m_signalMode=new ModelBlueprintSignal(this);
    m_signalMode->setLinObj(this);
}

void TestObject::initObject()
{

}

int TestObject::objId() const
{
    return m_objId;
}

void TestObject::setObjId(int newObjId)
{
    m_objId = newObjId;
}

QVariant TestObject::value() const
{
    return m_value;
}

void TestObject::setValue(const QVariant &newValue)
{
    m_value = newValue;
}

ModelBlueprintSignal *TestObject::signalMode() const
{
    return m_signalMode;
}
