#ifndef TESTVALUENODE_H
#define TESTVALUENODE_H

#include <QObject>
#include "nodeobjectitem.h"

class TestValueNode : public NodeObjectItem
{
    Q_OBJECT
public:
    explicit TestValueNode(QObject *parent = nullptr,QGraphicsItem* itemParent=nullptr);
    void solute()override;
private:
    PortObjectItem* m_valuePort=nullptr;
signals:

};

#endif // TESTVALUENODE_H
