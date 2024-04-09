#include "motademo.h"

#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
MotaDemo* MotaDemo::m_instance=nullptr;
QMap<QString,TalkWithFunc> MotaDemo::m_talkWithDictionary={};
int MotaDemo::s_nowItemId=-1;
MotaHero *MotaDemo::motaHero() const
{
    return m_motaHero;
}

MotaMap *MotaDemo::motaMap() const
{
    return m_motaMap;
}

MotaMonster *MotaDemo::motaMonster(int idx)
{
    auto it=m_monsterDictionary.find(idx);
    if(it!=m_monsterDictionary.end())
    {
        return it.value();
    }
    return nullptr;

}

MotaNPC *MotaDemo::motaNPC(int idx)
{
    auto it=m_npcDictionary.find(idx);
    if(it!=m_npcDictionary.end())
    {
        return it.value();
    }
    return nullptr;
}

bool MotaDemo::addHero(MotaHero *hero)
{
    //替换型
    //因为已经有初始化，所以替换的是属性。

    int oldId=m_motaHero->getId();
    int newId=hero->getId();
    *m_motaHero<<(*hero);

    //添加到Dictionary中

    m_objectTypeDictionary[m_motaHero->getId()]=Hero;

    //属于obj----map中修改

        //清除原有hero
    m_motaMap->delObject(oldId);

        //添加新hero
    auto pos=posFromMapMatrix(QPoint(m_motaHero->getPosX(),m_motaHero->getPosY()));
    m_motaMap->addObject(m_motaMap->getNowLayer(),pos.first,pos.second,newId);


    emit heroChanged(oldId,newId);

    return true;
}

bool MotaDemo::addMap(MotaMap *)
{
    return true;
}

bool MotaDemo::addMonster(MotaMonster * monster, int posx, int posy)
{
    qDebug()<<"ADD Monster";
    m_objectTypeDictionary[monster->getId()]=Monster;

    m_motaMonsterList.append(monster);

    auto pos=posFromMapMatrix(QPoint(monster->getPosX(),monster->getPosY()));
    m_motaMap->addObject(m_motaMap->getNowLayer(),pos.first,pos.second,monster->getId());


    return true;
}

bool MotaDemo::addNPC(MotaNPC * npc, int posx, int posy)
{
    qDebug()<<"ADD NPC";



    int id=npc->getId();
    qDebug()<<npc->getId();
    m_objectTypeDictionary[npc->getId()]=NPC;

    m_motaNPCList.append(npc);
    m_npcDictionary.insert(npc->getId(),npc);

    auto pos=posFromMapMatrix(QPoint(posx,posy));
    int layer=m_motaMap->getNowLayer();
    int x=pos.first;
    int y=pos.second;

    qDebug()<<"layer: "<<layer;

    qDebug()<<x<<" "<<y;
    qDebug()<<" all: "<<motaMap()->objectMap();
    qDebug()<<motaMap()->getObjectMapByLayer(layer);
    qDebug()<<"------PRE  MAP:----";
    qDebug()<<motaMap()->getObjectMapByLayer(layer)->mapMatrix();
    qDebug()<<"--------------------";



    m_motaMap->addObject(layer,x,y,id);

    qDebug()<<"------NEXT  MAP:----";
    qDebug()<<motaMap()->getObjectMapByLayer(layer)->mapMatrix();
    qDebug()<<"--------------------";

    //添入objPosDictionary
    auto it=m_objPosDictionary.find(id);
    if(it==m_objPosDictionary.end())
    {

        //没有--添加
        m_objPosDictionary.insert(id,QVector<MotaObjectPos>{{layer,x,y}});
    }
    else
    {
        // 已有 --添加到后面
        qDebug()<<"find!";
        it.value().append({layer,x,y});
    }



    qDebug()<<"ADD NPC  end";
    return true;
}

QJsonObject MotaDemo::getDemoSource()
{
    //整体obj
    QJsonObject obj;

    obj.insert("Type","Demo");

    //具体的Demo：mota
    QJsonObject demoObj;

    demoObj.insert("Demo",objectName());

    //data内容
    QJsonObject packetDataObj;


    QVector<QString> packetList;
    for(auto it=m_element.begin();it!=m_element.end();++it)
    {
        packetList.append(it.key());

        QJsonObject gameObjectDataObj=it.value().second->getItemData();
        packetDataObj.insert(it.value().first,gameObjectDataObj);
    }

    for(auto it=m_elementList.begin();it!=m_elementList.end();++it)
    {
        packetList.append(it.key());

        QJsonObject gameObjectListDataObj;
        QJsonArray listDataArray;
        for(auto item:it.value())
        {
            QJsonObject gameObjectDataObj=item->getItemData();
            listDataArray.append(gameObjectDataObj);
        }
        gameObjectListDataObj.insert("List",listDataArray);
        packetDataObj.insert(it.key(),gameObjectListDataObj);
    }

    packetDataObj.insert("PacketSize",packetList.size());

    QJsonArray packetNamelist;
    for(auto it:m_elementSort)
    {
        packetNamelist.append(it);
    }

    for(auto it=m_elementList.begin();it!=m_elementList.end();++it)
    {
        packetNamelist.append(it.key());
    }
    packetDataObj.insert("PacketList",packetNamelist);

    //
    qDebug()<<"check----";


    qDebug()<<"element:"<<m_element;
    qDebug()<<"m_elementList:"<<m_elementList;
    qDebug()<<"m_elementSort:"<<m_elementSort;
    qDebug()<<"checkEND---";

    demoObj.insert("Data",packetDataObj);

    obj.insert("Data",demoObj);

    return obj;
}

