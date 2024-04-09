#include "motamap.h"

#include <QMetaProperty>

MotaMap::MotaMap(QObject *parent)
    : GameObject{parent}
{
    setType(GameObject::Environment);
    setClassName("MotaMap");
    setSuperEdit(true);
    //m_map=new Model2DMap;
    m_tower=new ModelTower;
    //m_myComponents.append(m_map);
    //m_myComponents.append(new ModelTower);
    m_myComponents.append(m_tower);
    //m_myComponents.append(std::declval<Model2DMap>());
    m_myComponents.append(new Model2DMap);
    m_myComponents.append(new Model2DObjectMap);

    if(!m_registFlag)
    {
        //将处理策略注册进map中。
        //每个类进行一次初始化策略
        m_soluteStratagies.insert("ChangeElement",changeElement);

        //已进行初始化策略
        m_registFlag=true;
    }
}

void MotaMap::init(const QJsonObject *data)
{
    qDebug()<<"---init MotaMap---";
    qDebug()<<"check0:"<<data->keys();
    //属性--统一读取
    unsigned int id=data->value("Id").toInt();
    setId(id);
    unsigned int type=data->value("Type").toInt();
    //qDebug()<<"type:"<<type;
    setType(static_cast<Type>(type));
    qDebug()<<"-------------Type Read: Environment"<<(getType()==Type::Environment);
    //qDebug()<<"-------------Type Read: Environment--"<<getType();
    //qDebug()<<"-------------Type Read: Environment--"<<Type::Environment;

    //数据解析
    unsigned int mapLayer=data->value("MapLayer").toInt();  //层数
    unsigned int mapWidth=data->value("MapSize").toArray().at(0).toInt();  //网格数
    unsigned int mapHeight=data->value("MapSize").toArray().at(1).toInt();
    unsigned int mapThreshold=data->value("Threshold").toInt();

    unsigned int objWidth=data->value("Size").toArray().at(0).toInt();
    unsigned int objHeight=data->value("Size").toArray().at(0).toInt();

    if(data->contains("Pos"))
    {
        double objPosX=data->value("Pos").toArray().at(0).toDouble();
        double objPosY=data->value("Pos").toArray().at(0).toDouble();
        //objPos
        setPosX(objPosX);
        setPosY(objPosY);
        setPosInit(true);
    }else
    {
        setPosInit(false);
    }


    QString pixIdList=data->value("PixIdList").toString();
    QString name=data->value("Name").toString();


    //初始化设置
        //objSize
    setWidth(objWidth);
    setHeight(objHeight);

        //objPixList- -- --map
    setPixIdList(pixIdList);
    setName(name);

    setMapNetWidth(mapWidth);
    setMapNetHeight(mapHeight);



    QVector<QVector<QVector <int> > > motaMap(mapLayer,QVector<QVector <int> >(mapHeight,QVector <int> (mapWidth,0)));

    QJsonArray motaLayerMapData=data->value("MapMatrix").toArray();
    for(int i=0;i<mapLayer;++i)
    {
        QJsonArray motaHeightMapData=motaLayerMapData[i].toArray();
        for(int j=0;j<mapHeight;++j)
        {
            QJsonArray motaWidthMapData=motaHeightMapData[j].toArray();
            for(int k=0;k<mapWidth;++k)
            {
                //qDebug()<<motaWidthMapData[k].toInt();
                motaMap[i][j][k]=motaWidthMapData[k].toInt();
            }
        }
    }


    QVector<QVector<QVector <bool> > > motaValiedMap(mapLayer,QVector<QVector <bool> >(mapHeight,QVector <bool> (mapWidth,0)));

    if(!data->value("ValiedErea").isNull())
    {
        QJsonArray motaValiedLayerMapData=data->value("ValiedErea").toArray();
        for(int i=0;i<mapLayer;++i)
        {
            QJsonArray motaValiedHeightMapData=motaValiedLayerMapData[i].toArray();
            for(int j=0;j<mapHeight;++j)
            {
                QJsonArray motaValiedWidthMapData=motaValiedHeightMapData[j].toArray();
                for(int k=0;k<mapWidth;++k)
                {
                    motaValiedMap[i][j][k]=(bool)motaValiedWidthMapData[k].toInt();

                }
            }
        }
    }else
    {
        qDebug()<<"ValiedErea Null!";
    }

    qDebug()<<motaValiedMap;

    QVector<int> maplinkedList(mapLayer,0);
    QVector<int> mapPrelinkedList(mapLayer,0);
    if(!data->value("MapLayerLinkedList").isNull())
    {
        QJsonArray mapLinkedListData=data->value("MapLayerLinkedList").toArray();
        for(int i=0;i<mapLayer;++i)
        {
            maplinkedList[i]=mapLinkedListData[i].toInt();
            mapPrelinkedList[mapLinkedListData[i].toInt()]=i;
        }
    }

    QVector<QVector<QVector <int> > > motaObjectMap(mapLayer,QVector<QVector <int> >(mapHeight,QVector <int> (mapWidth,0)));

    QJsonArray motaObjectLayerMapData=data->value("MapObjectMatrix").toArray();
    for(int i=0;i<mapLayer;++i)
    {
        QJsonArray motaHeightMapData=motaObjectLayerMapData[i].toArray();
        for(int j=0;j<mapHeight;++j)
        {
            QJsonArray motaWidthMapData=motaHeightMapData[j].toArray();
            for(int k=0;k<mapWidth;++k)
            {
                //qDebug()<<motaWidthMapData[k].toInt();
                motaObjectMap[i][j][k]=motaWidthMapData[k].toInt();
            }
        }
    }


    int heroId=data->value("HeroId").toInt();

    //建立地图

    m_tower->setAllLayers(mapLayer);
    if(!data->value("MapLayerLinkedList").isNull())
    {
        m_tower->setLayerLinkedList(maplinkedList);
        m_tower->setLayerPreLinkList(mapPrelinkedList);
    }

    int index=0;
    QMap<int,QPair<int,int> > upPos;
    for(auto it :data->value("UpPos").toArray())
    {
        if(it.isArray())
        {
            upPos.insert(index,QPair<int,int>(it.toArray()[0].toInt(),it.toArray()[1].toInt()));
        }
        else if(it.isBool())
        {
            //false --赋值-1
            upPos.insert(index,QPair<int,int>(-1,-1));
        }
        else
        {
            //报错
            qDebug()<<"error! upPos read falied!" << index;
        }
        index++;
    }
    m_tower->setLayerUpPos(upPos);
    qDebug()<<"Check tower upPos:"<<upPos;



    index=0;
    QMap<int,QPair<int,int> > downPos;
    for(auto it :data->value("DownPos").toArray())
    {
        if(it.isArray())
        {
            downPos.insert(index,QPair<int,int>(it.toArray()[0].toInt(),it.toArray()[1].toInt()));
        }
        else if(it.isBool())
        {
            //false --跳过
            downPos.insert(index,QPair<int,int>(-1,-1));
        }
        else
        {
            //报错
            qDebug()<<"error! upPos read falied!" << index;
        }
        index++;
    }
    m_tower->setLayerDownPos(downPos);
    qDebug()<<"Check tower downPos:"<<downPos;




    for(int i=0;i<mapLayer;++i)
    {
        Model2DMap* tmpMap=new Model2DMap;
        Model2DObjectMap* tmpObjectMap=new Model2DObjectMap;

        qDebug()<<"--check0--"<<motaValiedMap[i];
        tmpMap->initMap(mapWidth,mapHeight,objWidth,objHeight,motaMap[i],motaValiedMap[i]);

        connect(tmpObjectMap,&Model2DObjectMap::hasHeroChanged,this,[this](bool flag){
            if(flag)
            {

            }
        });
        tmpObjectMap->initMap(mapWidth,mapHeight,motaObjectMap[i]);
        tmpObjectMap->initHero(heroId);

        m_map.append(tmpMap);
        m_objectMap.append(tmpObjectMap);
        qDebug()<<"m_objectMap"<<motaObjectMap;

    }

    //connect
    // 优化--在demo初始化后从demo处统一获取指针进行connect

    for(auto it:m_objectMap)
    {


        connect(it,&Model2DObjectMap::objectOverlaped,this,[this](Model2DObjectMap* map,int index1,int x1,int y1,int index2,int x2,int y2){
            //map无权在此处理，需要进行转发信号。
            // 优化--在demo初始化后从demo处对该信号进行管理
        });



    }









    qDebug()<<"--check--:";
    for(auto it:this->getMyComponents())
        {
            bool flag=true;
            int i=0;
            while(flag)
            {
                const QMetaObject * pNew=it->metaObject();
                QMetaProperty newProperty=pNew->property(i);
                //QMetaProperty oldProperty=pOld->property(i);
                i++;
                if(newProperty.isValid())
                {
                    qDebug()<<"check0.5:"<<it<<newProperty.read(it);
                }else
                {
                    flag=false;
                }
            }

        }



    qDebug()<<"check:"<<"heroPos"<<getHeroPos();
    GameObject::init(data);
    qDebug()<<"---init MotaMap---end";
}

