#ifndef MODELBLUEPRINTSIGNAL_H
#define MODELBLUEPRINTSIGNAL_H

#include <QObject>

class TestObject;
class ModelBlueprintSignal : public QObject
{
    Q_OBJECT
public:
    explicit ModelBlueprintSignal(QObject *parent = nullptr);
    void emitSignal(QString string);


    TestObject *linObj() const;
    void setLinObj(TestObject *newLinObj);

private:
    TestObject* m_linkObj=nullptr;

signals:

};

#endif // MODELBLUEPRINTSIGNAL_H