QVector<MotaDemo::MotaObjectPos> MotaDemo::getMotaObjectPos(int id)
{
    auto it=m_objPosDictionary.find(id);
    if(it!=m_objPosDictionary.end())
    {
        return it.value();
    }else
    {
        qDebug()<<"未找到该obj的pos";
    }
    return QVector<MotaDemo::MotaObjectPos>();
}


MotaDemo::MotaDemo(QObject *parent)
    : GameDemo{parent}
{

    setObjectName("Mota");
    //固有/静态/唯一性的GameObject的初始化
    /*
        1. 初始化
        2. 将GO注册进SourceManager中
    */
    //1. 初始化
    m_motaMap=new MotaMap;
    m_motaHero=new MotaHero;

    //2. 注册  --在统一注册中，根据init的结果进行处理（通过文件创建/进行新建）
    m_element.insert("MotaMap",QPair<QString,GameObject*>("MotaMap",m_motaMap));
    m_elementSort.append("MotaMap");

    m_element.insert("MotaHero",QPair<QString,GameObject*>("MotaHero",m_motaHero));
    m_elementSort.append("MotaHero");

    //m_element.insert("MotaMonster",QPair<QString,GameObject*>("MotaMonster",m_motaMonster));
    m_elementList.insert("MotaMonster",*new QVector<GameObject*>());
    m_elementList.insert("MotaNPC",*new QVector<GameObject*>());

    m_talkWithDictionary.insert("YellowDoor",talkWithYelloDoor);
    m_talkWithDictionary.insert("BlueDoor",talkWithBlueDoor);
    m_talkWithDictionary.insert("RedDoor",talkWithRedDoor);

    m_talkWithDictionary.insert("YellowKey",talkWithYellowKey);
    m_talkWithDictionary.insert("BlueKey",talkWithBlueKey);
    m_talkWithDictionary.insert("RedKey",talkWithRedKey);

    m_talkWithDictionary.insert("UpLader",talkWithUpLader);
    m_talkWithDictionary.insert("DownLader",talkWithDownLader);

    m_talkWithDictionary.insert("SmallHPPotion",talkWithSmallHPPotion);
    m_talkWithDictionary.insert("BigHPPotion",talkWithBigHPPotion);
    m_talkWithDictionary.insert("ATKGem",talkWithATKGem);
    m_talkWithDictionary.insert("DEFGem",talkWithDEFGem);

    //异步初始化处理
    //link--绑定Hero和Map
    connect(m_motaHero,&MotaHero::linkMap,this,[this](){

        QPair<int,QPair<int,int>> heroPos=m_motaMap->getHeroPos();

        QPoint p=m_motaMap->getElementPoint(heroPos.first,heroPos.second.first,heroPos.second.second);
        int posX=p.x();
        int posY=p.y();
        m_motaHero->setPosX(posX);
        m_motaHero->setPosY(posY);
        m_motaHero->setPosInit(true);
    });

    connect(m_motaMap,&GameObject::initialized,this,[this](){
        setEnvState(true);
    });
    connect(m_motaHero,&GameObject::initialized,this,[this](){
        setPlayerState(true);
    });
}

void MotaDemo::heroMoveToNextElement(GameObject *hero, QVariant v)
{
    //Variant
    /*
        vector[direction(int)]
    */
    //MotaHero* Hero=static_cast<MotaHero*>(hero);
    qDebug()<<"---MotaDemo::heroMoveToNextElement---";
    MotaHero* Hero=m_instance->m_motaHero;

    //获取当前的地图坐标
    QPair<int,QPair<int,int>> heroPos=m_instance->m_motaMap->getHeroPos();
    qDebug()<<"heroPos:"<<heroPos;

    int nowLayer=heroPos.first;
    qDebug()<<"ValiedMap"<<m_instance->m_motaMap->getValiedMap(nowLayer);
    int nowX=heroPos.second.first;
    int nowY=heroPos.second.second;
    int nextX=nowX;
    int nextY=nowY;
    QVector<QVariant> tmpList=v.toList();

    //获取方向
    int direction=tmpList[0].toInt();
    //  0: 不动 1右 2上 3左 4下
    //处理
    switch (direction) {
    case 1:
    {
        nextX+=1;
    }
        break;
    case 2:
        nextY-=1;
        break;
    case 3:
        nextX-=1;
        break;
    case 4:
        nextY+=1;
        break;
    case 0:
    default:
        qDebug()<<"No Active!";
        return;
    }

    //qDebug()<<"NextPos:"<<nextX<<nextY <<m_instance->m_motaMap->elementIsValied(nowLayer,nextX,nextY);
    //判断是否可行
    if(m_instance->m_motaMap->elementIsValied(nowLayer,nextX,nextY))
    {
//        // 可行，item移动 -- obj的属性改变；
//        QParallelAnimationGroup  * animationGroup=new QParallelAnimationGroup;
//        QPropertyAnimation * animationX=new QPropertyAnimation(Hero,"posX");
//        QPropertyAnimation * animationY=new QPropertyAnimation(Hero,"posY");

//        animationGroup->addAnimation(animationX);
//        animationGroup->addAnimation(animationY);

//        animationX->setDuration(200);
//        animationY->setDuration(200);

//        animationX->setStartValue(Hero->getPosX());
//        animationY->setStartValue(Hero->getPosY());

//        QPoint p=m_instance->m_motaMap->getElementPoint(nowLayer,nextX,nextY);
//        animationX->setEndValue((double)p.x());
//        animationY->setEndValue((double)p.y());

//        connect(animationGroup,&QParallelAnimationGroup::finished,m_instance,[=](){
//            qDebug()<<"QParallelAnimationGroup::finished";
//            qDebug()<<nowLayer<<nowX<<nowY<<nextX<<nextY;
//            m_instance->m_motaMap->objectMove(nowLayer,nowX,nowY,nextX,nextY);
//             qDebug()<<"QParallelAnimationGroup::finished   ---end";
//        });
//        animationGroup->start(QAbstractAnimation::DeleteWhenStopped);




        m_instance->m_motaMap->objectMove(nowLayer,nowX,nowY,nextX,nextY);
    }
}

