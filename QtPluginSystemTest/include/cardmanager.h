#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include <QObject>
#include "Card.h"
#include "manager.h"
#include <QMap>

class CardManager :public Manager
{
    Q_OBJECT
public:
    //这里没给它父Object
    static CardManager* getInstance();
    void getNewCard();
    void initManager() override;
    void addObject(QVariant var)override;
    QVariant findByID(int id)override;
    QVariant findByName(QString name)override;
signals:
    void cardChoiced( Card* );
private:
    static CardManager* m_instance;
    explicit CardManager(QObject *parent = nullptr);
    Card* m_card;
    QMap<int,QVariant>m_cardDictionaryByID;
    QMap<QString,QVariant>m_cardDictionaryByName;
};

#endif // CARDMANAGER_H