void MotaMap::tick()
{
    //输出可达矩阵信息
    qDebug()<<"---Now Show the MotaMap's Information---";
    m_tower->tick();
    for(auto it :m_map) it->tick();

    for(auto it :m_objectMap) it->tick();
    qDebug()<<"---Now Show the MotaMap's Information--- end";
}

void MotaMap::solutePacketData(InsPacketData *data)
{
    //根据data中的insName选择相应的函数，根据value进行处理。
    //连锁等处理信息应该在InsManager中进行逻辑
    //这个应该放在GameObject基类中

    auto it=m_soluteStratagies.find(data->insName);
    if(it!=m_soluteStratagies.end())
    {
        //指令处理--数据包处理
        it.value()(this,data->value);
        //后续处理在manager中进行
    }
}

void MotaMap::changeElement(unsigned int layer, int x, int y, int index)
{
    //进行安全性检查：layer是否存在
    //进行处理
    m_map[layer]->setElement(x,y,index);

}

void MotaMap::changeElement(unsigned int layer, int x, int y, int index, bool valiedFlag)
{
    //进行安全性检查：layer是否存在

    //进行处理
    m_map[layer]->setElement(x,y,index);
    m_map[layer]->setElementValied(x,y,valiedFlag);

}

int MotaMap::getNowLayer()
{
    return m_tower->getNowLayer();
}

