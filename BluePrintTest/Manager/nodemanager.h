#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <QObject>
#include <QPair>
#include <QGraphicsView>

#include "../Item/Node/nodeobjectitem.h"

#include "portinfomation.h"
#include "linkinformation.h"


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

public:
    explicit NodeManager(QObject *parent = nullptr);
    void setLinkView(QGraphicsView * view);
    void addNode(NodeObjectItem* node);
    NodeObjectItem* getNodeByPos(QPoint pos);
    QVector<NodeObjectItem*> getNodeList();

    static unsigned int nodeId();

private:

private:
    static unsigned int m_nodeId;
    static unsigned int m_portId;
    static QMap<unsigned int ,NodeObjectItem*> m_nodeDictionary;
    static QMap<unsigned int,QVector<LinkInformation> > m_linkInformationDictionary;
private:

    QGraphicsView * m_linkView=nullptr;
signals:

};

#endif // NODEMANAGER_H
