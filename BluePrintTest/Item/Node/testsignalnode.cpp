#include "testsignalnode.h"


TestSignalNode::TestSignalNode(QObject *parent, QGraphicsItem *itemParent)
: NodeObjectItem(parent,itemParent)
{
    setNodeType(StartNode);
    m_objLinkValuePort=new PortObjectItem(this);
    m_objLinkValuePort->initPort("TestPort1",
               PortObjectItem::Input,
               PortObjectItem::Int
               );
    m_objLinkValuePort->setSolveStratagy(PortObjectItem::Single);

    m_outValuePort=new PortObjectItem(this);
    m_outValuePort->initPort("TestPort1",
                                 PortObjectItem::Output,
                                 PortObjectItem::Int
                                 );
    addPort(m_objLinkValuePort);
    addPort(m_outValuePort);
}

void TestSignalNode::solute()
{
    m_outValuePort->setPortValue(m_objLinkValuePort->portValue());
}

TestObject *TestSignalNode::linkObj() const
{
    return m_linkObj;
}

void TestSignalNode::setLinkObj(TestObject *newLinkObj)
{
    m_linkObj = newLinkObj;
}