void MotaDemo::monsterMoveToNextElement(GameObject *monster, QVariant v)
{
    //Variant
    /*
        vector[direction(int)]
    */
    //MotaHero* Hero=static_cast<MotaHero*>(hero);
    qDebug()<<"---MotaDemo::heroMoveToNextElement---";
    MotaMonster* Monster=static_cast<MotaMonster*>(monster);

    //获取当前的地图坐标
    QPair<int,QPair<int,int>> monsterPos=m_instance->m_motaMap->findObjectPos(Monster->getId());
    qDebug()<<"heroPos:"<<monsterPos;

    int nowLayer=monsterPos.first;
    qDebug()<<"ValiedMap"<<m_instance->m_motaMap->getValiedMap(nowLayer);
    int nowX=monsterPos.second.first;
    int nowY=monsterPos.second.second;
    int nextX=nowX;
    int nextY=nowY;
    QVector<QVariant> tmpList=v.toList();

    //获取方向
    int direction=tmpList[0].toInt();
    //  0: 不动 1右 2上 3左 4下
    //处理
    switch (direction) {
    case 1:
    {
        nextX+=1;
    }
    break;
    case 2:
        nextY-=1;
        break;
    case 3:
        nextX-=1;
        break;
    case 4:
        nextY+=1;
        break;
    case 0:
    default:
        qDebug()<<"No Active!";
        return;
    }

    qDebug()<<"NextPos:"<<nextX<<nextY <<m_instance->m_motaMap->elementIsValied(nowLayer,nextX,nextY);
    //判断是否可行
    if(m_instance->m_motaMap->elementIsValied(nowLayer,nextX,nextY))
    {
        // 可行，item移动 -- obj的属性改变；
//        QParallelAnimationGroup  * animationGroup=new QParallelAnimationGroup;
//        QPropertyAnimation * animationX=new QPropertyAnimation(Monster,"posX");
//        QPropertyAnimation * animationY=new QPropertyAnimation(Monster,"posY");

//        animationGroup->addAnimation(animationX);
//        animationGroup->addAnimation(animationY);

//        animationX->setDuration(200);
//        animationY->setDuration(200);

//        animationX->setStartValue(Monster->getPosX());
//        animationY->setStartValue(Monster->getPosY());

//        QPoint p=m_instance->m_motaMap->getElementPoint(nowLayer,nextX,nextY);
//        animationX->setEndValue((double)p.x());
//        animationY->setEndValue((double)p.y());

//        connect(animationGroup,&QParallelAnimationGroup::finished,m_instance,[=](){
//            qDebug()<<"QParallelAnimationGroup::finished";
//            qDebug()<<nowLayer<<nowX<<nowY<<nextX<<nextY;
//            m_instance->m_motaMap->objectMove(nowLayer,nowX,nowY,nextX,nextY);
//            qDebug()<<"QParallelAnimationGroup::finished   ---end";
//        });
//        animationGroup->start(QAbstractAnimation::DeleteWhenStopped);
    m_instance->m_motaMap->objectMove(nowLayer,nowX,nowY,nextX,nextY);
    }
}

void MotaDemo::heroMoveToElement(GameObject *hero, QVariant v)
{
    //Variant
    /*
     * 直接移动Hero   包括跨层  --  不需要动画，只需要将Item移动/设置即可
     * 改英雄位置 改当前layer 切换view
        vector[layer(int),x(int),y(int)]
    */
    MotaHero* Hero=m_instance->m_motaHero;
    QVector<QVariant> tmpList=v.toList();
    int layer=tmpList[0].toInt();
    int x=tmpList[1].toInt();
    int y=tmpList[2].toInt();

    if(m_instance->m_motaMap->elementIsValied(layer,x,y))
    {
        // 可行，item移动 -- obj的属性改变；
        // 改变英雄位置
        m_instance->m_motaMap->objectMap()[m_instance->m_motaMap->getNowLayer()]->clearHero();
        m_instance->m_motaMap->objectMap()[layer]->setHeroPos(Hero->getId(),x,y);

        //改变当前layer
        qDebug()<<"**********check0;";
        qDebug()<<"nowLayer:"<<m_instance->m_motaMap->getNowLayer();
        qDebug()<<"nextLayer:"<<m_instance->m_motaMap->getNextLayer();
        qDebug()<<"linklist:"<<m_instance->m_motaMap->getTowerLink();
        m_instance->m_motaMap->nextLayer(layer);
        qDebug()<<"nowLayer:"<<m_instance->m_motaMap->getNowLayer();
        qDebug()<<"nextLayer:"<<m_instance->m_motaMap->getNextLayer();
        qDebug()<<"linklist:"<<m_instance->m_motaMap->getTowerLink();

        QPoint p=m_instance->m_motaMap->getElementPoint(layer,x,y);
        Hero->setPosX(p.x());
        Hero->setPosY(p.y());


        //改变当前View
        emit m_instance->layerChanged(layer);
    }
    else
    {
        qDebug()<<"error: element is no valied!"<< layer<<x<<y;
        qDebug()<<"this Layer:"<<m_instance->m_motaMap->getValiedMap(layer);
    }
}

