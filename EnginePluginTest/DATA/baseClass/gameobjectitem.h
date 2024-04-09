#ifndef GAMEOBJECTITEM_H
#define GAMEOBJECTITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <DATA/baseClass/gameobject.h>
#include <QObject>
#include <DATA/baseClass/pixsource.h>

/*
 * 以json包的形式更新
    x,y
    orderLayer
    width,height
    single,Multiple
    internel,timer
    Qvector<pix>
*/


class GameObjectItem:public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(int nowLayer READ getNowLayer WRITE setNowLayer NOTIFY nowLayerChanged)
    Q_PROPERTY(int nowZValue READ getNowZValue WRITE setNowZValue NOTIFY nowZValueChanged)
    Q_PROPERTY(PixType pixType READ getPixType WRITE setPixType NOTIFY pixTypeChanged)
    Q_PROPERTY(PixLayer pixLayer READ pixLayer WRITE setPixLayer NOTIFY pixLayerChanged)
    Q_PROPERTY(int interval READ getInterval WRITE setInterval NOTIFY intervalChanged)
    Q_PROPERTY(bool state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(unsigned int id READ getId WRITE setId NOTIFY idChanged)

public:
    enum PixType{Single,Multiple};
    enum PixLayer{Background,Object,Special};

public:
    GameObjectItem(GameObject*obj=nullptr,QObject *parent=nullptr );
    GameObjectItem(GameObject*obj,QPixmap pix,QObject *parent=nullptr);
    QRectF  boundingRect() const override;    //QRect绘制时除了topleft 都会往内部偏移1像素点，而QRectF是用浮点数表示区域，不会出现这个问题
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) override;

    GameObject *getLinkObj() const;
    void setLinkObj(GameObject *newLinkObj);

    QPixmap getObjPix() const;
    void setObjPix(QPixmap newObjPix);



    static QVector<QString> getLayers();
    static bool addLayer(QString layerName);
    static bool delLayer(int i);
    static void swapLayer(int i,int j);
    static QString getLayerById(int i);
    static void updateDefaultLayerIdx();

    static unsigned int globalId;
    static void registerId(GameObjectItem*);
    int getNowZValue() const;
    void setNowZValue(int newNowZValue);

    void setSyncPos(bool flag);


    int getNowLayer() const;
    void setNowLayer(int newNowLayer);

    QVector<QPixmap> getPixList() const;
    void setPixList(const QVector<QPixmap> &newPixList);


    void setPixType(PixType type);
    void setPixScale(QRect rect);
    void start();
    void end();

    GameObjectItem::PixType getPixType() const;

    int getInterval() const;
    void setInterval(int newInterval);

    unsigned int getId() const;
    void setId(unsigned int newId);

    bool getScriptBindState() const;
    void setScriptBindState(bool newScriptBindState);

    bool state() const;
    void setState(bool newState);

    GameObjectItem::PixLayer pixLayer() const;
    void setPixLayer(PixLayer newPixLayer);

    void setItemState(int itemId,bool newState);

private:
    void posChanged();
signals:
    void nowLayerChanged();
    void nowZValueChanged();

    void pixTypeChanged();

    void intervalChanged();

    void idChanged();

    void registerItem(GameObjectItem*,unsigned int);
    void resetPixScale();
    void stateChanged(bool);

    void pixLayerChanged();

private:
    void init();

protected:
    QPixmap m_objPix;
    QRect m_pixRect;
    QMap<int,QPixmap*> m_pixDictionary{};
    QMap<int ,PixSource*> m_pixSourceDictionary{};
    GameObject* m_linkObj=nullptr;
private:
    QVector<QPixmap> m_pixList;
    PixType m_pixType;
    QTimer*m_timer=nullptr;

    int m_nowPixIdx=0;
    int m_interval=100;




    int m_nowLayer;
    int m_nowZValue;

    bool m_scriptBindState=false;

    static QVector<QString> s_layers;
    static int s_defaultLayerIdx;
    static int s_layersHeight;

    bool m_posXFlag=false;
    bool m_posYFlag=false;


    unsigned int m_id;
    bool m_state=true;
    PixLayer m_pixLayer;
};

#endif // GAMEOBJECTITEM_H
