#ifndef TESTSIGNALNODE_H
#define TESTSIGNALNODE_H

#include <QObject>
#include "nodeobjectitem.h"
#include "../../Object/testobject.h"

class TestSignalNode : public NodeObjectItem
{
    Q_OBJECT
public:
    explicit TestSignalNode(QObject *parent = nullptr,QGraphicsItem* itemParent=nullptr);
    void solute()override;

    TestObject *linkObj() const;
    void setLinkObj(TestObject *newLinkObj);

private:
    PortObjectItem* m_objLinkValuePort=nullptr;
    PortObjectItem* m_outValuePort=nullptr;
    TestObject* m_linkObj=nullptr;
signals:

};

#endif // TESTSIGNALNODE_H
