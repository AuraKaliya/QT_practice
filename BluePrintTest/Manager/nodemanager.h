#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <QObject>
#include <QGraphicsView>

#include "../Item/Node/nodeobjectitem.h"


class NodeManager : public QObject
{
    Q_OBJECT


public:
    static void registerNode(NodeObjectItem* item);
    static void registerPort(PortObjectItem *port);
    static void updateNodeId();
    static void updatePortId();

public:
    explicit NodeManager(QObject *parent = nullptr);
    void setLinkView(QGraphicsView * view);
    void addNode(NodeObjectItem* node);
    NodeObjectItem* getNodeByPos(QPoint pos);
    QVector<NodeObjectItem*> getNodeList();
private:

private:
    static unsigned int m_nodeId;
    static unsigned int m_portId;

private:
    QMap<unsigned int ,NodeObjectItem*> m_nodeDictionary;
    QGraphicsView * m_linkView=nullptr;
signals:

};

#endif // NODEMANAGER_H
