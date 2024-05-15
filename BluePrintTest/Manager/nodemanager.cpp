#include "nodemanager.h"


unsigned int NodeManager::m_nodeId = 1;
unsigned int NodeManager::m_portId = 1;
QMap<unsigned int ,NodeObjectItem*> NodeManager::m_nodeDictionary{};
QMap<unsigned int,QVector<LinkInformation> > NodeManager::m_linkInformationDictionary{};
void NodeManager::registerNode(NodeObjectItem *item)
{
    item->setNodeId(m_nodeId);
    m_nodeDictionary[m_nodeId]=item;
    m_linkInformationDictionary[m_nodeId]=QVector<LinkInformation>();
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

PortInfomation NodeManager::getPortInfoByPos(QGraphicsView *view, QPoint pos)
{
    //qDebug()<<"NodeManager::getPortInfoByPos | check0:"<<pos;
    PortInfomation res;
    QGraphicsItem * item=view->itemAt(pos.x(),pos.y());
    NodeObjectItem* node = static_cast<NodeObjectItem*>(item);

    if(!node) return res;
    //qDebug()<<"NodeManager::getPortInfoByPos | check1: item != nullptr.";

    PortObjectItem* port=node->getPortByPos(view->mapToScene(pos));
    if(port)
    {
        res.setNode(node);
        res.setPort(port);
        //qDebug()<<"NodeManager::getPortInfoByPos | check 2: port:"<<port->portRect();
    }else
    {
       //qDebug()<<"NodeManager::getPortInfoByPos | check 2: no port.";
    }


    return res;
}

QPair<bool, PortObjectItem *> NodeManager::checkLinkPort(PortObjectItem *outPort, PortObjectItem *inPort)
{
    bool linkFlag=false;
    PortObjectItem* switchPort=nullptr;
    //1. 检查端口的输入输出类型
    if(
        (outPort->portType()==PortObjectItem::PortType::OutLink || outPort->portType() ==PortObjectItem::PortType::Output) &&
        (inPort->portType()==PortObjectItem::PortType::InLink  || inPort->portType() ==PortObjectItem::PortType::Input)
      )
    {
        linkFlag=true;
    }
    //2. 检查端口的数据类型
    if(linkFlag)
    {
        if(outPort->portDataType() != inPort->portDataType())
        {
            linkFlag=false;
        }


        if(!linkFlag)
            //3. 尝试能否进行添加转换
        {

        }
    }

    return QPair<bool,PortObjectItem*>(linkFlag,switchPort);
}

void NodeManager::linkPort( PortObjectItem *port1, PortObjectItem *port2,BezierCurveItem*linkLine)
{
    if(!port1  || !port2) return;

    LinkInformation linkInformation ;
    linkInformation.setLinkNode1(port1->linkNode());
    linkInformation.setLinkNode2(port2->linkNode());
    linkInformation.setLinkPort1(port1);
    linkInformation.setLinkPort2(port2);

    linkInformation.setLinkLine(linkLine);

    m_linkInformationDictionary[port1->linkNode()->nodeId()].append(linkInformation);
    m_linkInformationDictionary[port2->linkNode()->nodeId()].append(linkInformation);

    port1->setLinkPort(port2);
    port2->setLinkPort(port1);

    port1->setLinkPortState(true);
    port2->setLinkPortState(true);

    connect(port1->linkNode(),&NodeObjectItem::needUpdate,port1->linkNode(),[](NodeObjectItem* node){
        NodeManager::updateLinkLineByNode(node);
    });

    connect(port2->linkNode(),&NodeObjectItem::needUpdate,port2->linkNode(),[](NodeObjectItem* node){
        NodeManager::updateLinkLineByNode(node);
    });
}

void NodeManager::updateLinkLineByNode(NodeObjectItem *node)
{
    unsigned int id=node->nodeId();
    for(auto it: m_linkInformationDictionary[id])
    {
        if(it.linkLine())
        {
            it.linkLine()->UpdatePoint(
                QPointF(it.linkNode1()->pos()+it.linkPort1()->portRect().center()),
                QPointF(it.linkNode2()->pos()+it.linkPort2()->portRect().center())
                                       );
        }
    }
}

NodeManager::NodeManager(QObject *parent)
    : QObject{parent}
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

unsigned int NodeManager::nodeId()
{
    return m_nodeId;
}
