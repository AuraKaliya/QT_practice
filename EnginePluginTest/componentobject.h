#ifndef COMPONENTOBJECT_H
#define COMPONENTOBJECT_H

#include <QObject>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <TOOL/template/Registor.hpp>

using IntSignalFunc=void(*)(int);
class GameObject;
class ComponentObject : public QObject
{
    Q_OBJECT

public:
    explicit ComponentObject(QObject *parent = nullptr);
    //virtual void initProperty(QJsonObject jsonObj);
    //virtual QJsonObject getProperty();
    virtual void tick();
    virtual void bindToGameObject(GameObject* go);

    virtual bool waitForSignal(QObject* obj,const char * signal,const unsigned int ms=3000);
    virtual int waitForIntSignal(QObject* obj, const char *signal,const unsigned int ms=3000);

signals:
private:
    int  m_result;
    QEventLoop m_loop;

private slots:
    void solveIntSignal(int number);

};

#endif // COMPONENTOBJECT_H
