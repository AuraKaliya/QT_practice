#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>


class GraphicsItem : public QGraphicsItem
{

public:
    GraphicsItem(QPixmap *pixmap,QGraphicsItem* parent=nullptr);
    QRectF  boundingRect() const;    //QRect绘制时除了topleft 都会往内部偏移1像素点，而QRectF是用浮点数表示区域，不会出现这个问题
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) ;
    void show();
protected:
    QPixmap pix;    //作为图元显示对应图片
};

#endif // GRAPHICSITEM_H
