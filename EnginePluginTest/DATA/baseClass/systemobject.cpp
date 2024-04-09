#include "systemobject.h"
#include <QDebug>

SystemObject::SystemObject(QObject *parent)
    : QObject{parent},m_state(States::WaitWake)
{

    connect(this,&SystemObject::stateChanged,this,[&](){
        qDebug()<<this<<":StateChanged to  :"<<m_state;
        switch (m_state) {
        case Starting:
            systemInit();
            break;
        case Close:
            systemQuit();
            break;
        default:

            break;
        }
    });
}

SystemObject::States SystemObject::getState() const
{
    return  m_state;
}

void SystemObject::setState(const States &state)
{
    m_state=state;
    emit stateChanged(state);

#if 0
    qDebug()<<this<<":StateChanged to  :"<<state;
#endif

}
