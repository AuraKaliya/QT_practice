#include "item2dmap.h"

Item2DMap::Item2DMap(QPixmap *pixmap, QGraphicsItem *parent):GraphicsItem{pixmap,parent}
{

}

void Item2DMap::init(int xscale, int yscale, QMap<int, QPixmap *> map, int defaultIdx)
{
    xinterval= ((double)pix.width())/xscale;
    yinterval=((double)pix.height())/yscale;

    m_pixDictionary=map;

    for(int i=0;i<yscale;i++)
    {
        QVector<QPixmap*> tmpVector;
        for(int j=0;j<xscale;j++)
        {
            QPixmap* pix=map[defaultIdx];
            *pix = pix->scaled(xinterval,yinterval);
            tmpVector.append(pix);
        }
        m_mapPix.append(tmpVector);
    }

    initState=true;
}

void Item2DMap::setPix(int x,int y, int idx)
{
   m_mapPix[y][x]=m_pixDictionary.find(idx).value();
    update();
}

void Item2DMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   GraphicsItem::paint(painter,option,widget);
   if(initState)
   {
        int i=0;
        for(auto it:m_mapPix)
        {
            int j=0;
            for(auto it2:it)
            {
                painter->drawPixmap(i*xinterval,j*yinterval,*it2);
                j++;
            }
            i++;
        }
   }

}
