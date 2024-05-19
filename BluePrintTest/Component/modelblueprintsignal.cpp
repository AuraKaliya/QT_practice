#include "modelblueprintsignal.h"
#include "../Object/testobject.h"
#include "../Manager/blueprintssignalmanager.h"


ModelBlueprintSignal::ModelBlueprintSignal(QObject *parent)
    : QObject{parent}
{

}

void ModelBlueprintSignal::emitSignal(QString string)
{
    BlueprintsSignalManager::solveSignal(string,m_linkObj);
}

TestObject *ModelBlueprintSignal::linObj() const
{
    return m_linkObj;
}

void ModelBlueprintSignal::setLinObj(TestObject *newLinObj)
{
    m_linkObj = newLinObj;
}
