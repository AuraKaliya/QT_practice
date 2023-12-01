#ifndef DYNAMICITEM_H
#define DYNAMICITEM_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <graphicsitem.h>
#include <QVector>
#include <QMap>
#include <qtimer.h>

class DynamicItem : public GraphicsItem
{

public:
    explicit DynamicItem(QPixmap *pixmap,QGraphicsItem* parent=nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) override;
    void initPix(QVector<QString> stateList,QVector<QVector<QPixmap*> > pixList);
    void changeState(QString);
    void pixChanged();

private:

    int m_count=0;
    QVector<QPixmap*>* m_nowPixList;
    QVector<QVector<QPixmap*> > m_pixList;
    QVector<QString> m_stateList;

signals:

};

#endif // DYNAMICITEM_H
