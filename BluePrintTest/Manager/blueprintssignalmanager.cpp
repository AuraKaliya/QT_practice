#include "blueprintssignalmanager.h"
#include "nodemanager.h"

QMap<QString,QMultiMap<unsigned int,unsigned int> >  BlueprintsSignalManager::m_signalFromObjectToPortDictionary{};

void BlueprintsSignalManager::bindObjectAndPort(QString signalName, TestObject *obj, PortObjectItem *port)
{

}

void BlueprintsSignalManager::bindObjectAndPort(QString signalName, unsigned int objId, unsigned int portId)
{

    auto it=m_signalFromObjectToPortDictionary.find(signalName);
    if(it==m_signalFromObjectToPortDictionary.end())
    {
        m_signalFromObjectToPortDictionary[signalName]=QMultiMap<unsigned int,unsigned int>  {{objId,portId}};
    }
    else
    {
        it->insert(objId,portId);
    }
}

void BlueprintsSignalManager::solveSignal(QString signalName, TestObject *obj)
{
    //qDebug()<<"BlueprintsSignalManager::solveSignal | signalName"<<signalName<<"obj id:"<<obj->objId();
    //qDebug()<<"BlueprintsSignalManager::solveSignal | m_signalFromObjectToPortDictionary"<<m_signalFromObjectToPortDictionary;
    unsigned int objId=obj->objId();
    auto it=m_signalFromObjectToPortDictionary.find(signalName);
    if(it!=m_signalFromObjectToPortDictionary.end())
    {
        if(it->contains(objId))
        {

            auto portList=it->values(objId);
            // 可能会传递信息
            NodeManager::activateSignalPort(portList,obj);
        }
    }


}

BlueprintsSignalManager::BlueprintsSignalManager(QObject *parent)
    : QObject{parent}
{

}
