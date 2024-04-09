#ifndef MOTAHERO_H
#define MOTAHERO_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "../baseClass/gameobject.h"
#include "../baseClass/componentobject.h"
#include "../model/modelshowcharacter.h"
#include "../model/modelbattlebase.h"
#include "../model/modelmotabag.h"
//#include "motamap.h"

#include <TOOL/template/Registor.hpp>
class MotaHero : public GameObject
{
    Q_OBJECT
public:
    explicit MotaHero(QObject *parent = nullptr);
    void init(const QJsonObject * data)override;
    void tick()override;
    void solutePacketData(InsPacketData*data)override;
    QJsonObject getItemData()override;

    QString getStateIndexList();
    QVector<QString> getStateStrList();

    QString getStateListStr();
    void changeState(QString);
    static void changeState(GameObject *me, QVariant v);


    int linkMapId() const;

    unsigned int getATK();
    unsigned int getDEF();
    unsigned int getHP();
    bool getBattleState();

    void operator <<(MotaHero& obj);

    ModelBattleBase *battleBase() const;

    ModelMotaBag *motaBag() const;



private:
    ModelShowCharacter * m_showCharacter;
    ModelBattleBase *m_battleBase;

    ModelMotaBag * m_motaBag;




    int m_linkMapId=0;
    //MotaMap* m_linkMap=nullptr;
signals:
    void stateChanged(QString);
    void linkMap();
};
REGISTER_OBJECT(MotaHero,GameObject)
#endif // MOTAHERO_H
