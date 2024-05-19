#include "nodeobjectitem.h"

QMap<NodeObjectItem::NodeType,QPair<QColor,QColor>> NodeObjectItem::m_typeColorDictionary
{
    {NoType,{QColor(255,255,255,255),QColor(0,0,0,255)}}
    ,{StartNode,{QColor(200,255,120,255),QColor(255,255,255,255)}}
    ,{EndNode,{QColor(200,120,255,255),QColor(255,255,255,255)}}
    ,{SolveNode,{QColor(130,250,123,255),QColor(255,255,255,255)}}

};
NodeObjectItem::NodeObjectItem(QObject *parent, QGraphicsItem *itemParent)
    :QObject{parent}
    ,QGraphicsItem{itemParent}
    ,m_nodeId(0)
    ,m_nodeTitle("")
    ,m_fixTitleHeight(40)
    ,m_fixPortHeight(50)
    ,m_nodeWidth(260)
    ,m_nodeHeight(90)
    ,m_solveFlag(false)
    ,m_readyFlag(false)
    ,m_nextNodeList{}


{
    setFlags(ItemIsMovable | ItemClipsToShape | ItemIsSelectable);
    setNodeType(NoType);
    updateNodeSize();
}

QRectF NodeObjectItem::boundingRect() const
{
    //返回其所包含的输入端口数和输出端口数更高的 对应的高度  和 预设的宽度
    return QRectF(0,0,m_nodeWidth,m_nodeHeight);
}

void NodeObjectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal cornerRadius = 10.0; // 圆角的半径
    qreal titlecornerRadius = 10.0; // 圆角的半径
    QRectF titleBarRect(0, 0, boundingRect().width(), m_fixTitleHeight);

    // 根据选中状态设置节点的颜色
        if (isSelected()) {
        //选中设置笔，描绘边框颜色
        QPen pen;
        pen.setColor(Qt::white);
        pen.setWidth(4);
        //调整标题
        titlecornerRadius=7;
        titleBarRect=QRectF(2, 2, boundingRect().width()-4, 36);
        painter->setPen(pen);
        painter->setBrush(QColor(50,50,50,240));
    } else {
        //没选中不设置笔
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(70,70,70,240));
    }

    // 绘制背景
    painter->drawRoundedRect(boundingRect(), cornerRadius, cornerRadius);

    //重置
    painter->setPen(Qt::NoPen);

    // 绘制标题栏
    QLinearGradient gradient(titleBarRect.topLeft(), titleBarRect.bottomLeft());
    gradient.setColorAt(0, m_titleColor); // 起始颜色
    gradient.setColorAt(1, QColor(70,70,70,150));   // 终止颜色
    QBrush titleBarBrush(gradient);
    painter->setBrush(titleBarBrush); // 设置标题栏的颜色
    painter->drawRoundedRect(titleBarRect,titlecornerRadius,titlecornerRadius);

    // 添加标题文本
    QFont titleFont = painter->font();
    titleFont.setBold(true);
    titleFont.setPixelSize(15);
    painter->setFont(titleFont);
    painter->setPen(m_titleTextColor); // 设置标题文本颜色
    painter->drawText(titleBarRect, Qt::AlignCenter, m_nodeTitle);


    //绘制端口  Port
    for(const auto &it:m_portList)
    {
        //link端口
        if(it->portType()==PortObjectItem::InLink||it->portType()==PortObjectItem::OutLink)
        {
            // 根据端口类型绘制向右的实心三角形或空心三角形
            QPolygonF triangle;
            triangle << QPointF(it->portRect().right(), it->portRect().center().y())
                     << QPointF(it->portRect().left(), it->portRect().top())
                     << QPointF(it->portRect().left(), it->portRect().bottom());


            QPen pen(QColor(255,255,255,255), 4);
            pen.setCapStyle(Qt::RoundCap); // 设置线帽为圆滑
            pen.setJoinStyle(Qt::RoundJoin);
            painter->setPen(pen);
            if (!it->linkPortState()) {
                //未连接画空心三角形
                painter->setBrush(Qt::NoBrush);
                painter->drawPolygon(triangle);
            } else {
                // 已连接，画实心三角形
                painter->setBrush(QColor(255,255,255,255));
                painter->drawPolygon(triangle);
            }

            painter->setPen(Qt::NoPen);
            painter->setBrush(Qt::NoBrush);
        }

        //输入输出端口
        if(it->portType()==PortObjectItem::Input||it->portType()==PortObjectItem::Output)
        {
            //qDebug()<<"check:   "<<it->portName()<<it->portDataType() << PortObjectItem::getColorByDataType(it->portDataType());
            //qDebug()<<"check2:"<<QColor(223,213,200,255);
            //
            QPen pen(PortObjectItem::getColorByDataType(it->portDataType()),5);

            pen.setCapStyle(Qt::RoundCap); // 设置线帽为圆滑
            pen.setJoinStyle(Qt::RoundJoin);
            painter->setPen(pen);



            //未连接画空心
            if(!it->linkPortState())
            {
                //设置笔，不设置刷子画空心圆
                painter->setBrush(Qt::NoBrush);
                painter->drawEllipse(it->portRect());
            }//已连接画实心圆
            else
            {
                //不设置笔，画实心圆
                //PortObjectItem::getColorByDataType(it->portDataType())
                painter->setBrush(PortObjectItem::getColorByDataType(it->portDataType()));
                painter->drawEllipse(it->portRect());

            }

            painter->setPen(Qt::NoPen);
            painter->setBrush(Qt::NoBrush);

        }



    }





}

