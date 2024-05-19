#include "auraclassifydisplaywidget01.h"


AuraClassifyDisplayWidget01::AuraClassifyDisplayWidget01(AuraSwitchWidget01 *switchWidget, QStackedWidget* stackedWidget,QWidget *parent)
    : QWidget{parent}
    ,m_switchWidget(switchWidget)
    ,m_stackedWidget(stackedWidget)
{
    m_mainLayout=new QVBoxLayout(this);
    preInit();
}

void AuraClassifyDisplayWidget01::addWidget(ClickLabel *lb, QWidget *w)
{
    int nowCount =m_stackedWidget->count();
    m_switchWidget->addLabel(lb);
    m_stackedWidget->addWidget(w);
    if(!nowCount) m_switchWidget->setNowIndex(0);

}

void AuraClassifyDisplayWidget01::preInit()
{
    if(!m_switchWidget) m_switchWidget=new AuraSwitchWidget01();
    if(!m_stackedWidget) m_stackedWidget=new QStackedWidget();

    m_switchWidget->setParent(this);
    m_switchWidget->setVisible(true);

    m_stackedWidget->setParent(this);
    m_stackedWidget->setVisible(true);

    m_mainLayout->addWidget(m_switchWidget,1);
    m_mainLayout->addWidget(m_stackedWidget,14);

    setLayout(m_mainLayout);

    connect(m_switchWidget,&AuraSwitchWidget01::nowIndexChanged,m_stackedWidget,&QStackedWidget::setCurrentIndex);
    connect(m_stackedWidget,&QStackedWidget::currentChanged,this,[](int i){
        qDebug()<<"QStackedWidget::currentChanged | now Idx:"<<i;
    });
}
