#include "auraclassifydisplaywidget01.h"


AuraClassifyDisplayWidget01::AuraClassifyDisplayWidget01(AuraAbstractSwitchWidget *switchWidget, QStackedWidget* stackedWidget,QWidget *parent)
    : UIWidget{parent}
    ,m_switchWidget(switchWidget)
    ,m_stackedWidget(stackedWidget)
{
    preInit();
}

void AuraClassifyDisplayWidget01::addWidget(ClickLabel *lb, QWidget *w)
{
    int nowCount =m_stackedWidget->count();
    m_switchWidget->addLabel(lb);
    m_stackedWidget->addWidget(w);
    if(!nowCount) m_switchWidget->setNowIndex(0);

}

void AuraClassifyDisplayWidget01::initWidget()
{
    //======================设置======================

    if(!m_switchWidget) m_switchWidget=new AuraAbstractSwitchWidget();
    if(!m_stackedWidget) m_stackedWidget=new QStackedWidget();

    m_switchWidget->setParent(this);
    m_switchWidget->setVisible(true);

    m_stackedWidget->setParent(this);
    m_stackedWidget->setVisible(true);

    m_mainLayout->addWidget(m_switchWidget,1);
    m_mainLayout->addWidget(m_stackedWidget,14);

    setLayout(m_mainLayout);

    connect(m_switchWidget,&AuraAbstractSwitchWidget::nowIndexChanged,m_stackedWidget,&QStackedWidget::setCurrentIndex);
    connect(m_stackedWidget,&QStackedWidget::currentChanged,this,[](int i){
        qDebug()<<"QStackedWidget::currentChanged | now Idx:"<<i;
    });

    //======================设置======================
}

void AuraClassifyDisplayWidget01::preInit()
{
    //======================构建======================
    m_mainLayout=new QVBoxLayout(this);
    //======================构建======================
}
