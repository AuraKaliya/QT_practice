#ifndef LINKLINEINFORMATION_H
#define LINKLINEINFORMATION_H

#include "../Item/beziercurveitem.h"
#include "../Item/Node/nodeobjectitem.h"


//=============待更新==================
//  代码结构上可以进行优化
//=============待更新==================
class LinkInformation
{
public:
    LinkInformation();



    NodeObjectItem *linkNode1() const;
    void setLinkNode1(NodeObjectItem *newLinkNode1);

    NodeObjectItem *linkNode2() const;
    void setLinkNode2(NodeObjectItem *newLinkNode2);

    PortObjectItem *linkPort1() const;
    void setLinkPort1(PortObjectItem *newLinkPort1);

    PortObjectItem *linkPort2() const;
    void setLinkPort2(PortObjectItem *newLinkPort2);



    BezierCurveItem *linkLine() const;
    void setLinkLine(BezierCurveItem *newLinkLine);

private:

    NodeObjectItem* m_linkNode1=nullptr;
    NodeObjectItem* m_linkNode2=nullptr;

    PortObjectItem* m_linkPort1=nullptr;
    PortObjectItem* m_linkPort2=nullptr;

    BezierCurveItem* m_linkLine=nullptr;

    unsigned int m_linkNode1ID;
    unsigned int m_linkNode2ID;



};

#endif // LINKLINEINFORMATION_H
