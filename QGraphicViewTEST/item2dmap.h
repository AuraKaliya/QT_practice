#ifndef ITEM2DMAP_H
#define ITEM2DMAP_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <graphicsitem.h>
#include <QVector>
#include <QMap>

class Item2DMap: public GraphicsItem
{
public:
    Item2DMap(QPixmap *pixmap,QGraphicsItem* parent=nullptr);
    void init(int xscale,int yscale,QMap<int,QPixmap*> map,int defaultIdx);
    void setPix(int x,int y,int idx);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) ;
private:

    QMap<int,QPixmap* > m_pixDictionary;
    QVector<QVector <QPixmap*> > m_mapPix{};
    int xscale=10;
    bool initState=false;
    double xinterval=0;
    double yinterval=0;
};

#endif // ITEM2DMAP_H