QVector<QVector<int> > MotaMap::getMap(int layer)
{
    qDebug()<<"-------MotaMap::getMap-----";
    if(layer<m_tower->getAllLayers());
    qDebug()<<"check0:"<<layer<<m_tower->getAllLayers()<<m_map;
    qDebug()<<"check1:"<<m_map[layer]->getMapMatrix();
    qDebug()<<"-------MotaMap::getMap-----end";
    return m_map[layer]->getMapMatrix();
}

QVector<QVector<bool> > MotaMap::getValiedMap(int layer)
{
    if(layer<m_tower->getAllLayers());
    return m_map[layer]->getValiedMatrix();
}

QVector<int> MotaMap::getTowerLink()
{
    return m_tower->getLayerLinkedList();
}

void MotaMap::nextLayer()
{
    m_tower->nextLayer();
}

int MotaMap::getNextLayer()
{
    return m_tower->getNextLayer();
}

int MotaMap::getPreLayer()
{
    return m_tower->getPreLayer();
}

void MotaMap::nextLayer(int layer)
{
    m_tower->setNowLayer(layer);
}

bool MotaMap::elementIsValied(int layer, int x, int y)
{
    if(layer<m_tower->getAllLayers())
    {
        return m_map[layer]->elementIsValied(x,y);
    }else
    {
        qDebug()<<"MotaMap::elementIsValied : no have a layer;(layer=0)";
    }
    return false;
}

