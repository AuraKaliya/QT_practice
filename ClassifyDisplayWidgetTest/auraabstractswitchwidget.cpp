#include "auraabstractswitchwidget.h"

AuraAbstractSwitchWidget::AuraAbstractSwitchWidget(QWidget *parent)
    : UIWidget{parent}
    ,m_nowIndex(-1)
    ,m_preIndex(-1)
    ,m_labelList{}
{

}

void AuraAbstractSwitchWidget::addLabel(ClickLabel *label)
{
    label->setParent(this);
    label->setVisible(true);
    m_labelList.append(label);
    update();
}

ClickLabel *AuraAbstractSwitchWidget::getLabel(int index)
{
    if(index<0 || index>=m_labelList.size())
        return nullptr;
    return m_labelList[index];
}

int AuraAbstractSwitchWidget::nowIndex() const
{
    return m_nowIndex;
}

void AuraAbstractSwitchWidget::setNowIndex(int newNowIndex)
{
    if(newNowIndex<0 || newNowIndex>=m_labelList.size()) return;
    if(newNowIndex == m_nowIndex) return;

    m_preIndex = m_nowIndex;
    m_nowIndex = newNowIndex;

    emit nowIndexChanged(m_nowIndex);
    updateLabelState();
}

void AuraAbstractSwitchWidget::updateLayout()
{
    int count=m_labelList.size();
    if(count<1) return;
    int w=width()/count;
    int h=height();
    for(int i=0;i<m_labelList.count();++i)
    {
        m_labelList[i]->setGeometry(i*w,0,w,h);
    }
}

void AuraAbstractSwitchWidget::updateLabelState()
{
    update();
}
