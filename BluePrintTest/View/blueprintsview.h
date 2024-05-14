#ifndef BLUEPRINTSVIEW_H
#define BLUEPRINTSVIEW_H

#include <QWidget>
#include "gridgraphicsview.h"

class BlueprintsView : public GridGraphicsView
{
    Q_OBJECT
public:
    explicit BlueprintsView(QWidget *parent = nullptr);
    explicit BlueprintsView(QGraphicsScene *scene, QWidget *parent = nullptr);


signals:

};

#endif // BLUEPRINTSVIEW_H
