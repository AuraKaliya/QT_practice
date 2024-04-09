#ifndef MODELPROPERTY_H
#define MODELPROPERTY_H

#include <QObject>
#include <QString>
#include <QVariant>
#include "../baseClass/componentobject.h"

class ModelProperty : public ComponentObject
{
    Q_OBJECT
public:
    explicit ModelProperty(QObject *parent = nullptr);
    explicit ModelProperty(QString name="default", QString type="int", QVariant value=QVariant::fromValue(0),QObject *parent = nullptr);
    //ModelProperty(const ModelProperty& m);
    //ModelProperty & operator=(ModelProperty& m){return *this;};
    QString propertyName();
    QString propertyType();
    QVariant propertyValue();
    void setValue(QVariant& var);
    void tick()override;


private:
    QString m_name;
    QString m_type;
    QVariant m_value;



signals:

};
REGISTER_OBJECT(ModelProperty,ComponentObject)
#endif // MODELPROPERTY_H