void MotaDemo::heroMoveToLayer(GameObject *hero, QVariant v)
{
    //Variant
    /*
        vector[nextLayer(int)]
    */

    /*
     *
    */






}

void MotaDemo::heroMoveToNextLayer(GameObject *hero, QVariant v)
{
    //Variant
    /*
        0
    */

    /*
        1.获取当前层
        2.获取下一层-下一层位置
        3.移动角色
    */

    //int nowLayer=m_instance->m_motaMap->getNowLayer();

    qDebug()<<"-----MotaDemo::heroMoveToNextLayer----";
    qDebug()<<"Now Hero:"<<m_instance->m_motaMap->getHeroPos();

    int nextLayer=m_instance->m_motaMap->getNextLayer();
    qDebug()<<"nextLayer:"<<nextLayer;

    int x =m_instance->m_motaMap->getDownPos(nextLayer).first;
    int y =m_instance->m_motaMap->getDownPos(nextLayer).second;


    if(x!=-1&&y!=-1)
    {
        QVector<QVariant> list;
        list.append(QVariant(nextLayer));
        list.append(QVariant(x));
        list.append(QVariant(y));

        heroMoveToElement(m_instance->m_motaHero,QVariant(list));
    }
    else
    {
        qDebug()<<" warnning : 到头了！";
    }



    qDebug()<<"-----MotaDemo::heroMoveToNextLayer----end";
    qDebug()<<"Now Hero:"<<m_instance->m_motaMap->getHeroPos();

}

void MotaDemo::heroMoveToPreLayer(GameObject *hero, QVariant v)
{
    //Variant
    /*
        0
    */
    /*
        1.获取当前层
        2.获取上一层-上一层位置
        3.移动角色
    */

    int preLayer=m_instance->m_motaMap->getPreLayer();


    int x =m_instance->m_motaMap->getUpPos(preLayer).first;
    int y =m_instance->m_motaMap->getUpPos(preLayer).second;


    qDebug()<<"Test: CHECK:"<<x<<" "<<y;

    if(x!=-1 && y!=-1)
    {
        QVector<QVariant> list;
        list.append(QVariant(preLayer));
        list.append(QVariant(x));
        list.append(QVariant(y));

        heroMoveToElement(m_instance->m_motaHero,QVariant(list));
    }
    else
    {
        qDebug()<<" warnning : 到底了！";
    }


}

int MotaDemo::talkWithUpLader(MotaNPC *obj)
{
    int res=0;

    res=4;

    heroMoveToNextLayer(nullptr,QVariant());

    return res;
}

int MotaDemo::talkWithDownLader(MotaNPC *obj)
{
    int res=0;

    res=4;

    heroMoveToPreLayer(nullptr,QVariant());

    return res;
}

int MotaDemo::talkWithYelloDoor(MotaNPC *obj)
{
    int res=0;

    //检查hero包内是否有对应的钥匙

    if(m_instance->m_motaHero->motaBag()->yellowKey()>0)
    {
        res=3;
        //在这里进行处理了
        //开门动画

        //绘制状态改变
        //obj->setDrawState(false);
        emit obj->itemDrawStateChanged(s_nowItemId,false);

        //包内钥匙减一
        m_instance->m_motaHero->motaBag()->setYellowKey(m_instance->m_motaHero->motaBag()->yellowKey()-1);
    }
    else
    {
        res=4;

        //提示没钥匙了
    }
    return res;
}

int MotaDemo::talkWithBlueDoor(MotaNPC* obj)
{
    int res=0;
    //检查hero包内是否有对应的钥匙

    if(m_instance->m_motaHero->motaBag()->blueKey()>0)
    {
        res=3;
        //在这里进行处理了
        //开门动画

        //绘制状态改变
        //obj->setDrawState(false);
        emit obj->itemDrawStateChanged(s_nowItemId,false);
        //包内钥匙减一
        m_instance->m_motaHero->motaBag()->setBlueKey(m_instance->m_motaHero->motaBag()->blueKey()-1);
    }
    else
    {
        res=4;

        //提示没钥匙了

    }



    return res;
}

int MotaDemo::talkWithRedDoor(MotaNPC* obj)
{
    int res=0;

    if(m_instance->m_motaHero->motaBag()->redKey()>0)
    {
        res=3;
        //在这里进行处理了
        //开门动画


        //绘制状态改变
        //obj->setDrawState(false);
        emit obj->itemDrawStateChanged(s_nowItemId,false);

        //包内钥匙减一
        m_instance->m_motaHero->motaBag()->setRedKey(m_instance->m_motaHero->motaBag()->redKey()-1);
    }
    else
    {
        res=4;
        //提示没钥匙了
    }
    return res;
}

