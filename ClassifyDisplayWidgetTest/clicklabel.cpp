#include "clicklabel.h"

ClickLabel::ClickLabel(QWidget *parent)
    : QLabel{parent},m_entity(Entity())
{

}

ClickLabel::ClickLabel(const QString &text, QWidget *parent, Qt::WindowFlags f):QLabel{text,parent,f},m_entity(Entity())
{

}

void ClickLabel::mouseReleaseEvent(QMouseEvent *e)
{
    emit clicked();
    emit clickedMe(this);
}

Entity &ClickLabel::entity()
{
    return m_entity ;
}




