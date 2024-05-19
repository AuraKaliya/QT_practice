#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include<QVariant>
#include <QObject>
#include "../Component/modelblueprintsignal.h"

class TestObject : public QObject
{
    Q_OBJECT
public:
    explicit TestObject(QObject *parent = nullptr);

    void initObject();
    int objId() const;
    void setObjId(int newObjId);

    QVariant value() const;
    void setValue(const QVariant &newValue);

    ModelBlueprintSignal *signalMode() const;

private:
    ModelBlueprintSignal* m_signalMode=nullptr;
    int m_objId;
    QVariant m_value;
signals:
    void testSignal();
};

#endif // TESTOBJECT_H
