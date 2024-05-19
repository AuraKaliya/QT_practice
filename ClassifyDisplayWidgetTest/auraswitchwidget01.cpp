#include "auraswitchwidget01.h"
#include "clicklabel.h"

AuraSwitchWidget01::AuraSwitchWidget01(QWidget *parent)
    : QWidget{parent}
{
    m_nowIndex=-1;
    m_preIndex=-1;
}

void AuraSwitchWidget01::initWidget()
{

}

void AuraSwitchWidget01::addLabel(ClickLabel *label)
{
    if(!label) return;

    auto entity= label->entity();

    if(!entity.hasComponent("Id"))
    {
        entity.addComponent("Id",new Component<Entity>(entity));
    }

    if(!entity.hasComponent("State"))
    {
        entity.addComponent("State",new Component<Entity>(entity));
    }

    auto idComponent=entity.getComponent("Id");
    idComponent->setValue(m_labelList.size());

    auto stateComponent =entity.getComponent("State");
    stateComponent->setValue("Normal");

    label->setParent(this);

    connect(label,&ClickLabel :: clickedMe,this,[this](ClickLabel *label){
        setNowIndex(label->entity().getComponent("Id")->getValue<unsigned int>());
    });

    label->setVisible(true);
    m_labelList.append(label);
    update();
}

ClickLabel *AuraSwitchWidget01::getLabel(int index)
{
    if(index<0 || index>=m_labelList.size())
        return nullptr;
    return m_labelList[index];
}

void AuraSwitchWidget01::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    int count=m_labelList.size();
    if(count<1) return;
    int w=width()/count;
    int h=height();
    for(int i=0;i<m_labelList.count();++i)
    {
        m_labelList[i]->setGeometry(i*w,0,w,h);
    }
}

int AuraSwitchWidget01::nowIndex() const
{
    return m_nowIndex;
}

void AuraSwitchWidget01::setNowIndex(int newNowIndex)
{
    if(newNowIndex<0 || newNowIndex>=m_labelList.size()) return;
    m_preIndex = m_nowIndex;
    m_nowIndex = newNowIndex;

    updateLabelState();
}

void AuraSwitchWidget01::updateLabelState()
{
    if(m_nowIndex<0 || m_nowIndex>=m_labelList.size()) return;
    if(m_preIndex==m_nowIndex) return;
    m_labelList[m_nowIndex]->entity().getComponent("State")->setValue(QVariant("Current"));
    if(m_preIndex<0 || m_preIndex>=m_labelList.size()) return;
    m_labelList[m_preIndex]->entity().getComponent("State")->setValue(QVariant("Normal"));
    emit nowIndexChanged(m_nowIndex);
    update();
}

void AuraSwitchWidget01::updateLayout()
{
    resizeEvent(nullptr);
}
