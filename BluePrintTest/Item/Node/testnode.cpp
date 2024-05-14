#include "testnode.h"



TestNode::TestNode(QObject *parent, QGraphicsItem *itemParent)
    :NodeObjectItem(parent,itemParent)
{
    setNodeType(SolveNode);

    PortObjectItem* port1=new PortObjectItem(this);

    port1 ->initPort("TestPort1",
                    PortObjectItem::Input,
                    PortObjectItem::Int
                    );

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

    PortObjectItem* port4=new PortObjectItem(this);

    port4 ->initPort("TestPort4",
                    PortObjectItem::Output,
                    PortObjectItem::Bool
                    );

    addPort(port1);
    addPort(port2);
    addPort(port3);
    addPort(port4);

}
