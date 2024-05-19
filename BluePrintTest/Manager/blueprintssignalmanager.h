#ifndef BLUEPRINTSSIGNALMANAGER_H
#define BLUEPRINTSSIGNALMANAGER_H

#include <QObject>
#include <QString>
#include <QSet>
#include <QMap>

#include "../Component/modelblueprintsignal.h"
#include "../Object/testobject.h"
class PortObjectItem;
class BlueprintsSignalManager : public QObject
{
    Q_OBJECT
public:
    static void bindObjectAndPort(QString signalName,TestObject* obj,PortObjectItem*port);
    static void bindObjectAndPort(QString signalName,unsigned int objId,unsigned int portId);
    static void solveSignal(QString signalName,TestObject* obj);
public:

    explicit BlueprintsSignalManager(QObject *parent = nullptr);
private:
    static QMap<QString,QMultiMap<unsigned int,unsigned int> > m_signalFromObjectToPortDictionary;
signals:

};

#endif // BLUEPRINTSSIGNALMANAGER_H
