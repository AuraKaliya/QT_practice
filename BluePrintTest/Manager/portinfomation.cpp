#include "portinfomation.h"

PortInfomation::PortInfomation()
{

}

bool PortInfomation::isEmpty()
{
    return (!m_node || !m_port);
}

NodeObjectItem *PortInfomation::node() const
{
    return m_node;
}

void PortInfomation::setNode(NodeObjectItem *newNode)
{
    m_node = newNode;
}

PortObjectItem *PortInfomation::port() const
{
    return m_port;
}

void PortInfomation::setPort(PortObjectItem *newPort)
{
    m_port = newPort;
}
