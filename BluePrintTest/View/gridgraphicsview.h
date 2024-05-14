#ifndef BLUEPRINTVIEW_H
#define BLUEPRINTVIEW_H

#include <QWidget>
#include <QMenu>
#include <QtTypes>
#include <QPainter>
#include <QAction>
#include <QWheelEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

#include "../Scene/blueprintsscene.h"
class GridGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GridGraphicsView(QWidget *parent = nullptr);
    explicit GridGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);

    void setScaleRange(double minRange ,double maxRange);

    double nowScale() const;
    void setNowScale(double newNowScale);

    void scaleUp();
    void scaleDown();

    void updateSceneToCenter();
protected:
    void mouseMoveEvent(QMouseEvent* e)override;
    void mousePressEvent(QMouseEvent* e)override;
    void mouseReleaseEvent(QMouseEvent *e)override;
    void drawBackground(QPainter* p,const QRectF& r)override;
    void wheelEvent(QWheelEvent *e)override;
    void showEvent(QShowEvent *e) override;
private:
    void preInit();
    void updateScale();
private:
    QPoint m_currentPos;

    QPoint m_startPos;
    QPoint m_endPos;

    double m_minScale;
    double m_maxScale;
    double m_nowScale;
    bool m_moveSceneFlag;


    QPainter* m_backgroundPainter=nullptr;


signals:
    void nowScaleChanged(double);
};

#endif // BLUEPRINTVIEW_H
