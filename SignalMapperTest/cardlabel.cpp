#include "cardlabel.h"

CardLabel::CardLabel(int id, QWidget *parent)
    : ClickLabel{parent}
    ,m_id(id)
{
//一种是重写事件函数
//一种是信号的（扩展）转发
    connect(this,&ClickLabel::clicked,this,[this](){
    emit clickedCard(m_id);
});
}

unsigned int CardLabel::id() const
{
    return m_id;
}

void CardLabel::setId(unsigned int newId)
{
    m_id = newId;
}
