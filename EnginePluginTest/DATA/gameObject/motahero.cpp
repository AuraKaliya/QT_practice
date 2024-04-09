#include "motahero.h"

MotaHero::MotaHero(QObject *parent)
    : GameObject{parent}
{
    setType(GameObject::PlayerCharacter);
    setClassName("MotaHero");
    setSuperEdit(true);

    m_showCharacter=new ModelShowCharacter;
    m_myComponents.append(m_showCharacter);
    m_componentDictionary.insert("ShowCharacter",m_showCharacter);


    m_battleBase=new ModelBattleBase;
    m_myComponents.append(m_battleBase);
    m_componentDictionary.insert("BattleBase",m_battleBase);


    m_motaBag=new ModelMotaBag;
    m_myComponents.append(m_motaBag);
    m_componentDictionary.insert("MotaBag",m_motaBag);


    if(!m_registFlag)
    {
        //将处理策略注册进map中。
        //每个类进行一次初始化策略
        //m_soluteStratagies.insert("ChangeElement",changeElement);
        //已进行初始化策略
        m_registFlag=true;
    }


}

void MotaHero::init(const QJsonObject *data)
{
    qDebug()<<"----MotaHero::init----";
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
        m_showCharacter->setStateList(stateList);

        QString stateIndexList=data->value("StateIndexList").toString();
        m_showCharacter->setPixIndexList(stateIndexList);
    }




    QString name=data->value("Name").toString();
    setName(name);

    QString script=data->value("Script").toString();
    setScript(script);

    unsigned int mapId=data->value("LinkMapId").toInt();
    if(mapId)
    {
        m_linkMapId=mapId;
        emit linkMap();
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

    if(data->contains("MotaBag"))
    {
        QJsonObject bagVal=data->value("MotaBag").toObject();

        int yellow=bagVal.value("YellowKey").toInt();
        int blue =bagVal.value("BlueKey").toInt();
        int red =bagVal.value("RedKey").toInt();

        m_motaBag->setYellowKey(yellow);
        m_motaBag->setBlueKey(blue);
        m_motaBag->setRedKey(red);
    }

    //qDebug()<<"mapId"<<m_linkMapId;
    qDebug()<<"Battle~";
    m_battleBase->tick();

    qDebug()<<"bag~~";
    m_motaBag->tick();


    GameObject::init(data);
    qDebug()<<"----MotaHero::init----end";
}

void MotaHero::tick()
{
    qDebug()<<"---Now Show the MotaHero's Information---";

    m_showCharacter->tick();

}

void MotaHero::solutePacketData(InsPacketData *data)
{

}

QJsonObject MotaHero::getItemData()
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

    QJsonObject bagObj;

    bagObj.insert("YellowKey",m_motaBag->yellowKey());
    bagObj.insert("BlueKey",m_motaBag->blueKey());
    bagObj.insert("RedKey",m_motaBag->redKey());
    obj.insert("MotaBag",bagObj);

    obj.insert("LinkMapId",m_linkMapId);

    return obj;
}

QString MotaHero::getStateIndexList()
{
    return m_showCharacter->getPixIndexList();
}

QVector<QString> MotaHero::getStateStrList()
{
    QVector<QString> res;
    for(auto it:m_showCharacter->getStateList().split(","))
    {
        res.append(it);
    }
    return res;
}

QString MotaHero::getStateListStr()
{
     return m_showCharacter->getStateList();
}

void MotaHero::changeState(QString newState)
{
    m_showCharacter->setNowState(newState);
    emit stateChanged(newState);
}

void MotaHero::changeState(GameObject *me, QVariant v)
{
    MotaHero* Me=static_cast<MotaHero*>(me);

    QString newState=v.toString();
    Me->changeState(newState);

}

int MotaHero::linkMapId() const
{
    return m_linkMapId;
}

unsigned int MotaHero::getATK()
{
    return m_battleBase->getATK();
}

unsigned int MotaHero::getDEF()
{
    return m_battleBase->getDEF();
}

unsigned int MotaHero::getHP()
{
    return m_battleBase->getHP();
}

bool MotaHero::getBattleState()
{
    return m_battleBase->getState();
}

void MotaHero::operator <<(MotaHero &obj)
{
    GameObject::operator <<(obj);


    m_linkMapId=obj.m_linkMapId;


}

ModelBattleBase *MotaHero::battleBase() const
{
    return m_battleBase;
}

ModelMotaBag *MotaHero::motaBag() const
{
    return m_motaBag;
}
