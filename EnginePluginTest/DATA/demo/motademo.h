#ifndef MOTADEMO_H
#define MOTADEMO_H

#include <QObject>
#include "../baseClass/gamedemo.h"
#include "../gameObject/motamap.h"
#include "../gameObject/motahero.h"
#include "../gameObject/motamonster.h"
#include "../gameObject/motanpc.h"

#include <TOOL/template/Factory.hpp>

/*
    实际的Demo应该放在TOOL层，因为在Demo中并不只存有相关数据，还有进行处理的方案，有与UI交互的部分。
*/

using TalkWithFunc=int(*)(MotaNPC*);

class MotaDemo : public GameDemo
{
    Q_OBJECT
public:
    enum ObjectType{
        NoType=0,
        Hero=1,
        Monster=2,
        NPC=4,
        Event=5
    };

    struct MotaData
    {
        unsigned int heroId;
        unsigned int mapId;
        unsigned int towers;
        QVector<int> layerLink;

    };

    enum OverlapType{
        Unknown=0,
        HeroMonster=1,
        HeroNPC=2
    };

    struct BattleInfo
    {
        GameObject* obj1;
        GameObject* obj2;
        int winnerId;
    };


    struct MotaObjectPos
    {
        int layer;
        int x;
        int y;
    };

private:
    MotaMap * m_motaMap;
    MotaHero* m_motaHero;
    QVector<MotaMonster*> m_motaMonsterList;
    QVector<MotaNPC*> m_motaNPCList;

    explicit MotaDemo(QObject *parent = nullptr);

    static MotaDemo* m_instance;

    static int heroBattleWithMonster(MotaMonster*monster);
    static int heroTalkWithNPC(MotaNPC*npc);


    QMap<int,MotaDemo::ObjectType> m_objectTypeDictionary;
    QMap<int,MotaMonster*> m_monsterDictionary;
    QMap<int,MotaNPC*> m_npcDictionary;
    QMap<int,QVector<MotaObjectPos> > m_objPosDictionary;
    static QMap<QString,TalkWithFunc> m_talkWithDictionary;

    struct BattleInfo m_battleInfo;


    static int s_nowItemId;

public:
    static MotaDemo* getInstance();
    void init(const QJsonObject* obj)override;
    void registToManager()override;
    int heroActive(int objectId);
    static void setNowItemId(int id);
    static void resetNowItemId();

    QPoint posFromMap(QPoint point)override;
    QPair<int,int> posFromMapMatrix(QPoint point);

    static void heroMoveToNextElement(GameObject* hero,QVariant v);
    static void monsterMoveToNextElement(GameObject* monster,QVariant v);
    static void heroMoveToElement(GameObject* hero,QVariant v);
    static void heroMoveToLayer(GameObject* hero,QVariant v);
    static void heroMoveToNextLayer(GameObject* hero,QVariant v);
    static void heroMoveToPreLayer(GameObject* hero,QVariant v);

    static int talkWithUpLader(MotaNPC* obj);
    static int talkWithDownLader(MotaNPC* obj);
    static int talkWithYelloDoor(MotaNPC* obj);
    static int talkWithBlueDoor(MotaNPC* obj);
    static int talkWithRedDoor(MotaNPC* obj);
    static int talkWithSprite(MotaNPC* obj);

    static int talkWithYellowKey(MotaNPC* obj);
    static int talkWithBlueKey(MotaNPC* obj);
    static int talkWithRedKey(MotaNPC* obj);

    static int talkWithSmallHPPotion(MotaNPC* obj);
    static int talkWithBigHPPotion(MotaNPC* obj);
    static int talkWithATKGem(MotaNPC* obj);
    static int talkWithDEFGem(MotaNPC* obj);

    void objectMoved(int id,int x,int y);
    int  objectOverLaped(int id1,int id2);

    void animationHeroMoved(int newX,int newY);
    void animationMonsterMoved(MotaMonster * monster,int newX,int newY);

    MotaHero *motaHero() const;
    MotaMap *motaMap() const;
    MotaMonster* motaMonster(int idx);
    MotaNPC* motaNPC(int idx);

    bool addHero(MotaHero*hero);
    bool addMap(MotaMap*);
    bool addMonster(MotaMonster* ,int posx,int posy);
    bool addNPC(MotaNPC*npc,int posx,int posy);

    QJsonObject getDemoSource() override;

    QVector<MotaObjectPos> getMotaObjectPos(int id);

    QMap<int, QVector<MotaDemo::MotaObjectPos> > objPosDictionary() const;

public slots:
    void solveObjectOverLap(int obj1Id, int obj2Id, int newX, int newY);

signals:
    void battleStart(MotaHero*hero,MotaMonster*monster);
    void battleEnd(MotaHero*hero,MotaMonster*monster,int winnerId);
    void overLapSolved(int);
    void layerChanged(int);
    void heroChanged(int,int);
    void eventSend(QString);
};



#endif // MOTADEMO_H
