#include "testendnode.h"

TestEndNode::TestEndNode(QObject *parent, QGraphicsItem *itemParent)
    : NodeObjectItem(parent,itemParent)
{
    setNodeType(EndNode);

    PortObjectItem* port1=new PortObjectItem(this);

    port1 ->initPort("TestPort1",
                    PortObjectItem::InLink,
                    PortObjectItem::NoneDataType
                    );

    m_resPort=new PortObjectItem(this);

    m_resPort ->initPort("TestPort2",
                    PortObjectItem::Input,
                    PortObjectItem::Int
                    );


    addPort(port1);
    addPort(m_resPort);
}

void TestEndNode::solute()
{

    int res=m_resPort->portValue().toInt();


    qDebug()<<"EndNode : value="<<res;
    //emit stopSolution();

}
