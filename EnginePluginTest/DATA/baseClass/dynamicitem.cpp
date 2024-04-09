#include "dynamicitem.h"

DynamicItem::DynamicItem(GameObject *obj, QPixmap pix, QObject *parent):GameObjectItem{obj,pix,parent}
{
    if(obj!=nullptr)
    {
        obj->setNowState("Normal");

        //需要提出来，作为一个单独的控制函数   setStateMonited(true);
//        connect(obj,&GameObject::nowStateChanged,this,[this](){
//            qDebug()<<"GameObject::nowStateChanged";
//            qDebug()<<m_stateList;
//            qDebug()<<getLinkObj()->getNowState();
//            qDebug()<<"GameObject::nowStateChanged--end";
//            changeState(getLinkObj()->getNowState());
//        });
        //已转移至  setSyncPixState
    }

}

void DynamicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //
    if(state())
    {
        painter->drawPixmap(0,0,m_nowPix);
    }
}

void DynamicItem::initPix(QVector<QString> stateList, QVector<QVector<QPixmap *> > pixList)
{
//    qDebug()<<"DynamicItem::initPix\n"<<stateList <<pixList;
//    m_stateList=stateList;
//    m_pixList=pixList;
//    m_nowPixList=m_pixList[0];
//    qDebug()<<"m_objPix:"<<m_objPix;
//    qDebug()<<"m_nowPixList[0]:"<<m_nowPixList[0];
//    qDebug()<<m_nowPixList[0]->isNull();
//    qDebug()<<m_nowPixList[0]->width();
//    qDebug()<<m_nowPixList[0]->height();
//    setObjPix(*(m_nowPixList[0]));
//    qDebug()<<"m_objPix"<<m_objPix;
//    //update();

//    connect(&m_timer,&QTimer::timeout,this,[this](){
//        m_objPix=*(m_nowPixList[m_count]);
//        update();
//        m_count++;
//        if(m_count<m_nowPixList.size())
//        {
//            ;
//        }
//        else
//        {
//            //emit 已经经过一次循环
//            ;
//            m_count=0;
//        }
//    });

    //m_timer.start();
}

void DynamicItem::initPix(QVector<QString> stateList, QVector<QVector<int> > stateIndexList, int startX, int startY, int perWidth, int perHeight, int xInterval, int yInterval)
{
    qDebug()<<"DynamicItem::initPix";
//    for(auto it:m_pixList)
//    {
//        delete &it;
//    }
    m_pixList.clear();

    m_stateList=stateList;
    m_pixIndexList=stateIndexList;

    qDebug()<<"m_pixRect"<<m_pixRect;
    m_pixRect.setRect(0,0,perWidth,perHeight);
    qDebug()<<"m_pixRect"<<m_pixRect;

    //QVector<QVector<QPixmap> > pixList;
    int sourceWidth=m_objPix.width();
    int sourceHeight=m_objPix.height();
    qDebug()<<"$$$"<<sourceWidth<<sourceHeight;
    //进行切割。
    int nowY=startY;
    //暂时用不上--用于控制切割碎片的
    int pixHeight=qMin(sourceHeight-nowY,perHeight);
    while((nowY+perHeight+yInterval)<=sourceHeight)
    {
        int nowX=startX;
        int pixWidth=qMin(sourceWidth-nowX,perWidth);
        while((nowX+perWidth+xInterval)<=sourceWidth)
        {
            m_pixList.append(*new QPixmap(m_objPix.copy(nowX,nowY,perWidth,perHeight)));
            nowX+=(xInterval+perWidth);
            qDebug()<<"$$ x "<<nowX;
        }
        nowY+=(yInterval+perHeight);
        qDebug()<<"$$ y "<<nowY;
    }
    qDebug()<<" check--:"<<m_pixList<<m_pixList.size() <<m_pixIndexList <<m_pixIndexList.size();
    m_nowPixIndexList=m_pixIndexList[0];

    m_nowPix=m_pixList[m_nowPixIndexList[0]];

    m_timer.setInterval(100);
    connect(&m_timer,&QTimer::timeout,this,[this](){
        m_nowPix=m_pixList[m_nowPixIndexList[m_count]];
        update();
        m_count++;
        if(m_count<m_nowPixIndexList.size())
        {
            ;
        }
        else
        {
            //emit 已经经过一次循环
            ;
            m_count=0;
        }
    });

    m_timer.start();
}

void DynamicItem::setLayer(PixLayer layer)
{
    switch(layer)
    {
    case PixLayer::Background:
    {
        setNowLayer(0);
        setZValue(0);
    }
        break;
    case PixLayer::Object:
    {
        setNowLayer(1);
        setZValue(0);
    }
        break;
    case PixLayer::Special:
    {
        setNowLayer(2);
        setZValue(0);
    }
        break;
    default:
        qDebug()<<"Error: DynamicItem::setLayer : no have this PixLayer!";
        break;
    }
}

void DynamicItem::changeState(QString state)
{
    qDebug()<<"--DynamicItem::changeState--";
    qDebug()<<"Check0"<<state<<m_pixIndexList<<m_nowPixIndexList;

    //找到state对应的pixlist
    int index=-1;
    for(int i=0;i<m_stateList.size();++i)
    {
        qDebug()<<"Check1"<<i<<(state==m_stateList[i]);
        if(state==m_stateList[i])
        {
            index=i;
            break;
        }
    }
    qDebug()<<"check2:"<<index;

    //切换nowPix
    if(index!=-1)
    {
        m_nowPixIndexList=m_pixIndexList[index];
        m_count=0;
        update();
    }
    else
    {
        qDebug()<<"DynamicItem::changeState : no have this state!";
    }

    qDebug()<<"--DynamicItem::changeState--end";

}

void DynamicItem::setSyncPixState(bool flag)
{
    if(m_linkObj!=nullptr)
    {
        if(flag)
        {
            connect(m_linkObj,&GameObject::nowStateChanged,this,[this](){
                qDebug()<<"GameObject::nowStateChanged";
                qDebug()<<m_stateList;
                qDebug()<<getLinkObj()->getNowState();
                qDebug()<<"GameObject::nowStateChanged--end";
                changeState(getLinkObj()->getNowState());
            });
        }
    }
}
