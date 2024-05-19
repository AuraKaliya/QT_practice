#include "aurastatelabel01.h"

#include <QPaintEvent>

AuraStateLabel01::AuraStateLabel01(QWidget *parent)
    : ClickLabel{parent}
{
    preInit();
}

AuraStateLabel01::AuraStateLabel01(const QString &text, QWidget *parent, Qt::WindowFlags f)
:ClickLabel{text,parent,f}
{
    preInit();
}

void AuraStateLabel01::paintEvent(QPaintEvent *e)
{
    auto stateComponent= entity().getComponent("State");

    m_nowColor=UIStyle::getStateColor(stateComponent->getValue<QString>());

    QPainter p(this);
    p.setBrush(QBrush(m_nowColor));
    p.setPen(QPen(m_nowColor));
    p.drawRect(-1,-1,width()+2,height()+2);

    ClickLabel::paintEvent(e);
}

void AuraStateLabel01::preInit()
{
    entity().addComponent("Id" , new Component<Entity>(entity()));
    entity().addComponent("State" , new Component<Entity>(entity()));
}
