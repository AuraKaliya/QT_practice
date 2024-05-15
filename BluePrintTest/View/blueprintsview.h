#ifndef BLUEPRINTSVIEW_H
#define BLUEPRINTSVIEW_H

#include <QWidget>
#include "gridgraphicsview.h"
#include "../Item/beziercurveitem.h"

class BlueprintsView : public GridGraphicsView
{
    Q_OBJECT
public:
    explicit BlueprintsView(QWidget *parent = nullptr);
    explicit BlueprintsView(QGraphicsScene *scene, QWidget *parent = nullptr);


    BezierCurveItem* addLinkLine(QPointF startPoint,QPointF endPoint);
protected:
    void mouseMoveEvent(QMouseEvent* e)override;
    void mousePressEvent(QMouseEvent* e)override;
    void mouseReleaseEvent(QMouseEvent *e)override;
private:
    void preInit();
private:
    BezierCurveItem* m_previewLine=nullptr;


    PortObjectItem* m_nowStartPort=nullptr;
    QColor m_lineColor;
    bool m_drawFlag;
signals:

};

#endif // BLUEPRINTSVIEW_H
