#ifndef GAMEDEMO_H
#define GAMEDEMO_H

#include <QObject>
#include <QMap>
#include <QPoint>
#include "gameobject.h"

class GameDemo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool envState READ envState WRITE setEnvState NOTIFY envStateChanged)
    Q_PROPERTY(bool playerState READ playerState WRITE setPlayerState NOTIFY playerStateChanged)
    Q_PROPERTY(bool npcState READ npcState WRITE setNpcState NOTIFY npcStateChanged)
    Q_PROPERTY(bool eventState READ eventState WRITE setEventState NOTIFY eventStateChanged)
    Q_PROPERTY(bool initState READ initState WRITE setInitState NOTIFY initStateChanged)
public:
    explicit GameDemo(QObject *parent = nullptr);
    virtual void init(const QJsonObject* obj)=0;
    virtual QVector<GameObject*> getElement();
    virtual GameObject* getElement(QString name);
    virtual GameObject* getElement(int idx);
    virtual void registerElement(int idx, GameObject*obj);
    virtual void registToManager()=0;

    virtual QPoint posFromMap(QPoint point);

    //virtual void insRecv(InstructionContext* insContext)=0;
    //virtual void dataSend()=0;
    virtual int waitForIntSignal(QObject* obj, const char *signal,const unsigned int ms=3000);
    virtual QJsonObject getDemoSource();



    bool envState() const;
    void setEnvState(bool newEnvState);

    bool playerState() const;
    void setPlayerState(bool newPlayerState);

    bool npcState() const;
    void setNpcState(bool newNpcState);

    bool eventState() const;
    void setEventState(bool newEventState);

    bool initState() const;
    void setInitState(bool newInitState);


protected:
    QMap<QString,QPair<QString,GameObject*> > m_element;
    QMap<QString,QVector<GameObject*> > m_elementList;
    QVector<QString> m_elementSort;
    QMap<int,GameObject*> m_elementDictionary;

signals:
    void objectCreated(GameObject*);
    void objectCreatedFromFile(GameObject*,unsigned int id);
    void objectRegistToManager(GameObject*,QString);
    void demoFuncRegistToManager(SoluteFunc,QString);

    void envStateChanged();

    void playerStateChanged();

    void npcStateChanged();

    void eventStateChanged();

    void initStateChanged();

private:
    int  m_result;
    QEventLoop m_loop;

    bool m_envState=false;

    bool m_playerState=false;

    bool m_npcState=false;

    bool m_eventState=false;

    bool m_initState=false;

private slots:
    void solveIntSignal(int number);
};


//#define REGISTERTODEMO()

#endif // GAMEDEMO_H
