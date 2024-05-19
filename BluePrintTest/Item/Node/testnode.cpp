#include "testnode.h"



TestNode::TestNode(QObject *parent, QGraphicsItem *itemParent)
    :NodeObjectItem(parent,itemParent)
{
    setNodeType(SolveNode);



    PortObjectItem* port2=new PortObjectItem(this);

    port2 ->initPort("TestPort2",
                    PortObjectItem::InLink,
                    PortObjectItem::NoneDataType
                    );


    PortObjectItem* port3=new PortObjectItem(this);

    port3 ->initPort("TestPort3",
                    PortObjectItem::OutLink,
                    PortObjectItem::NoneDataType
                    );



    m_inPort1=new PortObjectItem(this);

    m_inPort1->initPort("AddPort1",
                        PortObjectItem::Input,
                        PortObjectItem::Int
                        );

    m_inPort2=new PortObjectItem(this);

    m_inPort2->initPort("AddPort2",
                        PortObjectItem::Input,
                        PortObjectItem::Int
                        );



    m_outPort=new PortObjectItem(this);

    m_outPort->initPort("AddPort2",
                        PortObjectItem::Output,
                        PortObjectItem::Int
                        );

    addPort(port2);
    addPort(port3);
    addPort(m_inPort1);
    addPort(m_inPort2);
    addPort(m_outPort);
    qDebug()<<"testNode : portList"<<portList().size();
}

void TestNode::solute()
{
    qDebug()<<"TestNode::solute  | start.";
    int a=m_inPort1->portValue().toInt();
    int b=m_inPort2->portValue().toInt();

    int res=a+b;
    m_outPort->setPortValue(res);

    qDebug()<<"TestNode::solute  | end."  <<" outPort:"<<m_outPort->portValue();
}
