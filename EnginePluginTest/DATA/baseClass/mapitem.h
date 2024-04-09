#ifndef MAPITEM_H
#define MAPITEM_H

#include <QObject>
#include <DATA/baseClass/gameobjectitem.h>
#include <DATA/baseClass/dynamicitem.h>

/*
1. 地图类型的Item
    额外拥有地图容量X*Y
    拥有基本图Pix（即空容量时显示的内容）
    拥有子图数count=X*Y
    拥有子图Vector<Pix*>  size=count
    初始化后生成子Item，根据容量进行填充。
    子Item不可选中，仅通过mapItem提供的方法进行定位和修改。
    子item的参数由MapItem进行规划确定
*/

class MapItem : public GameObjectItem
{
    Q_OBJECT
public:
    explicit MapItem(GameObject *obj, QPixmap pix,QObject *parent=nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) override;
    void initMap(int xScale, int yScale, QMap<int,PixSource*> map, int defaultIdx,int xInterval=32,int yInterval=32);
    void setPix(int x, int y, int idx);
    void setScale(int xScale,int yScale);
    void updateMap();

private:
    QVector<QVector<QPixmap> > m_mapPix{};
    QVector<QVector<int> > m_mapIdx{};
    int m_defaultIdx=0;
    int m_xScale=5;
    int m_yScale=5;
    bool m_initState=false;
    double m_xInterval=0;
    double m_yInterval=0;


    QVector<QVector<DynamicItem *> >m_itemList{};

    int m_nowX=0;
    int m_nowY=0;







signals:

};

#endif // MAPITEM_H
