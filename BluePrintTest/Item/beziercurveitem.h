#ifndef BEZIERCURVEITEM_H
#define BEZIERCURVEITEM_H

#include <QGraphicsItem>


class BezierCurveItem : public QGraphicsItem
{
public:
    BezierCurveItem(const QPointF& startPoint, const QPointF& endPoint);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void UpdatePoint(const QPointF& startPoint, const QPointF& endPoint);

    QColor lineColor() const;
    void setLineColor(const QColor &newLineColor);

    unsigned int lineWidth() const;
    void setLineWidth(unsigned int newLineWidth);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e) override;

private:
    QColor m_lineColor;
    unsigned int m_lineWidth;

    QPointF m_start;
    QPointF m_end;
    QPointF m_controlPoint1;
    QPointF m_controlPoint2;
};

#endif // BEZIERCURVEITEM_H
