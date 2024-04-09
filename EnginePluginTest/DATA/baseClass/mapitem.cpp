#include "mapitem.h"

MapItem::MapItem(GameObject *obj, QPixmap pix, QObject *parent)
    : GameObjectItem{obj, pix,parent}
{

}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(state())
    {
        GameObjectItem::paint(painter,option,widget);
        if(m_initState)
        {
            qDebug()<<"map2dItem paint";
            // qDebug()<<m_mapPix;
            qDebug()<<m_mapPix;
            //qDebug()<<"check0: Map2DItem"<<(int)&(*this);
            int i=0;
            for(auto it:m_mapPix)
            {
                int j=0;
                for(auto it2:it)
                {
                    painter->drawPixmap(i*(m_xInterval),j*(m_yInterval),it2);
                    j++;
                }
                i++;
            }
        }
    }
}

void MapItem::initMap(int xScale, int yScale, QMap<int, PixSource *> map, int defaultIdx, int xInterval, int yInterval)
{
    qDebug()<<"MapItem::initMap  --begin---";

    m_xScale=xScale;
    m_yScale=yScale;

    m_pixSourceDictionary=map;
    m_defaultIdx=defaultIdx;

    qDebug()<<"MapItem::initMap  --check0---"<<m_xScale<<m_yScale<<"--MapDictionary--:"<<m_pixSourceDictionary<<" -Default:-"<<m_defaultIdx;
    //创建scale数量的DynamicItem   从m_pixSourceDictionary的PixSource 中获取初始化数据信息：stateStrList stateIndexList ， 分割标准

    //初始化index标志
    for(int i=0;i<m_yScale;i++)
    {
        QVector<int> tmpVector;
        for(int j=0;j<m_xScale;j++)
        {
            tmpVector.append(m_defaultIdx);
        }
        m_mapIdx.append(tmpVector);
    }
    qDebug()<<"MapItem::initMap  --check1---"<<m_mapIdx;
    PixSource * pixSource=m_pixSourceDictionary.find(defaultIdx).value();


    for(int i=0;i<m_yScale;++i)
    {
        QVector<DynamicItem *> tmpVector;
        for(int j=0;j<m_xScale;++j)
        {

            DynamicItem * item=new DynamicItem(nullptr,*pixSource->pix(),nullptr);
            item->setObjPix(* pixSource->pix());
            item->initPix(pixSource->stateList(),pixSource->stateIndexList(),0,0,pixSource->getPerW(),pixSource->getPerH(),pixSource->XInterval(),pixSource->YInterval());
            item->setPixScale(QRect(0,0,xInterval,yInterval));
            item->setPos(j*xInterval,i*yInterval);
            item->setParentItem(this);

            qDebug()<<"MapItem::initMap  --check1.5--- pixId"<<pixSource->id();


            tmpVector.append(item);
        }
        m_itemList.append(tmpVector);
    }
    qDebug()<<"MapItem::initMap  --check2---   END";
    updateMap();
    qDebug()<<"MapItem::initMap  --check2.2---   END";
  //connect(this,&GameObjectItem::resetPixScale,this,&MapItem::updateMap);


  setPixScale(QRect(0,0,m_xScale*xInterval,m_yScale*yInterval));
  m_initState=true;
    //
  qDebug()<<"MapItem::initMap  --end---";
}

void MapItem::setPix(int x, int y, int idx)
{
   PixSource * pixSource=m_pixSourceDictionary.find(idx).value();
   m_itemList[y][x]->setObjPix(* pixSource->pix());
   m_itemList[y][x]->initPix(pixSource->stateList(),pixSource->stateIndexList(),0,0,pixSource->getPerW(),pixSource->getPerH(),pixSource->XInterval(),pixSource->YInterval());
   update();
}

void MapItem::setScale(int xScale, int yScale)
{
   m_xScale=xScale;
   m_yScale=yScale;



//   m_mapIdx.resize(m_yScale);
//   for(auto it:m_mapIdx)
//   {
//        it.resize(m_xScale);
//   }

   //updateMap();
}

void MapItem::updateMap()
{
   qDebug()<<"MapItem::updateMap  --start";
   qDebug()<<"MapItem::updateMap  --check0:"<<m_xInterval<<m_yInterval;
   m_xInterval= ((double)m_pixRect.width())/m_xScale;
   m_yInterval=((double)m_pixRect.height())/m_yScale;
   qDebug()<<"MapItem::updateMap  --check0.5:"<<m_xInterval<<m_yInterval;


   //在重设后，需要对Map进行更新
   //对scale进行更新
   for(auto it:m_mapPix)
   {
        it.clear();
   }
   m_mapPix.clear();

   for(int i=0;i<m_yScale;i++)
   {
        for(int j=0;j<m_xScale;j++)
        {
          PixSource * pixSource=m_pixSourceDictionary.find(m_mapIdx[j][i]).value();
          m_itemList[j][i]->setObjPix(* pixSource->pix());
          m_itemList[j][i]->initPix(pixSource->stateList(),pixSource->stateIndexList(),0,0,pixSource->getPerW(),pixSource->getPerH(),pixSource->XInterval(),pixSource->YInterval());
        }
   }
   update();
      qDebug()<<"MapItem::updateMap  --end";
}
