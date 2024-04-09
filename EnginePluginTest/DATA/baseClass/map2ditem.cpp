#include "map2ditem.h"

Map2DItem::Map2DItem(GameObject*obj,QPixmap pix,QObject *parent)
    : GameObjectItem{obj,pix,parent}
{



}

void Map2DItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(state())
    {
        GameObjectItem::paint(painter,option,widget);
        if(m_initState)
        {
            qDebug()<<"map2dItem paint";
            // qDebug()<<m_mapPix;
            qDebug()<<m_mapPix;
            //qDebug()<<"check0: Map2DItem"<<(int)&(*this);
            int i=0;
            for(auto it:m_mapPix)
            {
                int j=0;
                for(auto it2:it)
                {
                    painter->drawPixmap(i*(m_xInterval),j*(m_yInterval),it2);
                    j++;
                }
                i++;
            }
        }
    }
}


void Map2DItem::initMap(int xScale, int yScale, QMap<int, QPixmap *> map, int defaultIdx)
{

    m_xScale=xScale;
    m_yScale=yScale;

//    m_xInterval=( ((double)m_pixRect.width())/m_xScale)-1.0;
//    m_yInterval=(((double)m_pixRect.height())/m_yScale)-1.0;

    m_pixDictionary=map;
    m_defaultIdx=defaultIdx;


    for(int i=0;i<m_yScale;i++)
    {
        QVector<int> tmpVector;
        for(int j=0;j<m_xScale;j++)
        {
            tmpVector.append(m_defaultIdx);
        }
        m_mapIdx.append(tmpVector);
    }
    updateMap();

    connect(this,&GameObjectItem::resetPixScale,this,&Map2DItem::updateMap);


    m_initState=true;

}


void Map2DItem::setPix(int x, int y, int idx)
{
    m_mapPix[y][x]=QPixmap(*m_pixDictionary.find(idx).value());
    update();
}


void Map2DItem::setScale(int xScale, int yScale)
{
    m_xScale=xScale;
    m_yScale=yScale;
    m_mapIdx.resize(m_yScale);
    for(auto it:m_mapIdx)
    {
        it.resize(m_xScale);
    }
    updateMap();
}

void Map2DItem::setMapSource(QMap<int, QPixmap *> map)
{
    m_pixDictionary=map;
    updateMap();
}

void Map2DItem::updateMap()
{
    qDebug()<<"Map2DItem::updateMap";
    m_xInterval= ((double)m_pixRect.width())/m_xScale;
    m_yInterval=((double)m_pixRect.height())/m_yScale;

    //在重设后，需要对Map进行更新
    //对scale进行更新
    for(auto it:m_mapPix)
    {
        it.clear();
    }
    m_mapPix.clear();

    for(int i=0;i<m_yScale;i++)
    {
        QVector<QPixmap> tmpVector;
        for(int j=0;j<m_xScale;j++)
        {
            QPixmap pix=QPixmap(*m_pixDictionary[m_mapIdx[j][i]]);
            //qDebug()<<"pixInterval:"<<m_xInterval<<m_yInterval;
            pix = pix.scaled(m_xInterval,m_yInterval);
            //qDebug()<<"pixSize:"<<pix->size();
            tmpVector.append(pix);
        }
        m_mapPix.append(tmpVector);
    }

    update();
}

void Map2DItem::resetMap(QVector<QVector<int> > vector)
{

    qDebug()<<"resetMap"<<vector;
    qDebug()<<"check0:"<<m_mapPix;
    m_mapIdx=vector;
    for(auto it:m_mapPix)
    {
        it.clear();
    }
    m_mapPix.clear();

    for(int i=0;i<m_yScale;i++)
    {
        QVector<QPixmap> tmpVector;
        for(int j=0;j<m_xScale;j++)
        {

            QPixmap pix=QPixmap(*m_pixDictionary[vector[j][i]]);
            //qDebug()<<"pixInterval:"<<m_xInterval<<m_yInterval;

            pix = pix.scaled(m_xInterval,m_yInterval);
            //qDebug()<<"pixSize:"<<pix->size();

            tmpVector.append(pix);
        }
        m_mapPix.append(tmpVector);
    }
    qDebug()<<"check1:"<<m_mapPix;

    update();
}


