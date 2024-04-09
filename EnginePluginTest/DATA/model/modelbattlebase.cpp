#include "modelbattlebase.h"

ModelBattleBase::ModelBattleBase(QObject *parent)
    : ComponentObject{parent}
{
     setObjectName("ModelBattleBase");
}

void ModelBattleBase::tick()
{
     qDebug()<<"ModelBattleBase::tick";
     qDebug()<<"ATK:"<<m_ATK;
     qDebug()<<"DEF:"<<m_DEF;
     qDebug()<<"HP:"<<m_HP;
     qDebug()<<"State:"<<m_state;

}

unsigned int ModelBattleBase::getATK() const
{
    return m_ATK;
}

void ModelBattleBase::setATK(unsigned int newATK)
{
    if (m_ATK == newATK)
        return;
    m_ATK = newATK;
    emit ATKChanged();
}

bool ModelBattleBase::getState() const
{
    return m_state;
}

void ModelBattleBase::setState(bool newState)
{
    if (m_state == newState)
        return;
    m_state = newState;
    emit stateChanged();
}

unsigned int ModelBattleBase::getDEF() const
{
    return m_DEF;
}

void ModelBattleBase::setDEF(unsigned int newDEF)
{
    if (m_DEF == newDEF)
        return;
    m_DEF = newDEF;
    emit DEFChanged();
}

unsigned int ModelBattleBase::getHP() const
{
    return m_HP;
}

void ModelBattleBase::setHP(unsigned int newHP)
{
    if (m_HP == newHP)
        return;
    m_HP = newHP;
    emit HPChanged();
}
