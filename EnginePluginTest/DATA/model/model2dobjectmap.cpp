#include "model2dobjectmap.h"
#include "qcoreapplication.h"

#include <QTime>
#include "TOOL/template/ThreadPool.hpp"


Model2DObjectMap::Model2DObjectMap(QObject *parent)
    : ComponentObject{parent}
{
    setObjectName("Model2DObjectMap");
}

void Model2DObjectMap::tick()
{
    qDebug()<<"Model2DObjectMap::tick---";

    qDebug()<<m_mapMatrix;

    qDebug()<<"Model2DObjectMap::tick---end";

}

void Model2DObjectMap::initMap(int w, int h, QVector<QVector<int> > mapMatrix)
{
    setMapWidth(w);
    setMapHeight(h);
    m_mapMatrix=mapMatrix;
    m_itemMatrix=mapMatrix;
    m_initFlag=true;
}

void Model2DObjectMap::initHero(int heroId)
{
    m_heroId=heroId;

    auto it=getHeroPos();
    if(it.first!=-1)
    {
        setHasHero(true);
    }
    else
    {
        setHasHero(false);
    }
}

QPair<int, int> Model2DObjectMap::getHeroPos()
{
    m_heroPosX=-1;
    m_heroPosY=-1;
    bool flag=false;
    for(int i=0;i<m_mapMatrix.size();++i)
    {

        for(int j=0;j<m_mapMatrix[i].size();++j)
        {
            if(m_mapMatrix[i][j]==m_heroId)
            {
                m_heroPosX=j;
                m_heroPosY=i;
                flag=true;
                break;
            }
        }
        if(flag)
        {

            break;
        }
    }

    if(!flag)
    {
        qDebug() << "No Find Hero";
    }


    return QPair<int,int>(m_heroPosX,m_heroPosY);
}

int Model2DObjectMap::getHeroId()
{
    return m_heroId;
}

QPair<int, int> Model2DObjectMap::getObjectPos(int id)
{
    bool flag=false;
    for(int i=0;i<m_mapMatrix.size();++i)
    {
        for(int j=0;j<m_mapMatrix[i].size();++j)
        {
            if(m_mapMatrix[i][j]==id)
            {
                flag=true;
                return QPair<int, int>(j,i);
            }
        }
    }

    if(!flag)
    {
        qDebug()<<"Model2DObjectMap::getObjectPos: no find this id";
    }
    return QPair<int, int>(-1,-1);
}

void Model2DObjectMap::objectMove(int oldX, int oldY, int newX, int newY)
{
    //新版的逻辑
    /*
    1. 判断Old位置是否有Object
    2. 判断New位置是否有Object
    3. 发送对应信号
    4. 所有的Object的位置的改变都通过上一级类调用该类的setElement进行改变（分类：移动、战斗成功、战斗失败、NPC交互）
    */

    int obj1Id=m_mapMatrix[oldY][oldX];
    if(obj1Id!=0)
    {
        int obj2Id=m_mapMatrix[newY][newX];
        if(obj2Id!=0)
        {
            if(obj2Id==m_heroId)
            {
                emit objectOverlaped(this,obj2Id,oldX,oldY,obj1Id,newX,newY);
            }
            else
            {
                emit objectOverlaped(this,obj1Id,oldX,oldY,obj2Id,newX,newY);
            }
        }
        else
        {
            emit objectMoved(this,obj1Id,oldX,oldY,newX,newY);
        }
    }
}


//void Model2DObjectMap::objectMove(int oldX, int oldY, int newX, int newY)
//{

//     //！warning！
//    //缺少安全性检查

//    int obj1Id=m_mapMatrix[oldY][oldX];
//    if(obj1Id!=0)
//    {
//        m_mapMatrix[oldY][oldX]=0;
//    }else
//    {
//        qDebug()<<"Model2DObjectMap::objectMove : NO HAVE OBJECT";
//        qDebug()<<"m_mapMatrix"<<m_mapMatrix;
//        qDebug()<<"xy:"<<oldX<<oldY;
//        return;
//    }

//    int obj2Id=m_mapMatrix[newY][newX];
//    if(obj2Id==0){
//        m_mapMatrix[newY][newX]=obj1Id;
//        emit ObjectMove(obj1Id,newX,newY);
//    }
//    else
//    {
//        //emit ObjectOverLap(obj1Id,obj2Id,newX,newY);

//        if(m_signalLinkObj!=nullptr)
//        {
//            //等待处理完成的信号
//            QTimer timer;
//            timer.setSingleShot(true);
//            connect(&timer,&QTimer::timeout,[this,&obj1Id,&obj2Id,&newX,&newY]{
//                qDebug()<<"####Model2DObjectMap::objectMove: TIMEOUT! emit!";
//                emit ObjectOverLap(obj1Id,obj2Id,newX,newY);
//            });
//            timer.start(10);
//            //QCoreApplication::processEvents();
//            int res;
//            qDebug()<<"####Model2DObjectMap::objectMove: test1";
//            bool flag_wait=false;
//            QTime time=QTime::currentTime().addMSecs(10);
//            while(QTime::currentTime()<time)
//            {
//                QCoreApplication::processEvents();
//                if(!flag_wait)
//                {
//                    flag_wait=true;
//                    qDebug()<<"####Model2DObjectMap::objectMove: wait!" <<m_signalLinkObj;
//                    res=waitForIntSignal(m_signalLinkObj,SIGNAL(overLapSolved(int)),1000);
//                }
//            }

