#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <QObject>
#include <QPair>
#include <QGraphicsView>
#include <QCoreApplication>
#include "../Item/Node/nodeobjectitem.h"

#include "portinfomation.h"
#include "linkinformation.h"
#include "blueprintssignalmanager.h"
#include "../Object/testobject.h"

class NodeManager : public QObject
{
    Q_OBJECT


public:
    static void registerNode(NodeObjectItem* item);
    static void registerPort(PortObjectItem *port);

    static void updateNodeId();
    static void updatePortId();

    static PortInfomation getPortInfoByPos(QGraphicsView* view, QPoint pos);
    static QPair<bool,PortObjectItem*> checkLinkPort(PortObjectItem* outPort,PortObjectItem* inPort);
    static void linkPort(PortObjectItem* port1, PortObjectItem* port2, BezierCurveItem *linkLine);

    static void updateLinkLineByNode(NodeObjectItem* node);


    static void preInit();     //处理节点的 预处理阶段
    static void run();         //开始运行蓝图


    static void activateSignalPort(QList<unsigned int >portIdList,TestObject* obj);


public:
    explicit NodeManager(QObject *parent = nullptr);
    void setLinkView(QGraphicsView * view);
    void addNode(NodeObjectItem* node);
    NodeObjectItem* getNodeByPos(QPoint pos);
    QVector<NodeObjectItem*> getNodeList();

    static unsigned int nodeId();

    static bool solveFlag();
    static void setSolveFlag(bool newSolveFlag);

private:

private:
    static unsigned int m_nodeId;
    static unsigned int m_portId;
    static QMap<unsigned int ,NodeObjectItem*> m_nodeDictionary;
    static QMap<unsigned int ,PortObjectItem*> m_portDictionary;
    static QMap<unsigned int,QVector<LinkInformation> > m_linkInformationDictionary;

    static QSet<NodeObjectItem*> m_solveQueue;
    static QSet<NodeObjectItem*> m_nextSolveQueue;

    static bool m_solveFlag;
private:

    QGraphicsView * m_linkView=nullptr;
signals:

};

#endif // NODEMANAGER_H
