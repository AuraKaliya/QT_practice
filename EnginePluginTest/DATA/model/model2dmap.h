#ifndef MODEL2DMAP_H
#define MODEL2DMAP_H

#include <QObject>
#include <QPoint>
#include <QVector>
#include "../baseClass/componentobject.h"


/*
2DMap模型，具有2D地图描述的最小接口。
--设置地图大小
--设置地图可达矩阵
--询问某点可否到达
--设置地图内容矩阵
--设置阈值
--更新可达矩阵

##阈值可用set进行替代，后续可更新变动式的查询是否可达（通过询问集合该目标id是否在内）。
*/


//class Model2DMap : public ComponentObject
//{
//    Q_OBJECT

////    Q_PROPERTY(QVector<QVector <int> > mapMatrix READ getMapMatrix WRITE setMapMatrix NOTIFY mapMatrixChanged)
////    Q_PROPERTY(QVector<QVector<bool> > valiedMatrix READ getValiedMatrix WRITE setValiedMatrix NOTIFY valiedMatrixChanged)
////    Q_PROPERTY(QPair<int,int> mapSize READ getMapSize WRITE setMapSize NOTIFY mapSizeChanged)

//    Q_PROPERTY(int mapWidth READ getMapWidth WRITE setMapWidth NOTIFY mapWidthChanged)
//    Q_PROPERTY(int mapHeight READ getMapHeight WRITE setMapHeight NOTIFY mapHeightChanged)
//    //Q_PROPERTY(int mapDeFault READ getMapDeFault WRITE setMapDeFault NOTIFY mapDeFaultChanged)
//public:

//    explicit Model2DMap(QObject *parent = nullptr);
//    void tick()override;
//    void setMapSize(const unsigned int& width,const unsigned int& height);
//    void setMapSize(QPair<int,int>newMapSize);
//    virtual void setValiedErea( const QVector<QVector <bool> >& valiedMatrix);
//    virtual bool pointIsActived(const int& x,const int& y);
//    void setMapMatrix(const QVector<QVector <int> >& mapMatrix);
//    virtual void updateValiedEreaByMap();

//    void changeElement(int x,int y,int newIndex,bool valied=true);
//    QVector<QVector<int> > getMapMatrix() ;
//    QVector<QVector<bool> > getValiedMatrix() const;
//    void setValiedMatrix(const QVector<QVector<bool> > &newValiedMatrix);

//    QPair<int, int> getMapSize() const;

//    int getMapWidth() const;
//    void setMapWidth(int newMapWidth);

//    int getMapHeight() const;
//    void setMapHeight(int newMapHeight);

//    int getMapDeFault() const;
//    void setMapDeFault(int newMapDeFault);

//private:

//    QVector<QVector <bool> > m_valiedMatrix;

//    QVector<QVector <int> > m_MapMatrix;

//    QVector<QVector<int> > m_mapMatrix;

//    QPair<int, int> m_mapSize;

//    int m_mapWidth;

//    int m_mapHeight;

//    int m_mapDeFault;



//signals:

//    void mapMatrixChanged();
//    void valiedMatrixChanged();
//    void mapSizeChanged();
//    void mapWidthChanged();
//    void mapHeightChanged();
//    void mapDeFaultChanged();
//};

//REGISTER_OBJECT(Model2DMap,ComponentObject)













/*
----
    mapWidth
    mapHeight
    mapRealWidth
    mapRealHeight
----
QVector<QVector<int> > mapMatrix
QVector<QVector<int> > valiedMatrix
int perElementSize
----
get / set
----
isValied(int x,int y)
setElement(int x,int y,int value)
setElementValied(int x,int y,bool valied)



*/


class Model2DMap : public ComponentObject
{
    Q_OBJECT

    Q_PROPERTY(int mapWidth READ getMapWidth WRITE setMapWidth NOTIFY mapWidthChanged)
    Q_PROPERTY(int mapHeight READ getMapHeight WRITE setMapHeight NOTIFY mapHeightChanged)
    Q_PROPERTY(int mapRealWidth READ getMapRealWidth WRITE setMapRealWidth NOTIFY mapRealWidthChanged)
    Q_PROPERTY(int mapRealHeight READ getMapRealHeight WRITE setMapRealHeight NOTIFY mapRealHeightChanged)

public:

    explicit Model2DMap(QObject *parent = nullptr);
    void tick()override;

    int getMapWidth() const;
    void setMapWidth(int newMapWidth);

    int getMapHeight() const;
    void setMapHeight(int newMapHeight);

    int getMapRealWidth() const;
    void setMapRealWidth(int newMapRealWidth);

    int getMapRealHeight() const;
    void setMapRealHeight(int newMapRealHeight);

    bool elementIsValied(int x,int y);
    void setElement(int x,int y,int value);
    void setElementValied(int x,int y,bool valied);

    void initMap(int w,int h,int rw,int rh,QVector<QVector<int>> mapMatrix,QVector<QVector <bool> > valiedMatrix);


    QVector<QVector<bool> > getValiedMatrix() const;

    QVector<QVector<int> > getMapMatrix() const;

    QPoint getElementPoint(int x,int y);
    QPair<int,int> getPerElementSize();
private:

    int m_mapWidth;

    int m_mapHeight;

    int m_mapRealWidth;

    int m_mapRealHeight;

    QVector<QVector <bool> > m_valiedMatrix;
    QVector<QVector <int> > m_mapMatrix;
    int perElementSizeW;
    int perElementSizeH;

    bool m_initFlag=false;

signals:

    void mapWidthChanged();
    void mapHeightChanged();
    void mapRealWidthChanged();
    void mapRealHeightChanged();
};

REGISTER_OBJECT(Model2DMap,ComponentObject)





















#endif // MODEL2DMAP_H