QJsonObject MotaMap::getItemData()
{

    QJsonObject obj=GameObject::getItemData();

    obj.insert("MapLayer",(int)m_tower->getAllLayers());

    QJsonArray mapSize;
    mapSize.append(mapNetWidth());
    mapSize.append(mapNetHeight());
    obj.insert("MapSize",mapSize);


    QJsonArray mapArray;
    for(int i=0;i<m_map.size();++i)
    {
        QJsonArray preLayerMap;
        QVector<QVector<int>> mapMatrix=m_map[i]->getMapMatrix();
        for(auto it:mapMatrix)
        {
            QJsonArray preRow;
            for(auto it2:it)
            {
                preRow.append(it2);
            }
            preLayerMap.append(preRow);
        }
        mapArray.append(preLayerMap);
    }
    obj.insert("MapMatrix",mapArray);


    QJsonArray mapValiedArray;
    for(int i=0;i<m_map.size();++i)
    {
        QJsonArray preLayerMap;
        QVector<QVector<bool>> mapMatrix=m_map[i]->getValiedMatrix();
        for(auto it:mapMatrix)
        {
            QJsonArray preRow;
            for(auto it2:it)
            {
                preRow.append((int)it2);
            }
            preLayerMap.append(preRow);
        }
        mapValiedArray.append(preLayerMap);
    }
    obj.insert("ValiedErea",mapValiedArray);


    QJsonArray mapObjectArray;
    for(int i=0;i<m_objectMap.size();++i)
    {
        QJsonArray preLayerMap;
        QVector<QVector<int>> mapMatrix=m_objectMap[i]->mapMatrix();
        for(auto it:mapMatrix)
        {
            QJsonArray preRow;
            for(auto it2:it)
            {
                preRow.append(it2);
            }
            preLayerMap.append(preRow);
        }
        mapObjectArray.append(preLayerMap);
    }
    obj.insert("MapObjectMatrix",mapObjectArray);


    //upPos
    QJsonArray upPosArray;
    auto upPos=m_tower->layerUpPos();
    for(auto it=upPos.begin();it!=upPos.end();++it)
    {
        if(it.value().first!=-1)
        {
        QJsonArray layerPosArray;
        layerPosArray.append(it.value().first);
        layerPosArray.append(it.value().second);
        upPosArray.append(layerPosArray);
        }
    }
    upPosArray.append(false);
    obj.insert("UpPos",upPosArray);

    //downPos
    QJsonArray downPosArray;
    downPosArray.append(false);
    auto downPos=m_tower->layerDownPos();
    for(auto it=downPos.begin();it!=downPos.end();++it)
    {
        if(it.value().first!=-1)
        {
            QJsonArray layerPosArray;
            layerPosArray.append(it.value().first);
            layerPosArray.append(it.value().second);
            downPosArray.append(layerPosArray);
        }

    }
    obj.insert("DownPos",downPosArray);




    obj.insert("HeroId",m_objectMap[0]->getHeroId());

    QJsonArray linkArray;
    for(auto it:m_tower->getLayerLinkedList())
    {
        linkArray.append(it);
    }

    obj.insert("MapLayerLinkedList",linkArray);



    return obj;
}

void MotaMap::changeElement(GameObject *me, QVariant v)
{
    //Variant
    /*
        Vecotr[layer(int),x(int),y(int),newIndex(int)]
    */


    MotaMap* Me=static_cast<MotaMap*>(me);
    //处理数据
    QVector<QVariant> tmpList=v.toList();
    int layer=tmpList[0].toInt();
    int x=tmpList[1].toInt();
    int y=tmpList[2].toInt();
    int newIndex=tmpList[3].toInt();
    if(tmpList.size()>4)
    {
        bool valiedFlag=tmpList[4].toBool();
        Me->changeElement(layer,x,y,newIndex,valiedFlag);
    }else
    {
        Me->changeElement(layer,x,y,newIndex);
    }

}

void MotaMap::operator <<(GameObject &obj)
{
    GameObject::operator<<(obj);
    MotaMap* mObj=static_cast<MotaMap*>(&obj);

    this->m_map=mObj->m_map;
    this->m_tower=mObj->m_tower;
    this->m_tilePixDictionary=mObj->m_tilePixDictionary;
}

