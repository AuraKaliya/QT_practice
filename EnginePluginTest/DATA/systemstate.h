#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include <QObject>
#include <QState>
#include "./baseClass/systemobject.h"



/*
描述系统状态的类，获取系统属性，做一个集合，方便与状态机进行交互
*/


class SystemState : public QState
{
    Q_OBJECT

private:
    SystemObject* m_connectSystem=nullptr;
    QState* m_waitWakeState=nullptr;
    QState* m_startingState=nullptr;
    QState* m_workingState=nullptr;
    QState* m_closeState=nullptr;

public:
    explicit SystemState(QState *parent = nullptr);
    void connectToSystem(SystemObject* sys);
    void stateSwitch(const SystemObject::States & state);
    void connectNextBySignal(const QObject *sender, const char *signal);
    void connectToStartingBySignal(const QObject *sender, const char *signal);
    void connectToWorkingBySignal(const QObject *sender, const char *signal);
    void connectToCloseBySignal(const QObject *sender, const char *signal);

private:

signals:

    void nowStateChanged(const SystemObject::States&);
    void systemStateChanged(SystemObject*);
private slots:
    void stateSwitch();

};

#endif // SYSTEMSTATE_H
