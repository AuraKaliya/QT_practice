#include "modelshowcharacter.h"

ModelShowCharacter::ModelShowCharacter(QObject *parent)
    : ComponentObject{parent}
{
     setObjectName("ModelShowCharacter");
}

void ModelShowCharacter::tick()
{
     qDebug()<<"ModelShowCharacter::tick";
     qDebug()<<"stateList"<<m_stateList;
     qDebug()<<"pixList"<<m_pixList;
     qDebug()<<"nowState"<<m_nowState;
}

QString ModelShowCharacter::getStateList()
{
    return m_stateList;
}

void ModelShowCharacter::setStateList(const QString &newStateList)
{
    if (m_stateList == newStateList)
        return;
    m_stateList = newStateList;
    emit stateListChanged();
}

bool ModelShowCharacter::getPixType()
{
    return m_pixType;
}

void ModelShowCharacter::setPixType(bool newPixType)
{
    if (m_pixType == newPixType)
        return;
    m_pixType = newPixType;
    emit pixTypeChanged();
}

QString ModelShowCharacter::getPixList()
{
    return m_pixList;
}

void ModelShowCharacter::setPixList(const QString &newPixList)
{
    if (m_pixList == newPixList)
        return;
    m_pixList = newPixList;
    emit pixListChanged();
}

QString ModelShowCharacter::getPixIndexList()
{
    qDebug()<<"ModelShowCharacter::getPixIndexList()```";
    //qDebug()<<"check"<<m_pixIndexList;
    return m_pixIndexList;
}

void ModelShowCharacter::setPixIndexList(const QString &newPixIndexList)
{
    if (m_pixIndexList == newPixIndexList)
        return;
    m_pixIndexList = newPixIndexList;
    emit pixIndexListChanged();
}

QString ModelShowCharacter::getNowState()
{
    return m_nowState;
}

bool ModelShowCharacter::setNowState(const QString &newNowState)
{
    if (m_nowState == newNowState)
        return false;
    m_nowState = newNowState;
    emit nowStateChanged();
    return true;
}
