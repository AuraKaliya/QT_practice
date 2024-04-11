#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#pragma once

#include <QObject>
#include <DATA/baseClass/componentobject.h>
#include <QJsonObject>
#include <QJsonArray>
#include <DATA/instructioncontext.h>

#include <TOOL/template/Registor.hpp>
#include <TOOL/template/Factory.hpp>
/*
    游戏抽象对象类，是用于服务所有游戏对象的基类，引擎管理游戏对象主要是对这个的操作。

    游戏对象的共性：
    1.ID 全局唯一，在对象创建初被赋值。
    2.Name 对象实例的具体名字，也可以理解为昵称。 这里只提供途径，具体的可在子类中自定义相关。
      ClassName 对象所属具体类型的名字，用于实现预定义反射。
    3.Type 用于描述该对象实例属于引擎管理的对象中的何种大类型，这部分与引擎的扩展性关联，但为了方便开发和管理，需要进行界定。
    4.Model 加载的模块，引擎对GO的管理采用模块化加载，分模块Tick的策略进行。
    5.ObjectState 描述GO的生命周期，true表示存在，于实例建立时设置；false表示消亡，于破坏等事件发生后设置。
    6.nowState 描述GO当前状态，对于Character类型的Item用于切换显示动画。
        objectStateList 拥有的状态集，用于服务于nowState查询
    7.pixIdList 描述在形成Item时需要装载的图集资源。

*/
class GameObject;
using SoluteFunc=void (*)(GameObject*,QVariant);
class GameObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(unsigned int id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString className READ getClassName WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(double posX READ getPosX WRITE setPosX NOTIFY posXChanged)
    Q_PROPERTY(double posY READ getPosY WRITE setPosY NOTIFY posYChanged)
    Q_PROPERTY(int width READ getWidth WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ getHeight WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(bool visible READ getVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QString pixIdList READ getPixIdList WRITE setPixIdList NOTIFY pixIdListChanged)
    Q_PROPERTY(QString objectStateList READ getObjectStateList WRITE setObjectStateList NOTIFY objectStateListChanged)
    Q_PROPERTY(QString nowState READ getNowState WRITE setNowState NOTIFY nowStateChanged)
    Q_PROPERTY(int objectState READ getObjectState WRITE setObjectState NOTIFY objectStateChanged)
    Q_PROPERTY(QString script READ getScript WRITE setScript NOTIFY scriptChanged)

    Q_PROPERTY(bool posInit READ getPosInit WRITE setPosInit NOTIFY posInitChanged)
    Q_PROPERTY(bool superEdit READ getSuperEdit WRITE setSuperEdit NOTIFY superEditChanged)
    Q_PROPERTY(bool animationState READ animationState WRITE setAnimationState NOTIFY animationStateChanged)
    Q_PROPERTY(int pixId READ getPixId WRITE setPixId NOTIFY pixIdChanged)
    Q_PROPERTY(int itemId READ itemId WRITE setItemId NOTIFY itemIdChanged)
    Q_PROPERTY(bool loadProperty READ getLoadProperty WRITE setgetLoadProperty NOTIFY loadPropertyChanged)
    Q_PROPERTY(bool drawState READ drawState WRITE setDrawState NOTIFY drawStateChanged)
    Q_PROPERTY(Type type READ getType WRITE setType NOTIFY typeChanged)

    Q_PROPERTY(bool pixSourceFlag READ pixSourceFlag WRITE setPixSourceFlag NOTIFY pixSourceFlagChanged)

    Q_PROPERTY(QJsonObject data READ getData WRITE setData NOTIFY dataChanged)

public:
    enum Type
    {
        NonPlayerCharacter,
        PlayerCharacter,
        Environment,
        Event
    };

protected:
    unsigned int m_id;
    QString m_name;
    int m_objectState;
    Type m_type;
    QString m_className;
    static QMap<QString,SoluteFunc> m_soluteStratagies;
    static bool m_registFlag;

    QVector<ComponentObject*> m_myComponents;
    QMap<QString,ComponentObject*> m_componentDictionary;

    GameObject* m_linkGameObject=nullptr;

public:
    explicit GameObject(QObject *parent = nullptr);

    ComponentObject* getComponent(QString name);

    void operator <<(GameObject& obj);


    unsigned int getId() const;
    void setId(unsigned int newId);

    QString getName() const;
    void setName(const QString &newName);

    int getObjectState() const;
    void setObjectState(int newObjectState);

    Type getType() const;
    void setType(Type newType);

    virtual void init(const QJsonObject * data);
    virtual void tick();
    virtual QString getDataPacket();
    virtual void solutePacketData(InsPacketData*);
    virtual QJsonObject getItemData();

    QString getClassName() const;
    void setClassName(const QString &newClassName);

    bool getLoadProperty() const;
    void setgetLoadProperty(bool newLoadProperty);

    int getPixId() const;
    void setPixId(int newPixId);

    QJsonObject getData() const;
    void setData(const QJsonObject &newData);

    virtual void updateData();
    QVector<ComponentObject *> getMyComponents() const;
    void setMyComponents(const QVector<ComponentObject *> &newMyComponents);
    static  QMap<QString,SoluteFunc>* getSoluteStratagies();

    double getPosX() const;
    void setPosX(double newPosX);

    double getPosY() const;
    void setPosY(double newPosY);

    int getWidth() const;
    void setWidth(int newWidth);

    int getHeight() const;
    void setHeight(int newHeight);

    bool getVisible() const;
    void setVisible(bool newVisible);

    bool getSuperEdit() const;
    void setSuperEdit(bool newSuperEdit);

    QString getPixIdList() const;
    void setPixIdList(const QString &newPixIdList);

    QString getObjectStateList() const;
    void setObjectStateList(const QString &newObjectStateList);

    QString getNowState() const;
    void setNowState(const QString &newNowState);

    bool getPosInit() const;
    void setPosInit(bool newPosInit);

    QString getScript() const;
    void setScript(const QString &newScript);

    bool animationState() const;
    void setAnimationState(bool newAnimationState);

    bool drawState() const;
    void setDrawState(bool newDrawState);

    int itemId() const;
    void setItemId(int newItemId);

    bool pixSourceFlag() const;
    void setPixSourceFlag(bool newPixSourceFlag);

signals:
    void idChanged();
    void nameChanged();
    void objectStateChanged();
    void typeChanged();
    void classNameChanged();
    void loadPropertyChanged();
    void pixIdChanged();
    void dataChanged();

    void posXChanged();

    void posYChanged();

    void widthChanged();

    void heightChanged();

    void visibleChanged();

    void superEditChanged();

    void pixIdListChanged();

    void objectStateListChanged();

    void nowStateChanged();

    void posInitChanged();

    void scriptChanged();

    void animationStateChanged();

    void drawStateChanged(bool);

    void itemDrawStateChanged(int,bool);

    void initialized();

    void itemIdChanged();

    void pixSourceFlagChanged();

private:

    bool m_loadProperty;
    int m_pixId;
    QJsonObject m_data;
    double m_posX;
    double m_posY;
    int m_width;
    int m_height;
    bool m_visible;
    bool m_superEdit;
    QString m_pixIdList;
    QString m_objectStateList;
    QString m_nowState;
    bool m_posInit;
    QString m_script;
    bool m_animationState;
    bool m_drawState=true;
    int m_itemId;
    bool m_pixSourceFlag;
};

#endif // GAMEOBJECT_H
