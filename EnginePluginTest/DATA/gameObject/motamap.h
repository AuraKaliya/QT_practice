#ifndef MOTAMAP_H
#define MOTAMAP_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "../baseClass/gameobject.h"
#include "../baseClass/componentobject.h"
#include "../model/model2dmap.h"
#include "../model/modeltower.h"
#include "../model/model2dobjectmap.h"

#include <TOOL/template/Registor.hpp>
/*
魔塔地图
标准JSON格式

地图矩阵MapMatrix
## 0-1023 不可达区域
## 其余 可达区域

可达矩阵ValiedErea
## 0：不可达
## 1：可达

资源格式
【1-9】1位         --资源类别
【00-99】2位       --资源子类
【0000-9999】4位   --资源编号

9：GameObject类
00：地图类
0001：由文档指定资源编号 +自动生成时按照最大编号+1进行指定

MotaMap{
"Id":9000001,
"ClassName":"MotaMap",
"MapLayer":1,
"MapSize":[5,5],
"ValiedErea":[  [[1,1,0,0,0],
                [0,1,0,0,0],
                [0,1,1,0,0],
                [0,0,1,0,0],
                [0,0,1,1,0]]   ],
"MapMatrix":[   [[1024,1024,0,24,0],
                [0,1024,0,0,0],
                [25,1024,1024,0,0],
                [0,0,1024,58,0],
                [68,68,1024,1024,68]]   ],
"MapLayerLinkedList":[1,4,2,0,3]

}

*/

/*
可优化选项
at 和[]
QVector和直接数组
memset
*/

class MotaMap : public GameObject
{
    Q_OBJECT
    Q_PROPERTY(int mapNetWidth READ mapNetWidth WRITE setMapNetWidth NOTIFY mapNetWidthChanged)
    Q_PROPERTY(int mapNetHeight READ mapNetHeight WRITE setMapNetHeight NOTIFY mapNetHeightChanged)
public:
    explicit MotaMap(QObject *parent = nullptr);
    void init(const QJsonObject * data)override;
    void tick()override;
    void solutePacketData(InsPacketData*data)override;
    void changeElement(unsigned int layer, int x,int y,int index);
    void changeElement(unsigned int layer, int x,int y,int index,bool valiedFlag);
    int getNowLayer();
    QVector<QVector<int> > getMap(int layer);
    QVector<QVector<bool> > getValiedMap(int layer);
    QVector<int> getTowerLink();
    void nextLayer();
    int getNextLayer();
    int getPreLayer();
    void nextLayer(int layer);
    bool elementIsValied(int layer,int x,int y);
    QJsonObject getItemData()override;
    static void changeElement(GameObject* me,QVariant v);

    void  operator <<(GameObject& obj);
    QPoint getElementPoint(int layer,int x,int y);

    QPair<int,int> getMapInterval(int layer);

    QPair<int,QPair<int,int>> getHeroPos();
    QPair<int,QPair<int,int>> findObjectPos(int id);
    void objectMove(int layer,int oldX,int oldY,int newX,int newY);

    void setItemPos(int layer,int x, int y, int itemId);







    QPair<int,int> getUpPos();
    QPair<int,int> getDownPos();

    QPair<int,int> getUpPos(int layer);
    QPair<int,int> getDownPos(int layer);
    void heroMoveToNextLayer(int layer,int x,int y);

    void heroChanged(int newId);
    void addObject(int layer,int x,int y,int index);
    void delObject(int index);

    QVector<Model2DObjectMap *> objectMap() const;
    Model2DObjectMap* getObjectMapByLayer(int layer);
    //创建-设置相关
    /*
        1. 设置加载图片 设置默认填充 设置地图大小
        2.
    */


    int mapNetWidth() const;
    void setMapNetWidth(int newMapNetWidth);

    int mapNetHeight() const;
    void setMapNetHeight(int newMapNetHeight);

private:
    QVector<Model2DMap*> m_map;
    QVector<Model2DObjectMap*> m_objectMap;
    ModelTower* m_tower;
    QMap<int,int>m_tilePixDictionary;
    int m_mapNetWidth;
    int m_mapNetHeight;

signals:
    void linkDemo();
    void objectDeleted(int);
    void objectMoved(int id,int x,int y);
    void mapNetWidthChanged();
    void mapNetHeightChanged();
};
REGISTER_OBJECT(MotaMap,GameObject)
#endif // MOTAMAP_H
