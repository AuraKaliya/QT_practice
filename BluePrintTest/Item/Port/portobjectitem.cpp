#include "portobjectitem.h"
#include "../Node/nodeobjectitem.h"

QMap<PortObjectItem::PortDataType,QColor> PortObjectItem::m_typeColorDictionary{
    {NoneDataType,QColor(255,255,255,255)}
    ,{Int,QColor(223,213,200,255)}
    ,{Bool,QColor(200,244,244,255)}
    ,{String,QColor(220,180,200,255)}
    ,{Double,QColor(210,233,140,255)}
    ,{Float,QColor(230,210,13,255)}
};
QMultiMap<PortObjectItem::PortDataType,PortObjectItem::PortDataType> PortObjectItem::m_assertDataTypeDictionary{

    //Int
    {Int, Double},
    {Int, String},
    {Int, Bool},
    {Int, Float},

    //Double
    {Double, Int},
    {Double, String},
    {Double, Bool},
    {Double, Float},

    //Bool
    {Bool, Int},
    {Bool, String},
    {Bool, Double},
    {Bool, Float},

    //String
    {String, Int},
    {String, Bool},
    {String, Double},
    {String, Float}


};



QColor PortObjectItem::getColorByDataType(PortDataType type)
{

    //qDebug()<<"PortObjectItem::getColorByDataType | check0:"<<m_typeColorDictionary;
    //qDebug()<<"PortObjectItem::getColorByDataType | check1:"<<type<<m_typeColorDictionary[type].value();
    return m_typeColorDictionary[type];
}

PortObjectItem::PortObjectItem(QObject *parent)
    : QObject{parent},m_assertDataTypeSet{},m_portId(0),
    m_portName(""),m_portValue(0),m_portTip(""),
    m_portType(NoneType),m_portDataType(NoneDataType),m_dataState(false),
    m_linkNode(static_cast<NodeObjectItem*>(parent)),m_linkPortState(false)
{

}

void PortObjectItem::initPort(QString name, PortType type, PortDataType dataType)
{
    setPortName(name);
    setPortType(type);
    setPortDataType(dataType);
}




void PortObjectItem::addDataType(PortDataType dataType)
{

}

unsigned int PortObjectItem::portId() const
{
    return m_portId;
}

void PortObjectItem::setPortId(unsigned int newPortId)
{
    if (m_portId == newPortId)
        return;
    m_portId = newPortId;
    emit portIdChanged();
}

QString PortObjectItem::portName() const
{
    return m_portName;
}

void PortObjectItem::setPortName(const QString &newPortName)
{
    if (m_portName == newPortName)
        return;
    m_portName = newPortName;
    emit portNameChanged();
}

QVariant PortObjectItem::portValue() const
{
    return m_portValue;
}

void PortObjectItem::setPortValue(const QVariant &newPortValue)
{
    m_portValue = newPortValue;
    m_dataState=true;
}

QString PortObjectItem::portTip() const
{
    return m_portTip;
}

void PortObjectItem::setPortTip(const QString &newPortTip)
{
    if (m_portTip == newPortTip)
        return;
    m_portTip = newPortTip;

}

NodeObjectItem *PortObjectItem::linkNode() const
{
    return m_linkNode;
}

void PortObjectItem::setLinkNode(NodeObjectItem *newLinkNode)
{
    m_linkNode = newLinkNode;
}

PortObjectItem::PortType PortObjectItem::portType() const
{
    return m_portType;
}

void PortObjectItem::setPortType(PortType newPortType)
{
    if (m_portType == newPortType)
        return;
    m_portType = newPortType;
    emit portTypeChanged();
}

bool PortObjectItem::linkPortState() const
{
    return m_linkPortState;
}

void PortObjectItem::setLinkPortState(bool newLinkPortState)
{
    m_linkPortState = newLinkPortState;
}

QRect PortObjectItem::portRect() const
{
    return m_portRect;
}

void PortObjectItem::setPortRect(QRect newPortRect)
{
    m_portRect = newPortRect;

}

PortObjectItem::PortDataType PortObjectItem::portDataType() const
{
    return m_portDataType;
}

void PortObjectItem::setPortDataType(PortDataType newPortDataType)
{
    if (m_portDataType == newPortDataType)
        return;
    m_portDataType = newPortDataType;
    emit portDataTypeChanged();
}

PortObjectItem *PortObjectItem::linkPort() const
{
    return m_linkPort;
}

void PortObjectItem::setLinkPort(PortObjectItem *newLinkPort)
{
    m_linkPort = newLinkPort;
}


