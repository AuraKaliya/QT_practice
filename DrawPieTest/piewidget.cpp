#include "piewidget.h"

#include <QBrush>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

PieWidget::PieWidget(QWidget *parent)
    : QWidget{parent}
{
    m_labelCount=6;
    m_innerLength=300;
    setMinimumSize(m_innerLength,m_innerLength);
}

PieWidget::PieWidget(int labelCount, int innerR, QWidget *parent):PieWidget(parent)
{
    m_labelCount=labelCount;
    m_innerLength=innerR;
    setMinimumSize(m_innerLength,m_innerLength);
}

void PieWidget::paintEvent(QPaintEvent *e)
{
    int perAngel=360/m_labelCount;
    int offsetAngel=perAngel/2;
    int offsetLength=(m_centerRect.width()-m_innerRect.width())/4 + m_innerRect.width()/2;
    QPoint O(width()/2,height()/2);
    m_labelCenterPointList.clear();

    for(int i=0;i < m_labelCount;++i)
    {
        QPoint p=getRotatePoint(O,offsetLength,offsetAngel+i*perAngel);
        m_labelCenterPointList.append(p);
    }

    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QPen rectPen;
    rectPen.setWidth(4);
    rectPen.setColor(Qt::black);

    QPen pointPen;
    pointPen.setWidth(20);
    pointPen.setColor(Qt::blue);


    QPen sectorPen;
    sectorPen.setWidth(4);
    sectorPen.setColor(Qt::green);

    p.setPen(rectPen);
    p.drawRect(m_centerRect);

    p.setBrush(QBrush(QColor("red")));
    p.setPen(sectorPen);
    for(int i=0;i<m_labelCenterPointList.size();++i)
    {
        p.drawPie(m_centerRect,(i*perAngel)*16,perAngel*16);
    }

    if(m_nowIndex!=-1)
    {
        p.setBrush(QBrush(QColor("pink")));
        p.drawPie(m_centerRect,(m_nowIndex*perAngel)*16,perAngel*16);
    }

    p.setBrush(QBrush(QColor("white")));
    p.drawEllipse(m_innerRect);

    p.setPen(pointPen);

    for(auto it: m_labelCenterPointList)
    {
        p.drawPoint(it);
    }
}

void PieWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    int a=qMin(width(),height());
    m_centerRect=QRect((width()-a)/2,(height()-a)/2,a,a);
    m_innerRect=QRect((width()-m_innerLength)/2,(height()-m_innerLength)/2,m_innerLength,m_innerLength);
}

void PieWidget::enterEvent(QEnterEvent *e)
{
    setMouseTracking(true);
}

void PieWidget::leaveEvent(QEvent *e)
{
    setMouseTracking(false);
}

void PieWidget::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}

void PieWidget::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
    int flag=sectorContains(QPoint(e->pos().x()-m_centerRect.x(),e->pos().y()-m_centerRect.y()),m_centerRect,m_labelCount);
    m_nowIndex=flag;
    update();
}

int PieWidget::innerLength() const
{
    return m_innerLength;
}

void PieWidget::setInnerLength(int newInnerLength)
{
    m_innerLength = newInnerLength;
    setMinimumSize(m_innerLength,m_innerLength);
}

int PieWidget::sectorContains(QPoint p, QRect roundRect, int labelCount, int offsetAngel)
{
    int res=-1;
    int perAngel=360/m_labelCount;
    int r=roundRect.width()/2;
    QPoint O(roundRect.width()/2,roundRect.height()/2);
    QPoint v=p-O;
    double trueLength = std::sqrt(std::pow(v.x(), 2) + std::pow(v.y(), 2));
    if(trueLength<=r)
    {
        //计算角度
        int angel=qAtan2(v.y(),v.x())/PieWidget::Pi*180;
        if(angel<0)
        {
            angel=-angel;
        }
        else
        {
            angel=360-angel;
        }
        res=angel/perAngel;
    }
    else
    {
        res=-1;
    }

    return res;
}

int PieWidget::labelCount() const
{
    return m_labelCount;
}

void PieWidget::setLabelCount(int newLabelCount)
{
    m_labelCount = newLabelCount;
    m_labelStateList.clear();
    m_nowIndex=-1;
    for(int i=0;i<m_labelCount;i++)
    {
        m_labelStateList.append(LabelState::Unhover);
    }
}

QPoint PieWidget::getRotatePoint(QPoint O, int r, double angel)
{
    return QPoint(O.x()+r*qSin((angel+90)*PieWidget::Pi/180.0),O.y()+r*qCos((angel+90)*PieWidget::Pi/180.0));
}