void NodeObjectItem::nodeRun()
{
    //qDebug()<<"Node Run :"<<m_nodeTitle;
    //固定预处理
    //   进入到run阶段 代表所有输入端口准备就绪 此节点准备就绪
    //solute（）
    solute();
    //后续处理
    //qDebug()<<"Node Soluted : outPort"<<m_outPortList.size();

    //处理完成 需要先将输出端口连接的端口的状态设置为就绪状态
    for(auto it:m_outPortList)
    {
        //qDebug()<<"Node Soluted : outPort link"<<it->portId()<<" - "<<it->linkPort()->portId();
        PortObjectItem* port =it->linkPort();
        port->setPortValue(it->portValue());
        port->setDataState(true);
    }

    //   然后根据输入端口的策略进行状态重置
    resetInPortReadyState();

    setSolveFlag(true);
    setReadyFlag(false);
}

void NodeObjectItem::solute()
{
    //处理   获取输入端口的数据 --- 逻辑处理  --- 设置输出端口数据
}

QVariant NodeObjectItem::getValue()
{
    return QVariant(0);
}

void NodeObjectItem::addPort(PortObjectItem *port)
{
    m_portList.append(port);

    QRect portRect;

    int leftSpace=5;
    int a=30;

    if(port->portType()==PortObjectItem::Input)
    {
        portRect=QRect(leftSpace,m_fixTitleHeight+(m_inPortList.size()+1)*m_fixPortHeight+(m_fixPortHeight-a)/2,a,a);
        m_inPortList.append(port);
    }

    if(port->portType()==PortObjectItem::Output)
    {
        portRect=QRect(m_nodeWidth-leftSpace-a,m_fixTitleHeight+(m_outPortList.size()+1)*m_fixPortHeight+(m_fixPortHeight-a)/2,a,a);
        m_outPortList.append(port);
    }
    if(port->portType()==PortObjectItem::InLink)
    {
        portRect=QRect(leftSpace,m_fixTitleHeight+(m_fixPortHeight-a)/2,a,a);
        m_inLinkPort=port;
    }
    if(port->portType()==PortObjectItem::OutLink)
    {
        portRect=QRect(m_nodeWidth-leftSpace-a,m_fixTitleHeight+(m_fixPortHeight-a)/2,a,a);
        m_outLinkPort=port;
    }
    port->setLinkNode(this);
    port->setPortRect(portRect);

    connect(port,&PortObjectItem::dataStateChanged,this,[this,port](){
        if(port->dataState())
        m_waitDataPortSet.remove(port);
    });


    updateNodeSize();
}

void NodeObjectItem::initSolveInformation()
{
    setSolveFlag(false);
    setReadyFlag(false);
    m_startNodeList.clear();

    for(auto it:m_inPortList)
    {
        m_waitDataPortSet.insert(it);
    }
}

bool NodeObjectItem::checkReadyPort()
{
    if(m_waitDataPortSet.size()<1)
    {
        setReadyFlag(true);
    }

    return m_readyFlag;
}

