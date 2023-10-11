#include "people.h"

People::People(QObject *parent)
    : QObject{parent}
{
    setObjectName("People");
    setAge(10);
}

int People::getAge() const
{
    return m_age;
}

void People::setAge(const int &age)
{
    m_age=age;
}

QString People::getSex() const
{
    return m_sex;
}

void People::setSex(const QString &sex)
{
    m_sex=sex;
}

People::AgeState People::getAgeState() const
{
    return m_ageState;
}

void People::setAgeState(const AgeState &ageState)
{
    m_ageState=ageState;
}

People::SexState People::getSexState() const
{
    return m_sexState;
}

void People::setSexState(const SexState &sexState)
{
    m_sexState=sexState;
}

void People::addProperty(ModelProperty* property)
{

    m_propertiesList.append(property);
    m_propertiesMap.insert(property->propertyName(),property);
}

QVector<ModelProperty *> People::getPropertiesList()
{
    return m_propertiesList;
}

ModelProperty* People::getProperty(QString name)
{
    auto it = m_propertiesMap.find(name);
    if(it!=m_propertiesMap.end())
        return it.value();
    else
    {
        ModelProperty* pro=new ModelProperty(name);
        return pro;
    }
}
