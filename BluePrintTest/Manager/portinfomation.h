#ifndef PORTINFOMATION_H
#define PORTINFOMATION_H


#include "../Item/Node/nodeobjectitem.h"
#include "../Item/Port/portobjectitem.h"

class PortInfomation
{
public:
    PortInfomation();

    bool isEmpty();

    NodeObjectItem *node() const;
    void setNode(NodeObjectItem *newNode);

    PortObjectItem *port() const;
    void setPort(PortObjectItem *newPort);

private:
    NodeObjectItem* m_node=nullptr;
    PortObjectItem* m_port=nullptr;

};

#endif // PORTINFOMATION_H
