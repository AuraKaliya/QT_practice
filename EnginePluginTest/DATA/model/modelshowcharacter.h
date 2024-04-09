#ifndef MODELSHOWCHARACTER_H
#define MODELSHOWCHARACTER_H

#include <QObject>

#include <QVector>
#include "../baseClass/componentobject.h"


/*
    StateList --表明角色的状态数
    PixList  --表明状态对应的pixId，用|区分状态。
    --另外俩暂时不用
    PixType   --表明0：单图加载，pixList   1：多图加载，pixIdxList
*/


class ModelShowCharacter : public ComponentObject
{
    Q_OBJECT

    Q_PROPERTY(QString stateList READ getStateList WRITE setStateList NOTIFY stateListChanged)
    Q_PROPERTY(QString pixList READ getPixList WRITE setPixList NOTIFY pixListChanged)
    Q_PROPERTY(QString nowState READ getNowState WRITE setNowState NOTIFY nowStateChanged)
    Q_PROPERTY(QString pixIndexList READ getPixIndexList WRITE setPixIndexList NOTIFY pixIndexListChanged)
    Q_PROPERTY(bool pixType READ getPixType WRITE setPixType NOTIFY pixTypeChanged)

public:
    explicit ModelShowCharacter(QObject *parent = nullptr);
    void tick()override;

    QString getStateList() ;
    void setStateList(const QString &newStateList);

    bool getPixType() ;
    void setPixType(bool newPixType);

    QString getPixList() ;
    void setPixList(const QString &newPixList);

    //QVector<QVector<QPixmap*>> getPixListFromThis();

    QString getPixIndexList() ;
    void setPixIndexList(const QString &newPixIndexList);

    QString getNowState() ;
    bool setNowState(const QString &newNowState);

signals:

    void stateListChanged();
    void pixTypeChanged();
    void pixListChanged();
    void pixIndexListChanged();
    void nowStateChanged();

private:

    QVector<QString> m_stateVector;
    QVector<QVector<int> > m_stateIndexVector;

    QString m_stateList;
    bool m_pixType;
    QString m_pixList;
    QString m_pixIndexList;
    QString m_nowState;
};

REGISTER_OBJECT(ModelShowCharacter,ComponentObject)
#endif // MODELSHOWCHARACTER_H
