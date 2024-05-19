#ifndef TESTENDNODE_H
#define TESTENDNODE_H

#include <QObject>
#include "nodeobjectitem.h"

class TestEndNode : public NodeObjectItem
{
    Q_OBJECT
public:
    explicit TestEndNode(QObject *parent = nullptr,QGraphicsItem* itemParent=nullptr);
    void solute()override;



private:
    PortObjectItem* m_resPort=nullptr;
signals:

};

#endif // TESTENDNODE_H
