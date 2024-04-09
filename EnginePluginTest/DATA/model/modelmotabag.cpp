#include "modelmotabag.h"

ModelMotaBag::ModelMotaBag(QObject *parent)
    : ComponentObject{parent}
{

}

void ModelMotaBag::tick()
{
    qDebug()<<" ModelMotaBag::tick ----";
    qDebug()<<" yellow :"<<m_yellowKey;
    qDebug()<<" blue :"<<m_blueKey;
    qDebug()<<" red :"<<m_redKey;
    qDebug()<<" ModelMotaBag::tick ----end";
}

int ModelMotaBag::yellowKey() const
{
    return m_yellowKey;
}

void ModelMotaBag::setYellowKey(int newYellowKey)
{
    if (m_yellowKey == newYellowKey)
        return;
    m_yellowKey = newYellowKey;
    emit yellowKeyChanged();
}

int ModelMotaBag::blueKey() const
{
    return m_blueKey;
}

void ModelMotaBag::setBlueKey(int newBlueKey)
{
    if (m_blueKey == newBlueKey)
        return;
    m_blueKey = newBlueKey;
    emit blueKeyChanged();
}

int ModelMotaBag::redKey() const
{
    return m_redKey;
}

void ModelMotaBag::setRedKey(int newRedKey)
{
    if (m_redKey == newRedKey)
        return;
    m_redKey = newRedKey;
    emit redKeyChanged();
}
