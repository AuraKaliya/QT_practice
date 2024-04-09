#ifndef MOTANPC_H
#define MOTANPC_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "../baseClass/gameobject.h"
#include "../baseClass/componentobject.h"
#include "../model/modelshowcharacter.h"

class MotaNPC : public GameObject
{
    Q_OBJECT
public:
    explicit MotaNPC(QObject *parent = nullptr);
    void init(const QJsonObject * data)override;
    void tick()override;
    void solutePacketData(InsPacketData*data)override;

    QString getStateIndexList();
    QVector<QString> getStateStrList();

    QString getStateListStr();
    void changeState(QString newState);
    static void changeState(GameObject *me, QVariant v);


    int linkMapId() const;

    QJsonObject getItemData()override;




private:
    ModelShowCharacter * m_showCharacter;
    int m_linkMapId=0;

signals:
    void stateChanged(QString);
    void linkMap(GameObject* );

};
REGISTER_OBJECT(MotaNPC,GameObject)
#endif // MOTANPC_H
