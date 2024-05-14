#include "blueprintsview.h"

BlueprintsView::BlueprintsView(QWidget *parent)
    : GridGraphicsView{parent}
{

}

BlueprintsView::BlueprintsView(QGraphicsScene *scene, QWidget *parent)
    : GridGraphicsView(scene,parent)
{

}
