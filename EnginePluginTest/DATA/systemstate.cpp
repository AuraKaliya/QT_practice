#include "systemstate.h"
#include "qthread.h"

SystemState::SystemState(QState *parent)
    : QState{parent}
{
    m_waitWakeState=new QState(this);
    m_startingState=new QState(this);
    m_workingState=new QState(this);
    m_closeState=new QState(this);

}

void SystemState::connectToSystem(SystemObject *sys)
{
    m_connectSystem=sys;

    m_waitWakeState->assignProperty(sys,"state",SystemObject::WaitWake);
    m_startingState->assignProperty(sys,"state",SystemObject::Starting);
    m_workingState->assignProperty(sys,"state",SystemObject::Working);
    m_closeState->assignProperty(sys,"state",SystemObject::Close);

    connect(m_startingState,SIGNAL(entered()),this,SLOT(stateSwitch()),Qt::ConnectionType(Qt::AutoConnection | Qt::UniqueConnection));
    connect(m_workingState,SIGNAL(entered()),this,SLOT(stateSwitch()),Qt::ConnectionType(Qt::AutoConnection | Qt::UniqueConnection));
    connect(m_closeState,SIGNAL(entered()),this,SLOT(stateSwitch()),Qt::ConnectionType(Qt::AutoConnection | Qt::UniqueConnection));

    this->setInitialState(m_waitWakeState);

}









void SystemState::stateSwitch(const SystemObject::States &state)
{
    //主动进行状态转换

    qDebug()<<"SystemState::stateSwitch";
    //检查--  对指针的访问需要检查其有效性
    assert((m_connectSystem!=nullptr)&&(m_waitWakeState!=nullptr)&&
           (m_startingState!=nullptr)&&(m_workingState!=nullptr)&&
           (m_closeState!=nullptr));


    //处理需要转换的状态

    m_connectSystem->setState(state);

    stateSwitch();

}

void SystemState::connectNextBySignal(const QObject *sender, const char *signal)
{
    /* 已弃用 */
    /*
        为了拓展性，选择通过单层跳转的方式进行状态的转换，方便后续添加errorState及其处理方案
    */

        m_waitWakeState->addTransition(sender,signal,m_startingState);
        m_startingState->addTransition(sender,signal,m_workingState);
        m_workingState->addTransition(sender,signal,m_closeState);


        connect(m_waitWakeState,SIGNAL(finished()),this,SLOT(stateSwitch()),Qt::ConnectionType(Qt::AutoConnection | Qt::UniqueConnection));
        connect(m_startingState,SIGNAL(finished()),this,SLOT(stateSwitch()),Qt::ConnectionType(Qt::AutoConnection | Qt::UniqueConnection));
        connect(m_workingState,SIGNAL(finished()),this,SLOT(stateSwitch()),Qt::ConnectionType(Qt::AutoConnection | Qt::UniqueConnection));
}

void SystemState::connectToStartingBySignal(const QObject *sender, const char *signal)
{
    m_waitWakeState->addTransition(sender,signal,m_startingState);
    //connect(m_waitWakeState,SIGNAL(exited()),this,SLOT(stateSwitch()),Qt::ConnectionType(Qt::AutoConnection | Qt::UniqueConnection));
    //connect(m_startingState,SIGNAL(entered()),this,SLOT(stateSwitch()),Qt::ConnectionType(Qt::AutoConnection | Qt::UniqueConnection));

#if 0
    qDebug()<<"--------------------------------------";
    qDebug()<<"SystemState::connectToStartingBySignal";
    qDebug()<<"now m_waitWakeState Translation"<<m_waitWakeState->transitions();
    qDebug()<<"--------------------------------------";
#endif

}

void SystemState::connectToWorkingBySignal(const QObject *sender, const char *signal)
{
    m_startingState->addTransition(sender,signal,m_workingState);
   // connect(m_startingState,SIGNAL(exited()),this,SLOT(stateSwitch()),Qt::ConnectionType(Qt::AutoConnection | Qt::UniqueConnection));
   //connect(m_workingState,SIGNAL(entered()),this,SLOT(stateSwitch()),Qt::ConnectionType(Qt::AutoConnection | Qt::UniqueConnection));
}

void SystemState::connectToCloseBySignal(const QObject *sender, const char *signal)
{
    m_workingState->addTransition(sender,signal,m_closeState);
    //connect(m_workingState,SIGNAL(exited()),this,SLOT(stateSwitch()),Qt::ConnectionType(Qt::AutoConnection | Qt::UniqueConnection));
    //connect(m_closeState,SIGNAL(entered()),this,SLOT(stateSwitch()),Qt::ConnectionType(Qt::AutoConnection | Qt::UniqueConnection));
}

void SystemState::stateSwitch()
{
    emit nowStateChanged(m_connectSystem->getState());
    emit systemStateChanged(m_connectSystem);

#if 0
    qDebug()<<this<<" : StateSwitch  to "<<m_connectSystem->getState()<<" connected by "<<m_connectSystem;
#endif

}
