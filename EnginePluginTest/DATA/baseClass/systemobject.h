#ifndef SYSTEMOBJECT_H
#define SYSTEMOBJECT_H

#include <QObject>
#include <QString>

/*
系统基类---
    系统共性： 状态---属性
    管理者  管理内部属性的组织和共给---object
    注册器  对内部属性进行身份注册---object
    支持者  提供扩展（将自己交出去）---object

*/



class SystemObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(States state READ getState WRITE setState NOTIFY stateChanged)
public:
    enum States{
        WaitWake,
        Starting,
        Working,
        Close
    };
protected:
    States m_state;

    QObject* m_manager;
    QObject* m_register;
    QObject* m_provider;

public:
    explicit SystemObject(QObject *parent = nullptr);

    States getState()const;
    void setState(const States& state);

    virtual bool systemStart()=0;
    virtual bool systemInit()=0;
    virtual bool systemSolve()=0;
    virtual bool systemQuit()=0;


signals:
    void stateChanged(const States& state);

};

#endif // SYSTEMOBJECT_H
