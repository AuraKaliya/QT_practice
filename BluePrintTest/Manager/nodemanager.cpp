#include "nodemanager.h"


unsigned int NodeManager::m_nodeId = 1;
unsigned int NodeManager::m_portId = 1;
void NodeManager::registerNode(NodeObjectItem *item)
{
    item->setNodeId(m_nodeId);
    updateNodeId();
    for(auto it:item->portList())
    {
        registerPort(it);
    }
}

void NodeManager::registerPort(PortObjectItem *port)
{
    port->setPortId(m_portId);
    updatePortId();
}

void NodeManager::updateNodeId()
{
    m_nodeId++;
}

void NodeManager::updatePortId()
{
    m_portId++;
}

NodeManager::NodeManager(QObject *parent)
    : QObject{parent},m_nodeDictionary{}
{

}

void NodeManager::setLinkView(QGraphicsView *view)
{
    m_linkView=view;
}

void NodeManager::addNode(NodeObjectItem *node)
{
    m_nodeDictionary[node->nodeId()]=node;
}

NodeObjectItem *NodeManager::getNodeByPos(QPoint pos)
{
    if(!m_linkView) return nullptr;
    return static_cast<NodeObjectItem*>(m_linkView->itemAt(pos));
}

QVector<NodeObjectItem *> NodeManager::getNodeList()
{
    return  m_nodeDictionary.values();
}
