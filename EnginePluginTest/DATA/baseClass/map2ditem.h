#ifndef MAP2DITEM_H
#define MAP2DITEM_H

#include <QObject>
#include <DATA/baseClass/gameobjectitem.h>
#include <QMap>
#include <QVector>

class Map2DItem : public GameObjectItem
{
    Q_OBJECT
public:
    explicit Map2DItem(GameObject*obj,QPixmap pix,QObject *parent=nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) override;
    void initMap(int xScale,int yScale,QMap<int,QPixmap*> map,int defaultIdx);

    void setPix(int x, int y, int idx);
    void setScale(int xScale,int yScale);
    void setMapSource(QMap<int,QPixmap*> map);
    void updateMap();
    void resetMap(QVector<QVector<int> > vector);

private:
    QVector<QVector<QPixmap> > m_mapPix{};
    QVector<QVector<int> > m_mapIdx{};
    int m_defaultIdx=0;
    int m_xScale=5;
    int m_yScale=5;
    bool m_initState=false;
    double m_xInterval=0;
    double m_yInterval=0;


signals:

};

#endif // MAP2DITEM_H
