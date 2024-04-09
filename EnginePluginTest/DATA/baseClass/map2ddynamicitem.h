#ifndef MAP2DDYNAMICITEM_H
#define MAP2DDYNAMICITEM_H

#include <QObject>
#include <DATA/baseClass/gameobjectitem.h>
#include <QMap>
#include <QVector>
#include <DATA/baseClass/dynamicitem.h>

class Map2DDynamicItem : public GameObjectItem
{
    Q_OBJECT
public:
    explicit Map2DDynamicItem(GameObject*obj,QPixmap pix,QObject *parent=nullptr);
    void initMap(int xScale,int yScale,QMap<int,PixSource*> map,int defaultIdx);
signals:

};

#endif // MAP2DDYNAMICITEM_H
