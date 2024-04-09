#ifndef MOTAMONSTER_H
#define MOTAMONSTER_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "../baseClass/gameobject.h"
#include "../baseClass/componentobject.h"
#include "../model/modelshowcharacter.h"
#include "../model/modelbattlebase.h"

/*
    怪物GO
    1. ---拥有showCharacter模块    有动画显示
    2. --加载战斗模块  加载脚本自动--可进行自主移动
    3.碰撞会发生碰撞信号--统一处理事件

*/
class MotaMonster : public GameObject
{
    Q_OBJECT
public:
    explicit MotaMonster(QObject *parent = nullptr);
    void init(const QJsonObject * data)override;
    void tick()override;
    void solutePacketData(InsPacketData*data)override;


    QString getStateIndexList();
    QVector<QString> getStateStrList();

    QString getStateListStr();
    void changeState(QString newState);
    static void changeState(GameObject *me, QVariant v);


    int linkMapId() const;

    QJsonObject getItemData()override;

    unsigned int getATK();
    unsigned int getDEF();
    unsigned int getHP();
    bool getBattleState();


private:
    ModelShowCharacter * m_showCharacter;
    ModelBattleBase * m_battleBase;
    int m_linkMapId=0;

signals:
    void stateChanged(QString);
    void linkMap(GameObject* );
};
REGISTER_OBJECT(MotaMonster,GameObject)
#endif // MOTAMONSTER_H
