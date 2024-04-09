#include "modelproperty.h"

ModelProperty::ModelProperty(QObject *parent):ComponentObject{parent}
{
   setObjectName("ModelProperty");
}

ModelProperty::ModelProperty(QString name, QString type, QVariant value,QObject *parent )
    : ModelProperty(parent)
{
    m_name=name;
    m_type=type;
    m_value=value;

}

//ModelProperty::ModelProperty(const ModelProperty &m)
//{
//    m_name=m.m_name;
//    m_type=m.m_type;
//    m_value=m.m_type;
//}

 QString ModelProperty::propertyName()
{
    return m_name;
}

 QString ModelProperty::propertyType()
{
    return m_type;
}

 QVariant ModelProperty::propertyValue()
{
    return m_value;
}

void ModelProperty::setValue(QVariant &var)
{
    m_value=var;
}

void ModelProperty::tick()
{

}