void NodeObjectItem::resetInPortReadyState()
{
    for(auto it: m_inPortList)
    {
        if(it->solveStratagy() == PortObjectItem::Single)
        {
            m_waitDataPortSet.insert(it);
        }
    }
}

unsigned int NodeObjectItem::getInPortCount() const
{
    return std::count_if(m_portList.begin(),m_portList.end(),[](PortObjectItem* port){
        return port->portType() == PortObjectItem::Input;
    });
}

unsigned int NodeObjectItem::getOutPortCount() const
{
    return std::count_if(m_portList.begin(),m_portList.end(),[](PortObjectItem* port){
        return port->portType() == PortObjectItem::Output;
    });
}

PortObjectItem *NodeObjectItem::getPortByPos(QPointF pos)
{
    QPoint realPos(pos.x()-x(),pos.y()-y());
    //qDebug()<<"NodeObjectItem::getPortByPos |realPos:"<<realPos;
//    for(auto it:m_portList)
//    {
//        //qDebug()<<"NodeObjectItem::getPortByPos | check: "<<it->portRect();
//    }

    auto it =std::find_if(m_portList.begin(),m_portList.end(),[realPos](PortObjectItem* port){
        return port->portRect().contains(realPos);
    });
    if(it != m_portList.end())
    {
        return *it;
    }
    return nullptr;
}

void NodeObjectItem::updateNodeSize()
{
    //更新节点的boundingRect的大小

    // 1. 获取 输入 输出 的端口数
    unsigned int inPortCount=getInPortCount();
    unsigned int outPortCount=getOutPortCount();

    unsigned int height= qMax(inPortCount,outPortCount) * m_fixPortHeight;

    //留出一个title 和一个link 的高度
    m_nodeHeight=qMax(m_fixPortHeight,height)+m_fixTitleHeight+m_fixPortHeight;

    //暂时固定一个节点左右两边各80
    m_nodeWidth=260;
}

void NodeObjectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsItem::mouseMoveEvent(e);
    emit  needUpdate(this);
}

QSet<NodeObjectItem *> NodeObjectItem::startNodeList() const
{
    return m_startNodeList;
}

void NodeObjectItem::addStartNode(NodeObjectItem *node)
{
    m_startNodeList.insert(node);
}

QVector<NodeObjectItem *> NodeObjectItem::nextNodeList() const
{
    return m_nextNodeList;
}

void NodeObjectItem::setNextNodeList(const QVector<NodeObjectItem *> &newNextNodeList)
{
    m_nextNodeList = newNextNodeList;
}

void NodeObjectItem::addNextNode(NodeObjectItem *node)
{
    m_nextNodeList.append(node);
}

bool NodeObjectItem::readyFlag() const
{
    return m_readyFlag;
}

void NodeObjectItem::setReadyFlag(bool newReadyFlag)
{
    m_readyFlag = newReadyFlag;
}

bool NodeObjectItem::solveFlag() const
{
    return m_solveFlag;
}

void NodeObjectItem::setSolveFlag(bool newSolveFlag)
{
    m_solveFlag = newSolveFlag;
}

NodeObjectItem::NodeType NodeObjectItem::nodeType() const
{
    return m_nodeType;
}

void NodeObjectItem::setNodeType(NodeType newNodeType)
{
    if (m_nodeType == newNodeType)
        return;
    m_nodeType = newNodeType;

    if(! m_typeColorDictionary.contains(m_nodeType)) return;

    m_titleColor=m_typeColorDictionary[m_nodeType].first;
    m_titleTextColor=m_typeColorDictionary[m_nodeType].second;


    emit nodeTypeChanged();
}

QString NodeObjectItem::nodeTitle() const
{
    return m_nodeTitle;
}

void NodeObjectItem::setNodeTitle(const QString &newNodeName)
{
    if (m_nodeTitle == newNodeName)
        return;
    m_nodeTitle = newNodeName;
    emit nodeTitleChanged();
}

QVector<PortObjectItem *> NodeObjectItem::portList() const
{
    return m_portList;
}

unsigned int NodeObjectItem::nodeId() const
{
    return m_nodeId;
}

void NodeObjectItem::setNodeId(unsigned int newId)
{
    if (m_nodeId == newId)
        return;
    m_nodeId = newId;
    emit idChanged();
}
