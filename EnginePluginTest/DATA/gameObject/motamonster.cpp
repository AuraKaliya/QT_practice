#include "motamonster.h"

MotaMonster::MotaMonster(QObject *parent)
    : GameObject{parent}
{
    setType(GameObject::NonPlayerCharacter);
    setClassName("MotaMonster");
    setSuperEdit(true);

    m_showCharacter=new ModelShowCharacter;
    m_myComponents.append(m_showCharacter);
    m_componentDictionary.insert("ShowCharacter",m_showCharacter);

    m_battleBase=new ModelBattleBase;
    m_myComponents.append(m_battleBase);
    m_componentDictionary.insert("BattleBase",m_battleBase);

    if(!m_registFlag)
    {
        //将处理策略注册进map中。
        //每个类进行一次初始化策略
        //m_soluteStratagies.insert("ChangeElement",changeElement);
        //已进行初始化策略
        m_registFlag=true;
    }
}

void MotaMonster::init(const QJsonObject *data)
{
    qDebug()<<"----MotaMonster::init----";
    //属性--统一读取
    unsigned int id=data->value("Id").toInt();
    setId(id);

    unsigned int type=data->value("Type").toInt();
    setType(static_cast<Type>(type));

    if(data->contains("Pos"))
    {
        double objPosX=data->value("Pos").toArray().at(0).toDouble();
        double objPosY=data->value("Pos").toArray().at(0).toDouble();
        setPosX(objPosX);
        setPosY(objPosY);
        setPosInit(true);
    }else
    {
        setPosInit(false);
    }

    unsigned int objWidth=data->value("Size").toArray().at(0).toInt();
    unsigned int objHeight=data->value("Size").toArray().at(0).toInt();
    setWidth(objWidth);
    setHeight(objHeight);

    int sourcePipe=data->value("SourcePipe").toInt();
    if(sourcePipe==1)
    {
        setPixSourceFlag(true);
        QString pixIdList=data->value("PixSourceId").toString();
        setPixIdList(pixIdList);
        setPixId(pixIdList.toUInt());

    }else
    {
        QString pixIdList=data->value("PixIdList").toString();
        setPixIdList(pixIdList);

        QString multiplePix=data->value("MultiplePix").toString();
        setPixId(multiplePix.toUInt());


        QString stateList=data->value("StateList").toString();
        QString stateIndexList=data->value("StateIndexList").toString();

        m_showCharacter->setStateList(stateList);
        m_showCharacter->setPixIndexList(stateIndexList);
    }

//    QString pixIdList=data->value("PixIdList").toString();
//    setPixIdList(pixIdList);

    QString name=data->value("Name").toString();
    setName(name);


//    QString multiplePix=data->value("MultiplePix").toString();
//    setPixId(multiplePix.toUInt());


//    QString stateList=data->value("StateList").toString();
//    QString stateIndexList=data->value("StateIndexList").toString();

//    m_showCharacter->setStateList(stateList);
//    m_showCharacter->setPixIndexList(stateIndexList);

    QString script=data->value("Script").toString();
    setScript(script);

    unsigned int mapId=data->value("LinkMapId").toInt();
    if(mapId)
    {
        m_linkMapId=mapId;

        emit linkMap(this);
    }

    if(data->contains("Battle"))
    {
        QJsonObject battleVal=data->value("Battle").toObject();

        unsigned int atk=battleVal.value("ATK").toInt();
        unsigned int def=battleVal.value("DEF").toInt();
        unsigned int hp=battleVal.value("HP").toInt();
        bool state=battleVal.value("State").toBool();

        m_battleBase->setATK(atk);
        m_battleBase->setDEF(def);
        m_battleBase->setHP(hp);
        m_battleBase->setState(state);
    }
    //qDebug()<<"mapId"<<m_linkMapId;
    qDebug()<<"Battle~";
    m_battleBase->tick();
    GameObject::init(data);
    qDebug()<<"----MotaMonster::init----end";
}

void MotaMonster::tick()
{
    qDebug()<<"---Now Show the MotaMonster's Information---";
}

void MotaMonster::solutePacketData(InsPacketData *data)
{

}

QString MotaMonster::getStateIndexList()
{
    qDebug()<<"MotaMonster::getStateIndexList()";
    qDebug()<<"m_showCharacter:"<<m_showCharacter;
    return m_showCharacter->getPixIndexList();
}

QVector<QString> MotaMonster::getStateStrList()
{
    qDebug()<<"MotaMonster::getStateStrList";
    QVector<QString> res;
    for(auto it:m_showCharacter->getStateList().split(","))
    {
        res.append(it);
    }
    qDebug()<<"check1---002";
    return res;
}

QString MotaMonster::getStateListStr()
{
    return m_showCharacter->getStateList();
}

void MotaMonster::changeState(QString newState)
{
    m_showCharacter->setNowState(newState);
    emit stateChanged(newState);
}

void MotaMonster::changeState(GameObject *me, QVariant v)
{
    MotaMonster* Me=static_cast<MotaMonster*>(me);

    QString newState=v.toString();
    Me->changeState(newState);
}

int MotaMonster::linkMapId() const
{
    return m_linkMapId;
}

QJsonObject MotaMonster::getItemData()
{
    QJsonObject obj=GameObject::getItemData();


    obj.insert("MultiplePix",QString::number(getPixId()));
    obj.insert("StateList",m_showCharacter->getStateList());
    obj.insert("StateIndexList",m_showCharacter->getPixIndexList());

    QJsonObject battleObj;

    battleObj.insert("ATK",(int)m_battleBase->getATK());
    battleObj.insert("DEF",(int)m_battleBase->getDEF());
    battleObj.insert("HP",(int)m_battleBase->getHP());
    battleObj.insert("State",m_battleBase->getState());
    obj.insert("Battle",battleObj);


    obj.insert("LinkMapId",m_linkMapId);

    return obj;
}

unsigned int MotaMonster::getATK()
{
    return m_battleBase->getATK();
}

unsigned int MotaMonster::getDEF()
{
    return m_battleBase->getDEF();
}

unsigned int MotaMonster::getHP()
{
    return m_battleBase->getHP();
}

bool MotaMonster::getBattleState()
{
    return m_battleBase->getState();
}