int MotaDemo::talkWithSprite(MotaNPC *obj)
{
    int res=0;
    return res;
}

int MotaDemo::talkWithYellowKey(MotaNPC *obj)
{
    int res=0;

    res=3;

    emit obj->itemDrawStateChanged(s_nowItemId,false);
    m_instance->m_motaHero->motaBag()->setYellowKey(m_instance->m_motaHero->motaBag()->yellowKey()+1);

    return res;
}

int MotaDemo::talkWithBlueKey(MotaNPC *obj)
{
    int res=0;

    res=3;
    emit obj->itemDrawStateChanged(s_nowItemId,false);
    m_instance->m_motaHero->motaBag()->setBlueKey(m_instance->m_motaHero->motaBag()->blueKey()+1);

    return res;
}

int MotaDemo::talkWithRedKey(MotaNPC *obj)
{
    int res=0;

    res=3;
    emit obj->itemDrawStateChanged(s_nowItemId,false);
    m_instance->m_motaHero->motaBag()->setRedKey(m_instance->m_motaHero->motaBag()->redKey()+1);

    return res;
}

int MotaDemo::talkWithSmallHPPotion(MotaNPC *obj)
{
    int res=0;

    res=3;
    emit obj->itemDrawStateChanged(s_nowItemId,false);

    return res;
}

int MotaDemo::talkWithBigHPPotion(MotaNPC *obj)
{

    qDebug()<<" talk with big hpPotion!";
    int res=0;

    res=3;
    emit obj->itemDrawStateChanged(s_nowItemId,false);

    return res;
}

int MotaDemo::talkWithATKGem(MotaNPC *obj)
{
    int res=0;

    res=3;
    emit obj->itemDrawStateChanged(s_nowItemId,false);

    return res;
}

int MotaDemo::talkWithDEFGem(MotaNPC *obj)
{
    int res=0;

    res=3;
    emit obj->itemDrawStateChanged(s_nowItemId,false);

    return res;
}

void MotaDemo::objectMoved(int id, int x, int y)
{
    //判断id对应的种类
    auto it=m_objectTypeDictionary.find(id);
    if(it!=m_objectTypeDictionary.end())
    {
        switch (it.value()) {
        case Hero:
        {
            //hero
            animationHeroMoved(x,y);
        }
        break;
        case Monster:
        {
            //monster   找到具体的monster
            auto it2=m_monsterDictionary.find(id);
            if(it2!=m_monsterDictionary.end())
            {
                animationMonsterMoved(it2.value(),x,y);
            }
            else
            {

            }
        }
        break;
        default:
            break;
        }
    }
    else
    {

    }
}

int MotaDemo::objectOverLaped(int id1, int id2)
{
    //判断重叠类型： 类似linux的处理方式： hero=1， NPC=4， Monster=2

    qDebug()<<" obj overlap!"<<id1<<" "<<id2;
    int res = 0 ;
    if (m_motaHero->getId() == id1) {
        //英雄相关--发射处理信号--二级传递处理，等待结果返回
        res = heroActive(id2);
    }
    else if(m_motaHero->getId()==id2)
    {
        //英雄相关--发射处理信号--二级传递处理，等待结果返回
        res=heroActive(id1);
    }


    return res;
}

