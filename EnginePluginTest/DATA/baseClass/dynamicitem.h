#ifndef DYNAMICITEM_H
#define DYNAMICITEM_H

#include <QObject>
#include <DATA/baseClass/gameobjectitem.h>
#include <QMap>
#include <QVector>

class DynamicItem : public GameObjectItem
{
    Q_OBJECT
public:
    explicit DynamicItem(GameObject*obj,QPixmap pix,QObject *parent=nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) override;

    void initPix(QVector<QString> stateList,QVector<QVector<QPixmap*> > pixList);
    void initPix(QVector<QString> stateList,QVector<QVector<int> > stateIndexList,int startX=0, int startY=0, int perWidth=32, int perHeight=32, int xInterval=0, int yInterval=1);
    void setLayer(GameObjectItem::PixLayer layer);
    void changeState(QString);

    void setSyncPixState(bool flag);


private:

    QTimer m_timer;
    int m_count=0;
    QVector<int> m_nowPixIndexList;
    QVector<QVector<int> > m_pixIndexList;
    QVector<QPixmap> m_pixList;
    QVector<QString> m_stateList;

    QPixmap m_nowPix;
signals:

};

#endif // DYNAMICITEM_H
