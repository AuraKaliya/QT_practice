#ifndef TESTNODE_H
#define TESTNODE_H

#include <QObject>
#include "nodeobjectitem.h"
class TestNode : public NodeObjectItem
{
    Q_OBJECT
public:
    explicit TestNode(QObject *parent = nullptr,QGraphicsItem* itemParent=nullptr);

signals:

};

#endif // TESTNODE_H
