#include "motanpc.h"

MotaNPC::MotaNPC(QObject *parent)
    : GameObject{parent}
{
    setType(GameObject::NonPlayerCharacter);
    setClassName("MotaNPC");
    setSuperEdit(true);

    m_showCharacter=new ModelShowCharacter;
    m_myComponents.append(m_showCharacter);
    m_componentDictionary.insert("ShowCharacter",m_showCharacter);


    if(!m_registFlag)
    {
        //将处理策略注册进map中。
        //每个类进行一次初始化策略
        //m_soluteStratagies.insert("ChangeElement",changeElement);
        //已进行初始化策略
        m_registFlag=true;
    }
}

void MotaNPC::init(const QJsonObject *data)
{
    qDebug()<<"----MotaNPC::init----";

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

    QString name=data->value("Name").toString();
    setName(name);

    QString script=data->value("Script").toString();
    setScript(script);

    unsigned int mapId=data->value("LinkMapId").toInt();
    if(mapId)
    {
        m_linkMapId=mapId;

        emit linkMap(this);
    }
    qDebug()<<"mapId"<<m_linkMapId;
    GameObject::init(data);
    qDebug()<<"----MotaNPC::init----end";
}

void MotaNPC::tick()
{
 qDebug()<<"---Now Show the MotaNPC's Information---";
}

void MotaNPC::solutePacketData(InsPacketData *data)
{

}
QString MotaNPC::getStateIndexList()
{
 return m_showCharacter->getPixIndexList();
}

QVector<QString> MotaNPC::getStateStrList()
{
 QVector<QString> res;
 for(auto it:m_showCharacter->getStateList().split(","))
 {
        res.append(it);
 }
 return res;
}

QString MotaNPC::getStateListStr()
{
 return m_showCharacter->getStateList();
}

void MotaNPC::changeState(QString newState)
{
 m_showCharacter->setNowState(newState);
 emit stateChanged(newState);
}

void MotaNPC::changeState(GameObject *me, QVariant v)
{
 MotaNPC* Me=static_cast<MotaNPC*>(me);

 QString newState=v.toString();
 Me->changeState(newState);
}

int MotaNPC::linkMapId() const
{
 return m_linkMapId;
}

QJsonObject MotaNPC::getItemData()
{
 QJsonObject obj=GameObject::getItemData();

 return obj;
}



