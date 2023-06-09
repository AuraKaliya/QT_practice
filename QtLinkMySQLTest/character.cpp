#include "character.h"

Character::Character()
{

}

Character::Character(ReferenceType type)
{
    //CharacterReference::show();
    if(type==ReferenceType::CharacterReference)
    {
        setID(CharacterReference::getInstance()->ID());
        setName(CharacterReference::getInstance()->name());
        setTitleName(CharacterReference::getInstance()->titleName());
    }
}

int Character::ID() const
{
    return m_ID;
}

void Character::setID(int newID)
{
    m_ID = newID;
}

QString Character::name() const
{
    return m_name;
}

void Character::setName(const QString &newName)
{
    m_name = newName;
}

QString Character::titleName() const
{
    return m_titleName;
}

void Character::setTitleName(const QString &newTitleName)
{
    m_titleName = newTitleName;
}

void Character::showInfo()
{
    qDebug()<<"-------------------------";
    qDebug()<<"ID:"<<m_ID;
    qDebug()<<"Name:"<<m_name;
    qDebug()<<"TitleName:"<<m_titleName;
    qDebug()<<"-------------------------";
}
