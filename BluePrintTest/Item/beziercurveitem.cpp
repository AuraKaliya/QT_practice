#include "beziercurveitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>


BezierCurveItem::BezierCurveItem(const QPointF &startPoint, const QPointF &endPoint)
    : m_lineColor{Qt::blue},m_start(startPoint),m_end(endPoint)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable,true);
    setAcceptHoverEvents(true);
}

QRectF BezierCurveItem::boundingRect() const
{
    // 返回包围贝塞尔曲线的矩形
    qreal minX = qMin(qMin(m_start.x(), m_end.x()), qMin(m_controlPoint1.x(), m_controlPoint2.x()));
    qreal minY = qMin(qMin(m_start.y(), m_end.y()), qMin(m_controlPoint1.y(), m_controlPoint2.y()));
    qreal maxX = qMax(qMax(m_start.x(), m_end.x()), qMax(m_controlPoint1.x(), m_controlPoint2.x()));
    qreal maxY = qMax(qMax(m_start.y(), m_end.y()), qMax(m_controlPoint1.y(), m_controlPoint2.y()));
    return QRectF(minX, minY, maxX - minX, maxY - minY);
}

void BezierCurveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    setZValue(-1);

    if(m_start.x()>=m_end.x())
    {
        m_controlPoint1= QPointF (m_start.x() - 30, m_start.y()); // 偏离起点的第一个控制点
        m_controlPoint2= QPointF (m_end.x() +30, m_end.y());   // 偏离终点的第二个控制点
    }else
    {
        m_controlPoint1= QPointF (m_start.x() + 60, m_start.y()); // 偏离起点的第一个控制点
        m_controlPoint2= QPointF (m_end.x() -60, m_end.y());   // 偏离终点的第二个控制点
    }

    if(isSelected())
    {
        m_lineWidth=15;
    }else
    {
        m_lineWidth=8;
    }

    // 贝塞尔曲线
    QPainterPath bezierPath;
    bezierPath.moveTo(m_start);
    bezierPath.cubicTo(m_controlPoint1, m_controlPoint2, m_end);
    painter->setPen(QPen(m_lineColor, m_lineWidth));
    painter->drawPath(bezierPath);
}

void BezierCurveItem::UpdatePoint(const QPointF &startPoint, const QPointF &endPoint)
{
    m_start=startPoint;
    m_end=endPoint;
    update();
}

QColor BezierCurveItem::lineColor() const
{
    return m_lineColor;
}

void BezierCurveItem::setLineColor(const QColor &newLineColor)
{
    m_lineColor = newLineColor;
}

unsigned int BezierCurveItem::lineWidth() const
{
    return m_lineWidth;
}

void BezierCurveItem::setLineWidth(unsigned int newLineWidth)
{
    m_lineWidth = newLineWidth;
}

void BezierCurveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    QPainterPath bezierPath;
    bezierPath.moveTo(m_start);
    bezierPath.cubicTo(m_controlPoint1, m_controlPoint2, m_end);
    if (bezierPath.intersects(QRectF(e->pos(), QSizeF(m_lineWidth,m_lineWidth))))
        setSelected(true);
    else
        setSelected(false);
    e->ignore();
}
