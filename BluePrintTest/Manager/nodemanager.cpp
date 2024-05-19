#include "nodemanager.h"


unsigned int NodeManager::m_nodeId = 1;
unsigned int NodeManager::m_portId = 1;
bool NodeManager::m_solveFlag=false;
QMap<unsigned int ,NodeObjectItem*> NodeManager::m_nodeDictionary{};
QMap<unsigned int ,PortObjectItem*> NodeManager::m_portDictionary{};
QMap<unsigned int,QVector<LinkInformation> > NodeManager::m_linkInformationDictionary{};
QSet<NodeObjectItem*> NodeManager::m_nextSolveQueue{};
QSet<NodeObjectItem*> NodeManager::m_solveQueue{};

void NodeManager::registerNode(NodeObjectItem *item)
{

    item->setNodeId(m_nodeId);
    m_nodeDictionary.insert(m_nodeId,item);
    m_linkInformationDictionary[m_nodeId]=QVector<LinkInformation>();
    updateNodeId();
    //qDebug()<<"NodeManager::registerNode| port"<<item->portList();

    for(auto it:item->portList())
    {
        //qDebug()<<"NodeManager::registerNode|register";
        registerPort(it);
    }


    connect(item,&NodeObjectItem::stopSolution,item,[](){
        setSolveFlag(false);
    },Qt::QueuedConnection);

    //qDebug()<<"NodeManager::registerNode :NOW node:"<< m_nodeDictionary.keys();
    //qDebug()<<"NodeManager::registerNode :NOW port:"<< m_portDictionary.keys();
}

void NodeManager::registerPort(PortObjectItem *port)
{
    port->setPortId(m_portId);
    m_portDictionary.insert(m_portId,port);
    updatePortId();
    //qDebug()<<"NodeManager::registerPort : NOW Port id:"<<m_portId;
    //qDebug()<<"NodeManager::registerPort | now portDictionary:"<<m_portDictionary;
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

    if(port1->portType()==PortObjectItem::InLink || port1->portType()==PortObjectItem::Input )
    {
        port2->linkNode()->addNextNode(port1->linkNode());
        port1->setSolveStratagy(port2->solveStratagy());
    }
    else
    {
        port1->linkNode()->addNextNode(port2->linkNode());
        port2->setSolveStratagy(port1->solveStratagy());
    }



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

void NodeManager::preInit()
{
    //0， 清除影响
    m_solveQueue.clear();
    for(auto it:m_nodeDictionary)
    {
        it->initSolveInformation();
    }

    //1. 找出已注册的所有的开始节点   NodeType == StartNode
    auto it=m_nodeDictionary.values();
//    std::copy_if(it.begin(),it.end(),std::back_inserter(m_solveQueue),[](NodeObjectItem* node){
//        return node->nodeType()==NodeObjectItem::StartNode;
//    });
    std::for_each(it.begin(),it.end(),[](NodeObjectItem* node){
        if(node->nodeType() == NodeObjectItem::StartNode)
        {
            m_solveQueue.insert(node);
        }
    });



    //2. 为每个起始节点的 起始节点 赋值  自己即是自己的起始节点
    for(auto it:m_solveQueue)
    {
        it->addStartNode(it);
        it->checkReadyPort();
    }

    setSolveFlag(true);

    for(auto it:m_nodeDictionary)
    {
        qDebug()<<it->nodeId() << " ---- "<<it->nodeTitle();
    }
}

void NodeManager::run()
{
//while
    while(m_solveFlag)
    {
        //测试用  非阻塞计算
        QCoreApplication::processEvents();
        //qDebug()<<" NodeManager::run  | check 0 m_solveQueue:"<<m_solveQueue.size()  << "m_nextSolveQueue :" <<m_nextSolveQueue.size();

        // 将next与现 队列合并
        if(m_nextSolveQueue.size()>0)
        {
            m_solveQueue.unite(m_nextSolveQueue);
            m_nextSolveQueue.clear();
        }
        //qDebug()<<" NodeManager::run  | check 1 m_solveQueue:"<<m_solveQueue.size()  ;
        for(auto it: m_solveQueue)
        {
            if(it->checkReadyPort())
            {
                // 进行处理
                it->nodeRun();
                // 处理完成 去掉该节点， 将其连接的节点加入进队列
                m_solveQueue.remove(it);
                //qDebug()<<" NodeManager::run  | check 2 linkNode:"<<it->nodeId()<<" link n: "<<it->nextNodeList().size();
                for(auto nextNode:it->nextNodeList() )
                {
                    // 将后续节点的开始节点 添加 其的开始节点
                    for(auto startNode:it->startNodeList())
                    {
                        nextNode->addStartNode(startNode);
                        m_nextSolveQueue.insert(nextNode);
                    }
                }
            }
            else
            {
                //qDebug()<<" NodeManager::run  | check 3 node:"<<it->nodeId()<<" not ready.";
            }
        }
    }

}

void NodeManager::activateSignalPort(QList<unsigned int> portIdList,TestObject* obj)
{
    //qDebug()<<"NodeManager::activateSignalPort |portIdList:"<<portIdList;
     //qDebug()<<"NodeManager::activateSignalPort |m_portDictionary:"<<m_portDictionary;
    for(auto portId:portIdList)
    {
        auto it=m_portDictionary.find(portId);
        if(it!=m_portDictionary.end())
        {
            //可用QMetaObject工具获取特定属性， 那么还需要添加部分控制参数（由 port 控制）

            it.value()->setPortValue(obj->value());
            m_solveQueue.insert(it.value()->linkNode());
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

bool NodeManager::solveFlag()
{
    return m_solveFlag;
}

void NodeManager::setSolveFlag(bool newSolveFlag)
{
    m_solveFlag = newSolveFlag;
}
