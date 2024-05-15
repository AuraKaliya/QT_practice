#include "linkinformation.h"

LinkInformation::LinkInformation()
    :m_linkNode1ID(0),m_linkNode2ID(0)
{

}

NodeObjectItem *LinkInformation::linkNode1() const
{
    return m_linkNode1;
}

void LinkInformation::setLinkNode1(NodeObjectItem *newLinkNode1)
{
    m_linkNode1 = newLinkNode1;
}

NodeObjectItem *LinkInformation::linkNode2() const
{
    return m_linkNode2;
}

void LinkInformation::setLinkNode2(NodeObjectItem *newLinkNode2)
{
    m_linkNode2 = newLinkNode2;
}

PortObjectItem *LinkInformation::linkPort1() const
{
    return m_linkPort1;
}

void LinkInformation::setLinkPort1(PortObjectItem *newLinkPort1)
{
    m_linkPort1 = newLinkPort1;
}

PortObjectItem *LinkInformation::linkPort2() const
{
    return m_linkPort2;
}

void LinkInformation::setLinkPort2(PortObjectItem *newLinkPort2)
{
    m_linkPort2 = newLinkPort2;
}

BezierCurveItem *LinkInformation::linkLine() const
{
    return m_linkLine;
}

void LinkInformation::setLinkLine(BezierCurveItem *newLinkLine)
{
    m_linkLine = newLinkLine;
}
