#include "cardmanager.h"
//CardManager* g_cardManager=CardManager::getInstance();
CardManager* CardManager::m_instance=nullptr;
CardManager::CardManager(QObject *parent)
{
    m_card=nullptr;
}

CardManager *CardManager::getInstance()
{
    if(!m_instance)
    {
        m_instance=new CardManager;
    }
    return m_instance;
}

void CardManager::getNewCard()
{

    m_card=new Card;
    m_card->cardName=QString::number(m_card->cardId)+"ABCD";
    m_card->cardIntroduction="Hahahahaha"+QString::number(m_card->cardId);
    m_cardDictionaryByID.insert(m_card->cardId,QVariant::fromValue((void*)m_card));
    m_cardDictionaryByName.insert(m_card->cardName,QVariant::fromValue((void*)m_card));

    emit cardChoiced(m_card);
}

void CardManager::initManager()
{
    getNewCard();
}

void CardManager::addObject(QVariant var)
{
    if(var.canConvert<Card>())
    {
        Card* tmpCard=(Card*)var.value<void*>();
        m_cardDictionaryByID.insert(tmpCard->cardId,QVariant::fromValue((void*)tmpCard));
        m_cardDictionaryByName.insert(tmpCard->cardName,QVariant::fromValue((void*)tmpCard));
    }
}

QVariant CardManager::findByID(int id)
{
    auto it = m_cardDictionaryByID.find(id);
    if(it!=m_cardDictionaryByID.end())
    {
        return it.value();
    }
    else
    {
        return QVariant::fromValue(nullptr);
    }
}

QVariant CardManager::findByName(QString name)
{
    auto it = m_cardDictionaryByName.find(name);
    if(it!=m_cardDictionaryByName.end())
    {
        return it.value();
    }
    else
    {
        return QVariant::fromValue(nullptr);
    }
}
