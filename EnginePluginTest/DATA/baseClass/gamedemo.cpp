#include "gamedemo.h"

GameDemo::GameDemo(QObject *parent)
    : QObject{parent}
{

}

QVector<GameObject *> GameDemo::getElement()
{
    QVector<GameObject * >tmp;
    for(auto it:qAsConst(m_elementSort))
    {
        tmp.append(m_element.find(it).value().second);
    }

    for(auto it:qAsConst(m_elementList))
    {
        for(auto it2:it)
        {
            tmp.append(it2);
        }
    }
    return tmp;
}

GameObject *GameDemo::getElement(QString name)
{
    auto it=m_element.find(name);

    if(it!=m_element.end())
    {
        return it.value().second;
    }
    return nullptr;
}

GameObject *GameDemo::getElement(int idx)
{

    auto it=m_elementDictionary.find(idx);

    if(it!=m_elementDictionary.end())
    {
        return it.value();
    }
    return nullptr;



}

void GameDemo::registerElement(int idx, GameObject *obj)
{
    m_elementDictionary[idx]=obj;
}

QPoint GameDemo::posFromMap(QPoint point)
{
    return point;
}

int GameDemo::waitForIntSignal(QObject *obj, const char *signal, const unsigned int ms)
{
    m_result =0;
    connect(obj,signal,this,SLOT(solveIntSignal(int)));

    QTimer timer;
    timer.setSingleShot(true);

    connect(&timer,&QTimer::timeout,[this]{
        m_result=-1;
        qDebug()<<"ComponentObject::waitForSignal: TIMEOUT!";
        m_loop.quit();
    });
    timer.start(ms);

    m_loop.exec();
    timer.stop();

    return m_result;

}

QJsonObject GameDemo::getDemoSource()
{
    return QJsonObject();
}

void GameDemo::solveIntSignal(int number)
{
    if(m_loop.isRunning())
    {
        m_result=number;
        m_loop.quit();
    }
}

bool GameDemo::envState() const
{
    return m_envState;
}

void GameDemo::setEnvState(bool newEnvState)
{
    if (m_envState == newEnvState)
        return;
    m_envState = newEnvState;
    emit envStateChanged();
}

bool GameDemo::playerState() const
{
    return m_playerState;
}

void GameDemo::setPlayerState(bool newPlayerState)
{
    if (m_playerState == newPlayerState)
        return;
    m_playerState = newPlayerState;
    emit playerStateChanged();
}

bool GameDemo::npcState() const
{
    return m_npcState;
}

void GameDemo::setNpcState(bool newNpcState)
{
    if (m_npcState == newNpcState)
        return;
    m_npcState = newNpcState;
    emit npcStateChanged();
}

bool GameDemo::eventState() const
{
    return m_eventState;
}

void GameDemo::setEventState(bool newEventState)
{
    if (m_eventState == newEventState)
        return;
    m_eventState = newEventState;
    emit eventStateChanged();
}

bool GameDemo::initState() const
{
    return m_initState;
}

void GameDemo::setInitState(bool newInitState)
{
    if (m_initState == newInitState)
        return;
    m_initState = newInitState;
    emit initStateChanged();
}
