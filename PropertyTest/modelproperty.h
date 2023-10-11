#ifndef MODELPROPERTY_H
#define MODELPROPERTY_H

#include <QObject>
#include <QString>
#include <QVariant>

class ModelProperty : public QObject
{
    Q_OBJECT
public:
    ModelProperty(QString name="default", QString type="int", QVariant value=QVariant::fromValue(0),QObject *parent = nullptr);
    //ModelProperty(const ModelProperty& m);
    //ModelProperty & operator=(ModelProperty& m){return *this;};
    QString propertyName();
    QString propertyType();
    QVariant  propertyValue();
    void setValue(QVariant& var);



private:
    QString m_name;
    QString m_type;
    QVariant m_value;



signals:

};

#endif // MODELPROPERTY_H
