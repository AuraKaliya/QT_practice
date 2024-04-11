#include "uiwidget.h"

UIWidget::UIWidget(QWidget *parent)
    : QWidget{parent}
{

}

void UIWidget::init()
{

}

void UIWidget::demoInit()
{

}

void UIWidget::setUIStyle()
{

}

GameDemo *UIWidget::nowDemo() const
{
    return m_nowDemo;
}

void UIWidget::setNowDemo(GameDemo *newNowDemo)
{
    if (m_nowDemo == newNowDemo)
        return;
    m_nowDemo = newNowDemo;
    emit nowDemoChanged();
}

UIState UIWidget::nowUIState() const
{
    return m_nowUIState;
}

void UIWidget::setNowUIState(UIState newNowUIState)
{
    if (m_nowUIState == newNowUIState)
        return;
    m_nowUIState = newNowUIState;
    emit nowUIStateChanged();
}
