#include "gameobject.h"

#include <QMetaProperty>
QMap<QString,SoluteFunc> GameObject::m_soluteStratagies={};
bool GameObject::m_registFlag=false;
QVector<ComponentObject *> GameObject::getMyComponents() const
{
    return m_myComponents;
}

void GameObject::setMyComponents(const QVector<ComponentObject *> &newMyComponents)
{
    m_myComponents = newMyComponents;
}

QMap<QString, SoluteFunc>* GameObject::getSoluteStratagies()
{
    return &m_soluteStratagies;
}

GameObject::GameObject(QObject *parent)
    : QObject{parent},m_pixSourceFlag(false),m_id(0),m_loadProperty(false),m_animationState(false),m_script(""),m_objectStateList("Deal,Normal"),m_pixIdList(""),m_pixId(-1),m_posX(0.0),m_posY(0.0),m_width(50),m_height(50),m_visible(true),m_superEdit(false)
{

}

ComponentObject *GameObject::getComponent(QString name)
{
    ComponentObject* res=nullptr;
    auto it=m_componentDictionary.find(name);
    if(it!=m_componentDictionary.end())
    {
        res=it.value();
    }
    return res;
}

void GameObject::operator <<(GameObject &obj)
{

    //先当前GO的property进行赋值
    setId(obj.getId());
    setName(obj.getName());
    setClassName(obj.getClassName());
    setPixId(obj.getPixId());
    setObjectState(obj.getObjectState());
    setgetLoadProperty(obj.getLoadProperty());
    setType(obj.getType());
    setData(obj.getData());
    setPosX(obj.getPosX());
    setPosY(obj.getPosY());
    setWidth(obj.getWidth());
    setHeight(obj.getHeight());
    setVisible(obj.getVisible());
    setPixIdList(obj.getPixIdList());
    setPosInit(obj.getPosInit());
    setScript(obj.getScript());
    setItemId(obj.itemId());
    setPixSourceFlag(obj.pixSourceFlag());

//    if(obj.m_linkGameObject!=nullptr)
//    {
//        m_linkGameObject=
//    }

    qDebug()<<"operator <<  GameObject:"<<getId();
//    for(auto it:obj.getMyComponents())
//    {
//        bool flag=true;
//        int i=0;
//        while(flag)
//        {
//            const QMetaObject * pNew=it->metaObject();
//            QMetaProperty newProperty=pNew->property(i);
//            //QMetaProperty oldProperty=pOld->property(i);
//            i++;
//            if(newProperty.isValid())
//            {
//                qDebug()<<"check0.5:"<<it<<newProperty.read(it);
//            }else
//            {
//                flag=false;
//            }
//        }

//    }


    for(auto it:m_myComponents)
    {
        delete it;
        it=nullptr;
    }
    m_myComponents.clear();

    for(auto it:obj.getMyComponents())
    {
        ComponentObject * componet=Factory<ComponentObject>::GetInstance()->CreateObject(it->objectName()) ;
        const QMetaObject * pNew=componet->metaObject();
        //const QMetaObject * pOld=it->metaObject();

        bool flag=true;
        int i=0;
        while(flag)
        {
            QMetaProperty newProperty=pNew->property(i);
            //QMetaProperty oldProperty=pOld->property(i);
            i++;
            if(newProperty.isValid())
            {
                qDebug()<<"check0:"<<it<<newProperty.read(it);
                newProperty.write(componet,newProperty.read(it));
            }else
            {
                flag=false;
            }
        }
        m_myComponents.append(componet);
    }

    return;
}

unsigned int GameObject::getId() const
{
    return m_id;
}

