#include "dynamicitem.h"


DynamicItem::DynamicItem(QPixmap *pixmap, QGraphicsItem *parent):GraphicsItem{pixmap,parent}
{

}

void DynamicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //
    GraphicsItem::paint(painter,option,widget);
}
void DynamicItem::initPix(QVector<QString> stateList, QVector<QVector<QPixmap *> > pixList)
{
    m_stateList=stateList;
    m_pixList=pixList;
    m_nowPixList=&m_pixList[0];
    pix=*(*m_nowPixList)[m_count];
    update();
}

void DynamicItem::changeState(QString state)
{
    //找到state对应的pixlist
    int index=-1;
    for(int i=0;i<m_stateList.size();++i)
    {
        if(state==m_stateList[i])
        {
            index=i;
            break;
        }
    }
    //切换nowPix
    if(index!=-1)
    {
        m_nowPixList=&m_pixList[index];
    }
    else
    {
        qDebug()<<"DynamicItem::changeState : no have this state!";
    }

}

void DynamicItem::pixChanged()
{
    pix=*(*m_nowPixList)[m_count];
    m_count++;
    if(m_count<m_nowPixList->size())
    {
        ;
    }
    else
    {
        //emit 已经经过一次循环
        ;
        m_count=0;
    }
    update();
}
