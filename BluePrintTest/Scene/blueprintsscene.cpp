#include "blueprintsscene.h"

BlueprintsScene::BlueprintsScene(QObject *parent)
    : QGraphicsScene{parent}
{
    preInit();
}



void BlueprintsScene::preInit()
{
    m_nodeManager=new NodeManager(this);

}
