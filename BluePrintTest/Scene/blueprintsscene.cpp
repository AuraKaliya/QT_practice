#include "blueprintsscene.h"

BlueprintsScene::BlueprintsScene(QObject *parent)
    : QGraphicsScene{parent}
{
    preInit();
}

NodeManager *BlueprintsScene::getManager()
{
    return  m_nodeManager;
}

void BlueprintsScene::preInit()
{
    m_nodeManager=new NodeManager(this);
}