void GameObject::setId(unsigned int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

QString GameObject::getName() const
{
    return m_name;
}

void GameObject::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

int GameObject::getObjectState() const
{
    return m_objectState;
}

void GameObject::setObjectState(int newObjectState)
{
    if (m_objectState == newObjectState)
        return;
    m_objectState = newObjectState;
    emit objectStateChanged();
}

GameObject::Type GameObject::getType() const
{
    return m_type;
}

void GameObject::setType(Type newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

void GameObject::init(const QJsonObject *data)
{
    emit initialized();
}

void GameObject::tick()
{

}

QString GameObject::getDataPacket()
{
    return QString();
}

void GameObject::solutePacketData(InsPacketData *data)
{
    auto it=m_soluteStratagies.find(data->insName);
    if(it!=m_soluteStratagies.end())
    {
        //指令处理--数据包处理
        it.value()(this,data->value);
        //后续处理在manager中进行
    }
}

QJsonObject GameObject::getItemData()
{
    QJsonObject obj;
    obj.insert("Type",getType());
    obj.insert("Id",(int)getId());
    obj.insert("ClassName",getClassName());
    obj.insert("Name",getName());

    QJsonArray posArray;
    posArray.append(getPosX());
    posArray.append(getPosY());
    obj.insert("Pos",posArray);

    QJsonArray sizeArray;
    sizeArray.append(getWidth());
    sizeArray.append(getHeight());
    obj.insert("Size",sizeArray);

    obj.insert("PixIdList",getPixIdList());
    obj.insert("Script",getScript());
    return obj;
}


QString GameObject::getClassName() const
{
    return m_className;
}

void GameObject::setClassName(const QString &newClassName)
{
    if (m_className == newClassName)
        return;
    m_className = newClassName;
    emit classNameChanged();
}

bool GameObject::getLoadProperty() const
{
    return m_loadProperty;
}

void GameObject::setgetLoadProperty(bool newLoadProperty)
{
    if (m_loadProperty == newLoadProperty)
        return;
    m_loadProperty = newLoadProperty;
    emit loadPropertyChanged();
}

int GameObject::getPixId() const
{
    return m_pixId;
}

void GameObject::setPixId(int newPixId)
{
    if (m_pixId == newPixId)
        return;
    m_pixId = newPixId;
    emit pixIdChanged();
}

QJsonObject GameObject::getData() const
{
    return m_data;
}

void GameObject::setData(const QJsonObject &newData)
{
    if (m_data == newData)
        return;
    m_data = newData;
    emit dataChanged();
}

void GameObject::updateData()
{

}

double GameObject::getPosX() const
{
    return m_posX;
}

void GameObject::setPosX(double newPosX)
{
    if (qFuzzyCompare(m_posX, newPosX))
        return;
    m_posX = newPosX;
    emit posXChanged();
}

double GameObject::getPosY() const
{
    return m_posY;
}

void GameObject::setPosY(double newPosY)
{
    if (qFuzzyCompare(m_posY, newPosY))
        return;
    m_posY = newPosY;
    emit posYChanged();
}

int GameObject::getWidth() const
{
    return m_width;
}

void GameObject::setWidth(int newWidth)
{
    if (m_width == newWidth)
        return;
    m_width = newWidth;
    emit widthChanged();
}

int GameObject::getHeight() const
{
    return m_height;
}

void GameObject::setHeight(int newHeight)
{
    if (m_height == newHeight)
        return;
    m_height = newHeight;
    emit heightChanged();
}

bool GameObject::getVisible() const
{
    return m_visible;
}

void GameObject::setVisible(bool newVisible)
{
    if (m_visible == newVisible)
        return;
    m_visible = newVisible;
    emit visibleChanged();
}

bool GameObject::getSuperEdit() const
{
    return m_superEdit;
}

void GameObject::setSuperEdit(bool newSuperEdit)
{
    if (m_superEdit == newSuperEdit)
        return;
    m_superEdit = newSuperEdit;
    emit superEditChanged();
}

QString GameObject::getPixIdList() const
{
    return m_pixIdList;
}

void GameObject::setPixIdList(const QString &newPixIdList)
{
    if(newPixIdList=="")
        return;

    if (m_pixIdList == newPixIdList)
        return;
    m_pixIdList = newPixIdList;

    if(m_pixIdList.split(",")[0].toInt()!=0)
    {
        setPixId(m_pixIdList.split(",")[0].toInt());
    }

    emit pixIdListChanged();
}

QString GameObject::getObjectStateList() const
{
    return m_objectStateList;
}

void GameObject::setObjectStateList(const QString &newObjectStateList)
{
    if (m_objectStateList == newObjectStateList)
        return;
    m_objectStateList = newObjectStateList;
    emit objectStateListChanged();
}

QString GameObject::getNowState() const
{
    return m_nowState;
}

void GameObject::setNowState(const QString &newNowState)
{
    if (m_nowState == newNowState)
        return;
    m_nowState = newNowState;
    emit nowStateChanged();
}

bool GameObject::getPosInit() const
{
    return m_posInit;
}

void GameObject::setPosInit(bool newPosInit)
{
    if (m_posInit == newPosInit)
        return;
    m_posInit = newPosInit;
    emit posInitChanged();
}

QString GameObject::getScript() const
{
    return m_script;
}

void GameObject::setScript(const QString &newScript)
{
    if (m_script == newScript)
        return;
    m_script = newScript;
    emit scriptChanged();
}

bool GameObject::animationState() const
{
    return m_animationState;
}

void GameObject::setAnimationState(bool newAnimationState)
{
    if (m_animationState == newAnimationState)
        return;
    m_animationState = newAnimationState;
    emit animationStateChanged();
}

bool GameObject::drawState() const
{
    return m_drawState;
}

void GameObject::setDrawState(bool newDrawState)
{
    if (m_drawState == newDrawState)
        return;
    m_drawState = newDrawState;
    emit drawStateChanged(m_drawState);
}

int GameObject::itemId() const
{
    return m_itemId;
}

void GameObject::setItemId(int newItemId)
{
    if (m_itemId == newItemId)
        return;
    m_itemId = newItemId;
    emit itemIdChanged();
}

bool GameObject::pixSourceFlag() const
{
    return m_pixSourceFlag;
}

void GameObject::setPixSourceFlag(bool newPixSourceFlag)
{
    if (m_pixSourceFlag == newPixSourceFlag)
        return;
    m_pixSourceFlag = newPixSourceFlag;
    emit pixSourceFlagChanged();
}
