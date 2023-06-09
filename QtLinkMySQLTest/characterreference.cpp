#include "characterreference.h"

CharacterReference::CharacterReference()
{

}

void CharacterReference::show()
{
    qDebug()<<"----------CharacterReference::---------------";
    qDebug()<<"ID:"<<m_instance->ID();
    qDebug()<<"Name:"<<m_instance->name();
    qDebug()<<"TitleName:"<<m_instance->titleName();
    qDebug()<<"---------CharacterReference::----------------";
}
CharacterReference* CharacterReference::m_instance=nullptr;
QString CharacterReference::m_name="";
QString CharacterReference::m_titleName="";
int CharacterReference::m_ID=0;
CharacterReference *CharacterReference::getInstance()
{
    if(m_instance==nullptr)
        m_instance=new CharacterReference();
    return m_instance;
}

int CharacterReference::ID()
{
    return m_ID;
}

void CharacterReference::setID(int newID)
{
    m_ID = newID;
}

void CharacterReference::setIDByQVariant(const QVariant &value)
{
    setID(value.toInt());
}

QString CharacterReference::name()
{
    return m_name;
}

void CharacterReference::setName(const QString &newName)
{
    m_name = newName;
}

void CharacterReference::setNameByQVariant(const QVariant &value)
{
    setName(value.toString());
}

QString CharacterReference::titleName()
{
    return m_titleName;
}

void CharacterReference::setTitleName(const QString &newTitleName)
{
    m_titleName = newTitleName;
}

void CharacterReference::setTitleNameByQVariant(const QVariant &value)
{
   setTitleName(value.toString());
}
