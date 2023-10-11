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
    Q_PROPERTY(AgeState ageState READ getAgeState WRITE setAgeState NOTIFY ageStateChanged )
    Q_PROPERTY(QString sex READ getSex WRITE setSex NOTIFY sexChanged )
    Q_PROPERTY(SexState sexState READ getSexState WRITE setSexState NOTIFY sexStateChanged )

public:
    enum AgeState{
        Baby,
        kid,
        Teens,
        Adult,
        Old
    };


    enum SexState{
        Man,
        Woman
    };



protected:
    int m_age;
    QString m_sex;
    AgeState m_ageState;
    SexState m_sexState;


public:
    explicit People(QObject *parent = nullptr);

    int getAge()const;
    void setAge(const int & age);

    QString getSex()const;
    void setSex(const QString& sex);

    AgeState getAgeState()const;
    void setAgeState(const AgeState& age);

    SexState getSexState()const;
    void setSexState(const SexState& sexState);


    void addProperty( ModelProperty* property);
    QVector<ModelProperty*> getPropertiesList();
    ModelProperty* getProperty(QString name);

signals:
    void ageChanged(const int& age);
    void sexChanged(const QString& sex);
    void ageStateChanged(const AgeState& ageState);
    void sexStateChanged(const SexState& sexState);
private:
    QVector<ModelProperty*> m_propertiesList;
    QMap<QString,ModelProperty*> m_propertiesMap;
};

#endif // PEOPLE_H