//            qDebug()<<"####Model2DObjectMap::objectMove:test2";
//            bool flag=false;
//            QTime time1=QTime::currentTime().addMSecs(10);
//            while(QTime::currentTime()<time1)
//            {
//                QCoreApplication::processEvents();
//                if(!flag)
//                {
//                    flag=true;
//                    //emit ObjectOverLap(obj1Id,obj2Id,newX,newY);
//                    //qDebug()<<"####Model2DObjectMap::objectMove: emit ObjectOverLap"<<obj1Id<<obj2Id<<newX<<newY;
//                }
//            }
//            qDebug()<<"####Model2DObjectMap::objectMove:test3";
//            //emit ObjectOverLap(obj1Id,obj2Id,newX,newY);
//            qDebug()<<"####Model2DObjectMap::objectMove: "<<res;

//            if(res==-1|res==0)
//            {
//                qDebug()<<"Signal error！Model2DObjectMap::objectMove: "<<res;
//            }
//            else if(res==1)
//            {
//                m_mapMatrix[oldY][oldX]=obj1Id;
//                emit ObjectMove(obj1Id,oldX,oldY);
//            }
//            else if(res==obj1Id)
//            {
//                qDebug()<<"m_mapMatrix1"<<m_mapMatrix;
//                qDebug()<<getHeroPos();
//                m_mapMatrix[newY][newX]=res;
//                qDebug()<<"m_mapMatrix2"<<m_mapMatrix;
//                qDebug()<<getHeroPos();
//                emit ObjectMove(obj1Id,newX,newY);
//            }
//            else
//            {
//                qDebug()<<"check:"<<res <<obj1Id<< obj2Id;
//                qDebug()<<" move false!";
//                m_mapMatrix[oldY][oldX]=obj1Id;
//                emit ObjectMove(obj1Id,oldX,oldY);
//            }
//        }
//        else
//        {
//            qDebug()<<"ObjectOverLap! but no have link solve Object!";
//        }
//    }

//}



void Model2DObjectMap::addObject(int x, int y, int index)
{
    m_mapMatrix[y][x]=index;
}

void Model2DObjectMap::setElement(int x, int y, int index)
{
    //缺检查
    m_mapMatrix[y][x]=index;

}

void Model2DObjectMap::delObject(int index)
{
    for(int i=0;i<m_mapMatrix.size();i++)
    {
        bool flag=false;
        for(int j=0;j<m_mapMatrix[i].size();j++)
        {
            if(m_mapMatrix[i][j]==index)
            {
                m_mapMatrix[i][j]=0;
                flag=true;
                break;
            }
        }
        if(flag)
        {
            break;
        }

    }
}

int Model2DObjectMap::getMapWidth() const
{
    return m_mapWidth;
}

void Model2DObjectMap::setMapWidth(int newMapWidth)
{
    if (m_mapWidth == newMapWidth)
        return;
    m_mapWidth = newMapWidth;
    emit mapWidthChanged();
}

int Model2DObjectMap::getMapHeight() const
{
    return m_mapHeight;
}

void Model2DObjectMap::setMapHeight(int newMapHeight)
{
    if (m_mapHeight == newMapHeight)
        return;
    m_mapHeight = newMapHeight;
    emit mapHeightChanged();
}

bool Model2DObjectMap::hasHero() const
{
    return m_hasHero;
}

void Model2DObjectMap::setHasHero(bool newHasHero)
{
    if (m_hasHero == newHasHero)
        return;
    m_hasHero = newHasHero;
    emit hasHeroChanged(m_hasHero);
}

void Model2DObjectMap::clearHero()
{
    if(hasHero())
    {
        m_mapMatrix[m_heroPosY][m_heroPosX]=0;
    }
    setHasHero(false);
    emit heroCleared(m_heroId);

}

void Model2DObjectMap::setHeroPos(int heroId, int x, int y)
{

    m_mapMatrix[y][x]=heroId;
    initHero(heroId);
}

QVector<QVector<int> > Model2DObjectMap::mapMatrix() const
{
    return m_mapMatrix;
}

void Model2DObjectMap::checkState(int objId1, int objId2)
{



}

QObject *Model2DObjectMap::signalLinkObj() const
{
    return m_signalLinkObj;
}

void Model2DObjectMap::setSignalLinkObj(QObject *newSignalLinkObj)
{
    m_signalLinkObj = newSignalLinkObj;
}

void Model2DObjectMap::setItemPos(int x, int y, int id)
{
    if(y>0&&y<m_itemMatrix.size() )
    {
        if(x>0&&x<m_itemMatrix[y].size())
        {
            m_itemMatrix[y][x]=id;
        }
    }
}

int Model2DObjectMap::getItemId(int x, int y)
{
    int res=-1;
    if(y>=0&&y<m_itemMatrix.size() )
    {
        if(x>=0&&x<m_itemMatrix[y].size())
        {
            res=m_itemMatrix[y][x];
        }
    }

    return res;
}

void Model2DObjectMap::initItemMap(QVector<QVector<int> > itemMap)
{
    m_itemMatrix=itemMap;
}
