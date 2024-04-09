#ifndef MODELBATTLEBASE_H
#define MODELBATTLEBASE_H

#include <QObject>
#include <QVector>
#include "../baseClass/componentobject.h"


/*
    ATK  --攻击
    DEF  --防御
    HP   --血量
    State  --存活状态
*/

class ModelBattleBase : public ComponentObject
{
    Q_OBJECT

    Q_PROPERTY(unsigned int ATK READ getATK WRITE setATK NOTIFY ATKChanged)
    Q_PROPERTY(unsigned int DEF READ getDEF WRITE setDEF NOTIFY DEFChanged)
    Q_PROPERTY(unsigned int HP READ getHP WRITE setHP NOTIFY HPChanged)
    Q_PROPERTY(bool state READ getState WRITE setState NOTIFY stateChanged)


public:
    explicit ModelBattleBase(QObject *parent = nullptr);
    void tick()override;

    unsigned int getATK() const;
    void setATK(unsigned int newATK);

    bool getState() const;
    void setState(bool newState);

    unsigned int getDEF() const;
    void setDEF(unsigned int newDEF);

    unsigned int getHP() const;
    void setHP(unsigned int newHP);

signals:

    void ATKChanged();
    void stateChanged();

    void DEFChanged();

    void HPChanged();

private:
    unsigned int m_ATK;
    bool m_state;
    unsigned int m_DEF;
    unsigned int m_HP;
};
REGISTER_OBJECT(ModelBattleBase,ComponentObject)
#endif // MODELBATTLEBASE_H
