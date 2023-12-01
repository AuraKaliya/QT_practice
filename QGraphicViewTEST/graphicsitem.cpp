#include "graphicsitem.h"


GraphicsItem::GraphicsItem(QPixmap *pixmap, QGraphicsItem *parent):QGraphicsItem{parent}
{
    pix=*pixmap;
    setFlags(ItemIsMovable|ItemClipsToShape|ItemIsSelectable);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

QRectF GraphicsItem::boundingRect() const
{
    //return QRectF(-2-pix.width()/2,-2-pix.height()/2,pix.width(),pix.height());
    return QRectF(0,0,pix.width(),pix.height());
}

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //drawpixmap 使用GPU进行处理，而QLabel使用CPU处理（可能造成卡顿）
    //painter->drawPixmap(-pix.width()/2,-pix.height()/2,pix);

    painter->drawPixmap(0,0,pix);
    //QGraphicsItem::paint(painter,option,widget);
}

void GraphicsItem::show()
{
    qDebug()<<this<<" --- "<<pix.size();
}
