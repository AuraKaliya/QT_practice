#include "gameobjectitem.h"

QVector<QString> GameObjectItem::s_layers={"Default"};
int GameObjectItem::s_defaultLayerIdx=0;
int GameObjectItem::s_layersHeight=100;
unsigned int GameObjectItem::globalId=8000001;
GameObjectItem::GameObjectItem(GameObject*obj,QObject *parent):QObject{parent},m_nowLayer(0),m_nowZValue(0)
{
    setLinkObj(obj);
    if(obj==nullptr)
    {
        m_objPix=QPixmap(":/RESOURCE/default/GameObjectDefaultPix.png").scaled(200,200);
        m_pixType=Single;
        m_pixList.clear();
        m_pixList.resize(1);
        m_pixList.append(m_objPix);
        m_pixRect=m_objPix.rect();
    }

    init();
}

GameObjectItem::GameObjectItem(GameObject *obj, QPixmap pix,QObject *parent):QObject{parent},m_pixType(Single),m_objPix(pix),m_nowLayer(0),m_nowZValue(0)
{
    if(obj!=nullptr)
    {
        setLinkObj(obj);
    }

    m_pixList.clear();
    m_pixList.resize(1);
    m_pixList.append(m_objPix);
    m_pixRect=m_objPix.rect();

    init();
}

QRectF GameObjectItem::boundingRect() const
{
   //QRect rect=m_objPix.scaled(m_pixRect.width(),m_pixRect.height(),Qt::KeepAspectRatio,Qt::SmoothTransformation).rect();
   return QRectF(0,0,m_pixRect.width(),m_pixRect.height());
}

void GameObjectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   if(state())
   {
        painter->drawPixmap(0,0,m_objPix.scaled(m_pixRect.width(),m_pixRect.height(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
   }
}

GameObject *GameObjectItem::getLinkObj() const
{
    return m_linkObj;
}

void GameObjectItem::setLinkObj(GameObject *newLinkObj)
{
    if(m_linkObj!=nullptr)
    {
        //需要取消先前的连接
    }

    m_linkObj = newLinkObj;

    //setSyncPos(true);

}

QPixmap GameObjectItem::getObjPix() const
{
    return m_objPix;
}

void GameObjectItem::setObjPix(QPixmap newObjPix)
{
    m_objPix = newObjPix;

}

QVector<QString> GameObjectItem::getLayers()
{
    return s_layers;
}

bool GameObjectItem::addLayer(QString layerName)
{
    s_layers.append(layerName);
    return true;
}

bool GameObjectItem::delLayer(int i)
{
    if(i==s_defaultLayerIdx)
        return false;
    else
        s_layers.removeAt(i);
    return true;
}

void GameObjectItem::swapLayer(int i, int j)
{
    QString tmp=s_layers[i];
    s_layers[i]=s_layers[j];
    s_layers[j]=tmp;

    if(i==s_defaultLayerIdx||j==s_defaultLayerIdx)
    {
        updateDefaultLayerIdx();
    }
}

QString GameObjectItem::getLayerById(int i)
{
    if(i<s_layers.size())
    return s_layers[i];
    else return "Error";
}

void GameObjectItem::updateDefaultLayerIdx()
{
    int i=s_layers.indexOf("Default");
    s_defaultLayerIdx=i;
}

void GameObjectItem::registerId(GameObjectItem *item)
{
    item->setId(globalId);
    globalId++;
}

int GameObjectItem::getNowZValue() const
{
    return m_nowZValue;
}

void GameObjectItem::setNowZValue(int newNowZValue)
{
    m_nowZValue = newNowZValue;
    setZValue(m_nowZValue+((s_defaultLayerIdx-m_nowLayer)*s_layersHeight));
    qDebug()<<"ZValueChanged "<<zValue();
}

void GameObjectItem::setSyncPos(bool flag)
{
    if(m_linkObj!=nullptr)
    {
        if(flag)
        {
            connect(m_linkObj,&GameObject::posXChanged,this,[this](){
                //qDebug()<<" GameObject::posXChanged ,nowPos"<<m_linkObj->getPosX()<<m_linkObj->getPosY();
                m_posXFlag=true;
                posChanged();
            });
            connect(m_linkObj,&GameObject::posYChanged,this,[this](){
                //qDebug()<<" GameObject::posYChanged ,nowPos"<<m_linkObj->getPosX()<<m_linkObj->getPosY();
                m_posYFlag=true;
                posChanged();
            });
        }
    }
}

int GameObjectItem::getNowLayer() const
{
    return m_nowLayer;
}

void GameObjectItem::setNowLayer(int newNowLayer)
{
    m_nowLayer = newNowLayer;

}

QVector<QPixmap> GameObjectItem::getPixList() const
{
    return m_pixList;
}

void GameObjectItem::setPixList(const QVector<QPixmap> &newPixList)
{
    m_pixList = newPixList;
}

void GameObjectItem::setPixType(PixType type)
{
    m_pixType=type;
}

void GameObjectItem::setPixScale(QRect rect)
{
    //qDebug()<<"GameObjectItem::setPixScale";
    m_pixRect=rect;
    emit resetPixScale();
}

void GameObjectItem::start()
{
    m_timer=new QTimer;
    m_timer->setInterval(m_interval);
    QObject::connect(m_timer,&QTimer::timeout,this,[this](){
        if(m_pixType==Single)
        {
            end();
        }
        else if(m_pixType==Multiple)
        {
            if(m_nowPixIdx<m_pixList.size()-1) m_nowPixIdx++;
            else m_nowPixIdx=0;
        }
        m_objPix=m_pixList[m_nowPixIdx];
    });
    m_timer->start();
}

void GameObjectItem::end()
{
    m_timer->stop();
    m_timer->deleteLater();
}

void GameObjectItem::init()
{
    setFlags(ItemIsMovable|ItemClipsToShape|ItemIsSelectable);
    setCacheMode(DeviceCoordinateCache);
    registerId(this);
    emit registerItem(this,this->getId());

}

bool GameObjectItem::getScriptBindState() const
{
    return m_scriptBindState;
}

void GameObjectItem::setScriptBindState(bool newScriptBindState)
{
    m_scriptBindState = newScriptBindState;
}

void GameObjectItem::posChanged()
{

    if(m_posXFlag)
    {
        m_posXFlag=false;
        this->setPos(m_linkObj->getPosX(),this->pos().y());
    }
    if(m_posYFlag)
    {
        m_posYFlag=false;
        this->setPos(this->pos().x(),m_linkObj->getPosY());
    }

}

GameObjectItem::PixType GameObjectItem::getPixType() const
{
    return m_pixType;
}

int GameObjectItem::getInterval() const
{
    return m_interval;
}

void GameObjectItem::setInterval(int newInterval)
{
    if (m_interval == newInterval)
    return;
    m_interval = newInterval;
    emit intervalChanged();

    if(m_timer==nullptr)
    return ;
    m_timer->setInterval(newInterval);

}

unsigned int GameObjectItem::getId() const
{
    return m_id;
}

void GameObjectItem::setId(unsigned int newId)
{
    if (m_id == newId)
    return;
    m_id = newId;
    emit idChanged();
}

bool GameObjectItem::state() const
{
    return m_state;
}

void GameObjectItem::setState(bool newState)
{
    if (m_state == newState)
    return;
    m_state = newState;
    emit stateChanged(m_state);
}

GameObjectItem::PixLayer GameObjectItem::pixLayer() const
{
    return m_pixLayer;
}

void GameObjectItem::setPixLayer(PixLayer newPixLayer)
{
    if (m_pixLayer == newPixLayer)
    return;
    m_pixLayer = newPixLayer;
    emit pixLayerChanged();
}

void GameObjectItem::setItemState(int itemId, bool newState)
{
    qDebug()<<m_id<<"nowState:"<<m_state<<(m_linkObj!=nullptr) <<"get signal:   id--newState"<<itemId<<" "<<newState;
    if(m_linkObj!=nullptr)
    {
      if(m_id==itemId)
      {
            setState(newState);
      }
    }
}