void MotaDemo::animationHeroMoved( int newX, int newY)
{
    MotaHero* Hero=m_instance->m_motaHero;

    QParallelAnimationGroup  * animationGroup=new QParallelAnimationGroup;
    QPropertyAnimation * animationX=new QPropertyAnimation(Hero,"posX");
    QPropertyAnimation * animationY=new QPropertyAnimation(Hero,"posY");

    animationGroup->addAnimation(animationX);
    animationGroup->addAnimation(animationY);

    animationX->setDuration(200);
    animationY->setDuration(200);

    animationX->setStartValue(Hero->getPosX());
    animationY->setStartValue(Hero->getPosY());

    QPoint p=m_instance->m_motaMap->getElementPoint(m_instance->m_motaMap->getHeroPos().first,newX,newY);
    animationX->setEndValue((double)p.x());
    animationY->setEndValue((double)p.y());

    connect(animationGroup,&QParallelAnimationGroup::finished,m_instance,[=](){
        qDebug()<<"QParallelAnimationGroup::finished";
        qDebug()<<"QParallelAnimationGroup::finished   ---end";
    });
    animationGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void MotaDemo::animationMonsterMoved(MotaMonster *monster, int newX, int newY)
{

    QParallelAnimationGroup  * animationGroup=new QParallelAnimationGroup;
    QPropertyAnimation * animationX=new QPropertyAnimation(monster,"posX");
    QPropertyAnimation * animationY=new QPropertyAnimation(monster,"posY");

    animationGroup->addAnimation(animationX);
    animationGroup->addAnimation(animationY);

    animationX->setDuration(200);
    animationY->setDuration(200);

    animationX->setStartValue(monster->getPosX());
    animationY->setStartValue(monster->getPosY());

    QPoint p=m_instance->m_motaMap->getElementPoint(m_instance->m_motaMap->findObjectPos(monster->getId()).first,newX,newY);
    animationX->setEndValue((double)p.x());
    animationY->setEndValue((double)p.y());

    connect(animationGroup,&QParallelAnimationGroup::finished,m_instance,[=](){
        qDebug()<<"QParallelAnimationGroup::finished";
        qDebug()<<"QParallelAnimationGroup::finished   ---end";
    });
    animationGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

int MotaDemo::heroBattleWithMonster(MotaMonster * monster)
{

    //res   1:win  2:lost
    int res=-1;

    qDebug()<<"#### heroBattleWithMonster: "<<monster;
    QString eventStr="Hero battle with Monster:"+monster->getName();
    emit m_instance->eventSend(eventStr);
    //start --
    emit m_instance->battleStart(m_instance->m_motaHero,monster);
    // 此处进行逻辑处理
    int winId=0;

    unsigned int obj1Id=m_instance->m_motaHero->getId();
    unsigned int obj2Id=monster->getId();

    unsigned int obj1ATK=m_instance->m_motaHero->getATK();
    unsigned int obj2ATK=monster->getATK();

    unsigned int obj1DEF=m_instance->m_motaHero->getDEF();
    unsigned int obj2DEF=monster->getDEF();

    int obj1HP=m_instance->m_motaHero->getHP();
    int obj2HP=monster->getHP();

    qDebug()<<"check0:"<<obj1Id<<obj1ATK<<obj1DEF<<obj1HP;
    qDebug()<<"check1:"<<obj2Id<<obj2ATK<<obj2DEF<<obj2HP;


    int turn=0;
    while(obj1HP>0||obj2HP>0||turn>1000)
    {
        if(obj1ATK>obj2DEF)
        {
          obj2HP-= (obj1ATK-obj2DEF);
          if(obj2HP<=0)
          {
            break;
          }
        }

        if(obj2ATK>obj1DEF)
        {
          obj1HP-= (obj2ATK-obj1DEF);
        }
        turn++;
    }

    //战斗结束
    if(obj2HP<=0)
    {
        winId=obj1Id;
        m_instance->m_motaHero->battleBase()->setHP(obj1HP);
        //monster->setDrawState(false);
        emit monster->itemDrawStateChanged(s_nowItemId,false);
        res=1;
    }

    if(obj1HP<=0)
    {
        winId=obj2Id;
        res=2;
    }

    //test
    qDebug()<<"MotaDemo::heroBattleWithMonster :winner:"<<winId <<obj1HP;
    //

    //end--
    emit m_instance->battleEnd(m_instance->m_motaHero,monster,winId);
    return res;
}

int MotaDemo::heroTalkWithNPC(MotaNPC *npc)
{
    int res=0;

    //获取NPC名字，从字典中选择相应的talkwith函数进行处理。
    //

    QString name=npc->getName();
    qDebug()<<"hero talk with NPC:"<<name;
    QString eventStr="Hero talk with NPC:"+name;

    emit getInstance()->eventSend(eventStr);

    auto it=m_talkWithDictionary.find(name);
    if(it!=m_talkWithDictionary.end())
    {
        res=it.value()(npc);
    }
    else
    {

    }

    return res;
}

QMap<int, QVector<MotaDemo::MotaObjectPos> > MotaDemo::objPosDictionary() const
{
    return m_objPosDictionary;
}

MotaDemo *MotaDemo::getInstance()
{
    if(m_instance==nullptr)
    {
        m_instance=new MotaDemo;
    }
    return m_instance;
}

void MotaDemo::init(const QJsonObject *obj)
{
    QJsonObject data =obj->value("Data").toObject();

    for(auto it:data.value("PacketList").toArray())
    {
        QString packetName=it.toString();
        qDebug()<<"MotaDemo::init"<<packetName;
        QJsonObject tmp=data.value(packetName).toObject();
        if(m_element.find(packetName)!=m_element.end())
        {
            m_element[packetName].second->init(&tmp);
        }
        else if(tmp.contains("List"))
        {
            for(auto item:tmp.value("List").toArray())
            {
                GameObject* obj=Factory<GameObject>::GetInstance()->CreateObject(packetName);
                qDebug()<<"item"<<item.toVariant()<<"\n\n"<<item.isObject()<<item.toObject();
                QJsonObject tmp2=item.toObject();

                //得想办法把obj给加入到List中
                if(obj->getClassName()=="MotaMonster")
                {
                    MotaMonster* monster=static_cast<MotaMonster*>(obj);
                    m_motaMonsterList.append(monster);
                    connect(monster,&MotaMonster::linkMap,this,[this](GameObject* obj){
                        qDebug()<<"MotaMonster::linkMap--"<<obj->getId()<<obj->getClassName();
                        QPair<int,QPair<int,int>> objPos=m_motaMap->findObjectPos(obj->getId());
                        if(objPos.first!=-1)
                        {
                            QPoint p=m_motaMap->getElementPoint(objPos.first,objPos.second.first,objPos.second.second);
                            int posX=p.x();
                            int posY=p.y();
                            obj->setPosX(posX);
                            obj->setPosY(posY);
                            obj->setPosInit(true);
                        }
                    });
                }
                else if(obj->getClassName()=="MotaNPC")
                {
                    MotaNPC* npc=static_cast<MotaNPC*>(obj);
                    m_motaNPCList.append(npc);
                    connect(npc,&MotaNPC::linkMap,this,[this](GameObject* obj){
                        qDebug()<<"MotaNPC::linkMap--"<<obj->getId()<<obj->getClassName();
                        QPair<int,QPair<int,int>> objPos=m_motaMap->findObjectPos(obj->getId());
                        if(objPos.first!=-1)
                        {
                            QPoint p=m_motaMap->getElementPoint(objPos.first,objPos.second.first,objPos.second.second);
                            int posX=p.x();
                            int posY=p.y();
                            obj->setPosX(posX);
                            obj->setPosY(posY);
                            obj->setPosInit(true);
                        }
                    });
                }
                obj->init(&tmp2);
                m_elementList[packetName].append(obj);

            }
        }

    }


//    for(auto it=m_element.begin();it!=m_element.end();++it)
//    {
//        if(data.contains(it.key()))
//        {
//            //qDebug()<<"!!!!MotaDemo::init!!!!"<<it.key();
//            QJsonObject tmp=data.value(it.key()).toObject();
//            it.value().second->init(&tmp);
//        }
//    }

    //对m_objPosDictionary进行初始化
    //通过获取map中的objmap进行
    auto objMapList=m_motaMap->objectMap();
    for(int i=0;i<objMapList.size();++i)
    {
        auto mapMatrix=objMapList[i]->mapMatrix();
        for(int y=0;y<mapMatrix.size();++y)
        {
            for(int x=0;x<mapMatrix[y].size();++x)
            {
                if(mapMatrix[y][x]!=0)
                {
                    //不为0 代表此处有obj
                    auto it= m_objPosDictionary.find(mapMatrix[y][x]);
                    if(it==m_objPosDictionary.end())
                    {
                        //没有  添加
                        m_objPosDictionary.insert(mapMatrix[y][x],QVector<MotaObjectPos>{{i,x,y}});
                    }else
                    {
                        //已有  加后面
                        it.value().append({i,x,y});
                    }
                }
            }
        }
    }

    qDebug()<<"CHECK----: obj-PosDictionary:";
    for(auto it=m_objPosDictionary.begin();it!=m_objPosDictionary.end();++it)
    {
        qDebug()<<it.key()<<"--{";
        for(auto it2:it.value())
        {
            qDebug()<<it2.layer<<","<<it2.x<<","<<it2.y;
        }
        qDebug()<<"--}";
    }
    qDebug()<<"CHECK----: obj-PosDictionary:  ---end";


    //初始化完成后，进行连接
    //connect    --在最高级类处进行统一的connect处理（最外层）  --通过指针

    //motamap--objectMap
    for(auto it:m_motaMap->objectMap())
    {
        it->setSignalLinkObj(this);
        //connect(it,SIGNAL(ObjectOverLap(int,int,int,int)),this,SLOT(solveObjectOverLap(int,int,int,int)));
        connect(it,&Model2DObjectMap::objectMoved,this,[this](Model2DObjectMap* map,int index,int oX,int oY,int nX,int nY){
            this->objectMoved(index,nX,nY);
            map->setElement(oX,oY,0);
            map->setElement(nX,nY,index);
        });

        connect(it,&Model2DObjectMap::objectOverlaped,this,[this](Model2DObjectMap* map,int index1,int x1,int y1,int index2,int x2,int y2){
            //先判断是何类型的重叠： hero-monster hero-NPC
            //根据类型调用处理函数，返回处理结果值res
            //根据res执行不同的后续处理
            //  battle 1:win  2:lost   npc: 3:NPC消失  4：NPC不消失
            // 有hero 参与的情况  index1一定是hero

            //这里进行item的确定，在每次overlaped时于demo中动态化
            qDebug()<<"---check getitemID-----"<<x2<<y2<<map->getItemId(x2,y2)<<" x1:"<<x1<<x2<<map->getItemId(x1,y1);
            qDebug()<<map->mapMatrix();
            qDebug()<<"---check getitemID-----end";

            setNowItemId(map->getItemId(x2,y2));

            int res=this->objectOverLaped(index1,index2);
            qDebug()<<"objectOverlap soluted res="<<res;
            switch (res) {
            case 1:
            {
                map->setElement(x2,y2,0);
            }
                break;
            case 2:
            {
                qDebug()<<"lost!!!!! gameover!!!!";
            }
            break;
            case 3:
            {
                map->setElement(x2,y2,0);
            }
            break;
            case 4:
            {

            }
            break;
            default:
                break;
            }
            resetNowItemId();
        });

    }

//    connect(m_motaMap,&MotaMap::objectMoved,this,[this](int id,int x,int y){
//            //
//    });

    registToManager();
}

void MotaDemo::registToManager()
{
    qDebug()<<"---MotaDemo::registToManager---";


    //对自己注册
    m_objectTypeDictionary[m_motaHero->getId()]=Hero;



    for(auto it:m_motaMonsterList)
    {
        m_objectTypeDictionary[it->getId()]=Monster;
        m_monsterDictionary[it->getId()]=it;
    }

    for(auto it:m_motaNPCList)
    {
        m_objectTypeDictionary[it->getId()]=NPC;
        m_npcDictionary[it->getId()]=it;
    }

    /*
     *  将Demo的指令进行注册
        将该Demo中的所有GO向SourceManager进行注册
        1.从文件中读取的资产应该具有已标准化的ID
        2.对新建的ID进行依靠Source自己处理。
        3.在source生成Demo配置文件时再进行统一的标准化处理。
        4.注册GameObject类、所含组件和属性。
    */

    //将demo的func--指令处理进行建立。
    emit demoFuncRegistToManager(heroMoveToNextElement,"heroMoveToNextElement");
    emit demoFuncRegistToManager(monsterMoveToNextElement,"monsterMoveToNextElement");
    emit demoFuncRegistToManager(heroMoveToElement,"heroMoveToElement");
    emit demoFuncRegistToManager(heroMoveToLayer,"heroMoveToLayer");
    emit demoFuncRegistToManager(heroMoveToNextLayer,"heroMoveToNextLayer");
    emit demoFuncRegistToManager(heroMoveToPreLayer,"heroMoveToPreLayer");

    //将demo的func--指令处理进行建立。


    //将demo中含有的所有GameObject种类进行注册
    emit objectRegistToManager(new MotaMap(m_motaMap),"MotaMap");
    emit objectRegistToManager(new MotaHero(m_motaHero),"MotaHero");

    for(auto it:m_motaMonsterList)
    {
       emit objectRegistToManager(new MotaMonster(it),"MotaMonster");


    }

    for(auto it:m_motaNPCList)
    {
       emit objectRegistToManager(new MotaNPC(it),"MotaNPC");


    }


    //将demo中含有的所有GameObject进行建立

    qDebug()<<"---check0:"<<m_motaMap->getId()<<m_motaMap->getPixIdList();

    if(m_motaMap->getId()!=0)
    {
        emit objectCreatedFromFile(m_motaMap,m_motaMap->getId());

    }
    else
    {
        emit objectCreated(m_motaMap);
    }


    qDebug()<<"---check1:"<<m_motaHero->getId()<<m_motaHero->getPixIdList();
    if(m_motaHero->getId()!=0)
    {
        emit objectCreatedFromFile(m_motaHero,m_motaHero->getId());
    }
    else
    {
        emit objectCreated(m_motaHero);
    }


    for(auto it:m_motaMonsterList)
    {
        if(it->getId()!=0)
        {
            emit objectCreatedFromFile(it,it->getId());
        }
        else
        {
            emit objectCreated(it);
        }
    }

    for(auto it:m_motaNPCList)
    {
        if(it->getId()!=0)
        {
            emit objectCreatedFromFile(it,it->getId());
        }
        else
        {
            emit objectCreated(it);
        }
    }

    setInitState(true);
    qDebug()<<"---MotaDemo::registToManager---end";
}

int MotaDemo::heroActive(int objectId)
{
    int res =0;
    qDebug()<<"#### heroActive:"<<objectId;

    auto it=m_objectTypeDictionary.find(objectId);
    if(it!=m_objectTypeDictionary.end())
    {
        qDebug()<<" active find!";
        switch (it.value()) {
        case Monster:
        {
            qDebug()<<" Monster!";
            auto monster= m_monsterDictionary.find(objectId);
            if(monster!=m_monsterDictionary.end())
            {
                res=heroBattleWithMonster(monster.value());
            }
        }
            break;
        case NPC:
        {
            qDebug()<<" NPC!";
            auto npc= m_npcDictionary.find(objectId);
            if(npc!=m_npcDictionary.end())
            {
                qDebug()<<"npc find!";
                res= heroTalkWithNPC(npc.value());
            }else
            {
                qDebug()<<" npc no find! ";
                qDebug()<<m_npcDictionary;
                qDebug()<<"----";
                qDebug()<<objectId;

            }
        }
            break;
        default:
            qDebug()<<"NO FIND!";
            break;
        }
    }
    return res;
}

void MotaDemo::setNowItemId(int id)
{

    s_nowItemId=id;
}

void MotaDemo::resetNowItemId()
{
    s_nowItemId=-1;
}

QPoint MotaDemo::posFromMap(QPoint point)
{
    //检查初始化 --是否设置了map的size 和 realsize

    //判断point在map的哪个区域
    int mapXInterval=m_motaMap->getMapInterval(m_motaMap->getNowLayer()).first;
    int mapYInterval=m_motaMap->getMapInterval(m_motaMap->getNowLayer()).second;

    int w=point.x();
    int h=point.y();


    int x=w/mapXInterval;
    int y=h/mapYInterval;


    return m_motaMap->getElementPoint(m_motaMap->getNowLayer(),x,y);

    // 返回对应的point

}

QPair<int, int> MotaDemo::posFromMapMatrix(QPoint point)
{
    int nowLayer=m_motaMap->getNowLayer();
    int mapXInterval=m_motaMap->getMapInterval(nowLayer).first;
    int mapYInterval=m_motaMap->getMapInterval(nowLayer).second;

    int w=point.x();
    int h=point.y();


    int x=w/mapXInterval;
    int y=h/mapYInterval;


    if(x>=m_motaMap->objectMap()[nowLayer]->getMapWidth())
        x=m_motaMap->objectMap()[nowLayer]->getMapWidth()-1;

    if(y>=m_motaMap->objectMap()[nowLayer]->getMapWidth())
        y=m_motaMap->objectMap()[nowLayer]->getMapWidth()-1;

    return QPair<int, int>(x,y);
}

void MotaDemo::solveObjectOverLap(int obj1Id, int obj2Id, int newX, int newY)
{
    qDebug()<<"####rece    ObjectOverLap " <<obj1Id <<obj2Id<<newX<<newY;
 //判断是否是英雄相关
    if(m_motaHero->getId()==obj1Id)
    {
       //英雄相关--发射处理信号--二级传递处理，等待信号返回
        heroActive(obj2Id);
    }
    else if(m_motaHero->getId()==obj2Id)
    {
        //英雄相关--发射处理信号--二级传递处理，等待信号返回
        heroActive(obj1Id);
    }
    else
    {
        //其他碰撞/重叠
    }

}


