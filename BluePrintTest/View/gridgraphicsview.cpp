#include "gridgraphicsview.h"

GridGraphicsView::GridGraphicsView(QWidget *parent)
:QGraphicsView{parent}
{
    preInit();
}

GridGraphicsView::GridGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView{scene,parent}
{
    preInit();
}

void GridGraphicsView::setScaleRange(double minRange, double maxRange)
{
    if (maxRange < minRange)
        std::swap(maxRange, minRange);
    minRange = std::max(0.0, minRange);
    maxRange = std::max(0.0, maxRange);
    updateScale();
}

void GridGraphicsView::mouseMoveEvent(QMouseEvent *e)
{

    m_currentPos=e->pos();

    m_endPos=m_currentPos;

    QGraphicsView::mouseMoveEvent(e);
}

void GridGraphicsView::mousePressEvent(QMouseEvent *e)
{

    m_startPos=e->pos();
    m_currentPos=m_startPos;
    m_endPos=m_currentPos;

    // 为右键
    if(e->buttons() ==Qt::RightButton)
    {

    }

    // 为左键
    if(e->buttons()==Qt::LeftButton)
    {

    }
    QGraphicsView::mousePressEvent(e);
}

void GridGraphicsView::mouseReleaseEvent(QMouseEvent *e)
{
    QGraphicsView::mouseReleaseEvent(e);
    m_currentPos=e->pos();
    m_endPos=m_currentPos;

    // 为左键   释放
    if (e->buttons() == Qt::LeftButton)
    {

    }

}

void GridGraphicsView::drawBackground(QPainter *p, const QRectF &r)
{
    QGraphicsView::drawBackground(p, r);
    auto drawGrid = [&](double gridStep) {
        QRect windowRect = rect();
        QPointF tl = mapToScene(windowRect.topLeft());
        QPointF br = mapToScene(windowRect.bottomRight());

        double left = std::floor(tl.x() / gridStep - 0.5);
        double right = std::floor(br.x() / gridStep + 1.0);
        double bottom = std::floor(tl.y() / gridStep - 0.5);
        double top = std::floor(br.y() / gridStep + 1.0);

        // vertical lines
        for (int xi = int(left); xi <= int(right); ++xi) {
            QLineF line(xi * gridStep, bottom * gridStep, xi * gridStep, top * gridStep);

            p->drawLine(line);
        }

        // horizontal lines
        for (int yi = int(bottom); yi <= int(top); ++yi) {
            QLineF line(left * gridStep, yi * gridStep, right * gridStep, yi * gridStep);
            p->drawLine(line);
        }
    };


    QPen pfine(QColor(60,60,60), 1.0);

    p->setPen(pfine);
    drawGrid(15);

    QPen pen(QColor(25,25,25), 1.0);

    p->setPen(pen);
    drawGrid(150);

}


void GridGraphicsView::wheelEvent(QWheelEvent *e)
{
    QPoint delta = e->angleDelta();

    if (delta.y() == 0) {
        e->ignore();
        return;
    }
    double const d = delta.y() / std::abs(delta.y());
    if (d > 0.0)
        scaleUp();
    else
        scaleDown();
}

void GridGraphicsView::showEvent(QShowEvent *e)
{
    QGraphicsView::showEvent(e);

    updateSceneToCenter();
}

void GridGraphicsView::preInit()
{
    //=========================设置View的模式========================
    //   最大选取模式
    setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);
    setRenderHints(
                     QPainter::Antialiasing
                   | QPainter::SmoothPixmapTransform
                   | QPainter::TextAntialiasing
                   | QPainter::LosslessImageRendering
                   );

    //转换时规定鼠标下的点为锚点
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    //关闭scrollbar
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //缓冲背景
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    //启用功能
    setDragMode(QGraphicsView::ScrollHandDrag);
    //setDragMode(QGraphicsView::RubberBandDrag);

    setAcceptDrops(true);
    //=========================设置View的模式========================

    //=========================初始化场景========================
    if(! scene())
    {
        BlueprintsScene *s=new BlueprintsScene();
        setScene(s);
        int maxSize=1000;
        setSceneRect(-maxSize,-maxSize,2*maxSize,2*maxSize);
    }
    //=========================初始化场景========================

    //===============其他设置=============
    m_moveSceneFlag=false;
    //m_backgroundPainter=new QPainter(this->viewport());
    //m_backgroundPainter->setBrush(QColor(53,53,53));

    setBackgroundBrush(QColor(53,53,53));

    m_nowScale=1;
    setScaleRange(0.3,2);
    //===============其他设置=============
}

void GridGraphicsView::updateScale()
{
    m_nowScale = std::max(m_minScale, std::min(m_maxScale, m_nowScale));

    if (m_nowScale <= 0)
        return;

    if (m_nowScale == transform().m11())
        return;

    QTransform matrix;
    matrix.scale(m_nowScale, m_nowScale);
    setTransform(matrix, false);

    emit nowScaleChanged(m_nowScale);
}

double GridGraphicsView::nowScale() const
{
    return m_nowScale;
}

void GridGraphicsView::setNowScale(double newNowScale)
{
    m_nowScale = newNowScale;
    updateScale();
}

void GridGraphicsView::scaleUp()
{
    double const step = 1.2;
    double const factor = std::pow(step, 1.0);

    if (m_minScale > 0) {
        QTransform t = transform();
        t.scale(factor, factor);
        if (t.m11() >= m_minScale) {

            setNowScale(t.m11());
            return;
        }
    }

    scale(factor, factor);
    emit nowScaleChanged(transform().m11());
}

void GridGraphicsView::scaleDown()
{
    double const step = 1.2;
    double const factor = std::pow(step, -1.0);

    if (m_minScale > 0) {
        QTransform t = transform();
        t.scale(factor, factor);
        if (t.m11() <= m_minScale) {
             setNowScale(t.m11());
            return;
        }
    }
    scale(factor, factor);
    emit nowScaleChanged(transform().m11());
}

void GridGraphicsView::updateSceneToCenter()
{
    if (scene()) {
        scene()->setSceneRect(QRectF());

        QRectF sceneRect = scene()->sceneRect();

        if (sceneRect.width() > this->rect().width() || sceneRect.height() > this->rect().height()) {
            fitInView(sceneRect, Qt::KeepAspectRatio);
        }

        centerOn(sceneRect.center());
    }

}