QPoint MotaMap::getElementPoint(int layer, int x, int y)
{
    return m_map[layer]->getElementPoint(x,y);
}

QPair<int, int> MotaMap::getMapInterval(int layer)
{
    return m_map[layer]->getPerElementSize();
}

QPair<int, QPair<int, int> > MotaMap::getHeroPos()
{
    qDebug()<<"MotaMap::getHeroPos()"<<m_tower->getNowLayer()<<" --- "<<m_objectMap[m_tower->getNowLayer()]->mapMatrix();

    return QPair<int, QPair<int, int> >(m_tower->getNowLayer(),m_objectMap[m_tower->getNowLayer()]->getHeroPos());
}

QPair<int, QPair<int, int> > MotaMap::findObjectPos(int id)
{
    qDebug()<<"--- MotaMap::findObjectPos---";
    bool flag=false;
    for(int i=0;i<m_tower->getAllLayers();++i)
    {

        QPair<int, int> tmp=m_objectMap[i]->getObjectPos(id);
        if(tmp.first!=-1)
        {
            flag=true;
            qDebug()<<"--- MotaMap::findObjectPos---end--true";
            return QPair<int, QPair<int, int> >(i,tmp);
        }

    }

    if(!flag)
    {
         qDebug()<<"--- MotaMap::findObjectPos---end--false";
    }

    return QPair<int, QPair<int, int> >(-1,QPair<int, int> ());
}

void MotaMap::objectMove(int layer, int oldX, int oldY, int newX, int newY)
{
    m_objectMap[layer]->objectMove(oldX,oldY,newX,newY);
}

void MotaMap::setItemPos(int layer, int x, int y, int itemId)
{
    m_objectMap[layer]->setItemPos(x,y,itemId);
}

QPair<int, int> MotaMap::getUpPos()
{
    return m_tower->getUpPos(m_tower->getNowLayer());
}

QPair<int, int> MotaMap::getDownPos()
{
    return m_tower->getDownPos(m_tower->getNowLayer());
}

QPair<int, int> MotaMap::getUpPos(int layer)
{
return m_tower->getUpPos(layer);
}

QPair<int, int> MotaMap::getDownPos(int layer)
{
return m_tower->getDownPos(layer);
}

void MotaMap::heroMoveToNextLayer(int layer, int x, int y)
{
    //获取当前hero的位置，修改至目标位置。

    int nowLayer=m_tower->getNowLayer();
    int heroId=m_objectMap[nowLayer]->getHeroId();
    m_objectMap[nowLayer]->clearHero();
    m_objectMap[layer]->setHeroPos(heroId,x,y);
    m_tower->setNowLayer(layer);
}

void MotaMap::heroChanged(int newId)
{
    for(auto it:m_objectMap)
    {
        it->initHero(newId);
    }
}

void MotaMap::addObject(int layer, int x, int y, int index)
{
    m_objectMap[layer]->addObject(x,y,index);
}

void MotaMap::delObject(int index)
{
    for(auto it:m_objectMap)
    {
        it->delObject(index);
    }
    emit objectDeleted(index);
}


QVector<Model2DObjectMap *> MotaMap::objectMap() const
{
    return m_objectMap;
}

Model2DObjectMap *MotaMap::getObjectMapByLayer(int layer)
{
    if(layer>=0 && layer<m_objectMap.size())
    {
        return m_objectMap[layer];
    }
    return nullptr;
}






int MotaMap::mapNetWidth() const
{
    return m_mapNetWidth;
}

void MotaMap::setMapNetWidth(int newMapNetWidth)
{
    if (m_mapNetWidth == newMapNetWidth)
        return;
    m_mapNetWidth = newMapNetWidth;
    emit mapNetWidthChanged();
}

int MotaMap::mapNetHeight() const
{
    return m_mapNetHeight;
}

void MotaMap::setMapNetHeight(int newMapNetHeight)
{
    if (m_mapNetHeight == newMapNetHeight)
        return;
    m_mapNetHeight = newMapNetHeight;
    emit mapNetHeightChanged();
}
