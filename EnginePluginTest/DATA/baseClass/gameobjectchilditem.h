#ifndef GAMEOBJECTCHILDITEM_H
#define GAMEOBJECTCHILDITEM_H

#include <QObject>

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <DATA/baseClass/gameobject.h>


class GameObjectChildItem :public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit GameObjectChildItem(QGraphicsItem* itemParent,QPixmap pix,QObject *parent = nullptr);

signals:

};

#endif // GAMEOBJECTCHILDITEM_H
