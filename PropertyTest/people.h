#ifndef PEOPLE_H
#define PEOPLE_H

#include <QObject>
#include "modelproperty.h"
#include <QMap>
#include <QVector>

class People : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY ageChanged )

protected:
    int m_age;

public:
    explicit People(QObject *parent = nullptr);
    int getAge()const;
    void setAge(const int & age);
    void addProperty( ModelProperty* property);
    QVector<ModelProperty*> getPropertiesList();
    ModelProperty* getProperty(QString name);

signals:
    void ageChanged(const int& age);
private:
    QVector<ModelProperty*> m_propertiesList;
    QMap<QString,ModelProperty*> m_propertiesMap;
};

#endif // PEOPLE_H
