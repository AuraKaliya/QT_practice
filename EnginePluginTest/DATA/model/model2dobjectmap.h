#ifndef MODEL2DOBJECTMAP_H
#define MODEL2DOBJECTMAP_H

#include <QObject>
#include <QPoint>
#include <QVector>
#include <QEventLoop>
#include <QTimer>

#include "../baseClass/componentobject.h"

class Model2DObjectMap : public ComponentObject
{
    Q_OBJECT

    Q_PROPERTY(int mapWidth READ getMapWidth WRITE setMapWidth NOTIFY mapWidthChanged)
    Q_PROPERTY(int mapHeight READ getMapHeight WRITE setMapHeight NOTIFY mapHeightChanged)
    Q_PROPERTY(bool hasHero READ hasHero WRITE setHasHero NOTIFY hasHeroChanged)

public:

    explicit Model2DObjectMap(QObject *parent = nullptr);
    void tick()override;

    void initMap(int w,int h,QVector<QVector <int> >mapMatrix);
    void initHero(int heroId);
    QPair<int,int> getHeroPos();
    int getHeroId();
    QPair<int,int>getObjectPos(int id);
    void objectMove(int oldX,int oldY,int newX,int newY);
    void addObject(int x,int y,int index);
    void setElement(int x,int y,int index);
    void delObject(int index);

    int getMapWidth() const;
    void setMapWidth(int newMapWidth);

    int getMapHeight() const;
    void setMapHeight(int newMapHeight);

    bool hasHero() const;
    void setHasHero(bool newHasHero);

    void clearHero();
    void setHeroPos(int heroId,int x,int y);
    QVector<QVector<int> > mapMatrix() const;

    void checkState(int objId1,int objId2);

    QObject *signalLinkObj() const;
    void setSignalLinkObj(QObject *newSignalLinkObj);


    void setItemPos(int x,int y,int id);
    int getItemId(int x,int y);


    void initItemMap(QVector<QVector <int> > itemMap);

signals:

    void mapWidthChanged();
    void mapHeightChanged();
    void hasHeroChanged(bool);

    void objectMoved(Model2DObjectMap* map,int index,int oX,int oY,int nX,int nY);
    void objectOverlaped(Model2DObjectMap* map,int index1,int x1,int y1,int index2,int x2,int y2);

    void heroCleared(int);

private:
    QVector<QVector <int> > m_mapMatrix;
    QVector<QVector<int> > m_itemMatrix;
    int m_heroPosX;
    int m_heroPosY;
    int m_heroId;
    int m_mapWidth;
    int m_mapHeight;
    bool m_hasHero;

    bool m_initFlag=false;

    QObject* m_signalLinkObj=nullptr;
};

REGISTER_OBJECT(Model2DObjectMap,ComponentObject)
#endif // MODEL2DOBJECTMAP_H
