#include "testvaluenode.h"

TestValueNode::TestValueNode(QObject *parent, QGraphicsItem *itemParent)
    :NodeObjectItem(parent,itemParent)
{
    setNodeType(StartNode);
    m_valuePort=new PortObjectItem(this);
    m_valuePort->initPort("TetsValuePort",
                          PortObjectItem::Output,
                          PortObjectItem::Int
                          );

    m_valuePort->setSolveStratagy(PortObjectItem::Multiple);

    addPort(m_valuePort);

}

void TestValueNode::solute()
{
    m_valuePort->setPortValue(4);
}
