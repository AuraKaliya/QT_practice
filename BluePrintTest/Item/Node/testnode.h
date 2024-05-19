#ifndef TESTNODE_H
#define TESTNODE_H

#include <QObject>
#include "nodeobjectitem.h"
class TestNode : public NodeObjectItem
{
    Q_OBJECT
public:
    explicit TestNode(QObject *parent = nullptr,QGraphicsItem* itemParent=nullptr);
    void solute()override;
private:
    //add
    PortObjectItem* m_inPort1;
    PortObjectItem* m_inPort2;
    PortObjectItem* m_outPort;

signals:

};

#endif // TESTNODE_H
