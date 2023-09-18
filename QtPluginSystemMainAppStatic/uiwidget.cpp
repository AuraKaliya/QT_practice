#include "uiwidget.h"

UIWidget::UIWidget(QWidget *parent)
    : QWidget{parent}
{

}

UIWidget *UIWidget::getWidget()
{
    return this;
}

void UIWidget::addWidget(UIWidget *w)
{

}

QMap<QString, Manager *> UIWidget::getManager()
{
    return m_managerDictionaryByName;
}

void UIWidget::addManager(QString s, Manager *m)
{
    m_managerDictionaryByName.insert(s,m);
}
