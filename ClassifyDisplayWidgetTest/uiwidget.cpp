#include "uiwidget.h"

UIWidget::UIWidget(QWidget *parent)
    : QWidget{parent}
{

}

UIWidget::~UIWidget()
{

}

void UIWidget::initWidget()
{

}



void UIWidget::updateLayout()
{

}

void UIWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    updateLayout();
}
