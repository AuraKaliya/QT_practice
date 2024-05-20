#include "auraswitchwidget01.h"
#include "clicklabel.h"

AuraSwitchWidget01::AuraSwitchWidget01(QWidget *parent)
    : AuraAbstractSwitchWidget{parent}
{

}

void AuraSwitchWidget01::addLabel(ClickLabel *label)
{
    if(!label) return;

    auto & entity= label->entity();

    if(!entity.hasComponent("Id"))
    {
        qDebug()<<"AuraSwitchWidget01::addLabel : no have Id. add it.";
        entity.addComponent("Id",new Component<Entity>(entity));
    }

    if(!entity.hasComponent("State"))
    {
        qDebug()<<"AuraSwitchWidget01::addLabel : no have State. add it.";
        entity.addComponent("State",new Component<Entity>(entity));
    }

    auto idComponent=entity.getComponent("Id");
    idComponent->setValue(m_labelList.size());

    auto stateComponent =entity.getComponent("State");
    stateComponent->setValue("Normal");

    connect(label,&ClickLabel :: clickedMe,this,[this](ClickLabel *label){
        setNowIndex(label->entity().getComponent("Id")->getValue<unsigned int>());
    });

    label->setDrawFunction(std::bind(&AuraSwitchWidget01::labelPaint,
                                     std::placeholders::_1,
                                     std::placeholders::_2 ));

    AuraAbstractSwitchWidget::addLabel(label);
}

void AuraSwitchWidget01::updateLabelState()
{
    m_labelList[m_nowIndex]->entity().getComponent("State")->setValue("Current");
    if(m_preIndex<0 || m_preIndex>=m_labelList.size()) return;
    m_labelList[m_preIndex]->entity().getComponent("State")->setValue("Normal");

    AuraAbstractSwitchWidget::updateLabelState();
}

void AuraSwitchWidget01::labelPaint(QPainter *p, ClickLabel *w)
{
    auto stateComponent= w->entity().getComponent("State");

    QColor color =UIStyle::getStateColor(stateComponent->getValue<QString>());
    p->setBrush(QBrush(color));
    p->setPen(QPen(color));
    p->drawRect(-1,-1,w->width()+2,w->height()+2);
    qDebug()<<"AuraSwitchWidget01::labelPaint | in label:"<<w;
}
