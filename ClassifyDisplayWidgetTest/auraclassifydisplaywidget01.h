#ifndef AURACLASSIFYDISPLAYWIDGET01_H
#define AURACLASSIFYDISPLAYWIDGET01_H

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>

//============需要替换成接口文件===============
#include "auraswitchwidget01.h"
//============需要替换成接口文件===============


class AuraClassifyDisplayWidget01 : public QWidget
{
    Q_OBJECT
public:
    explicit AuraClassifyDisplayWidget01(AuraSwitchWidget01* switchWidget,QStackedWidget* stackedWidget,QWidget *parent = nullptr);
    void addWidget(ClickLabel* lb,QWidget* w);
private:
    void preInit();
private:
    QVBoxLayout* m_mainLayout=nullptr;
    AuraSwitchWidget01* m_switchWidget=nullptr;
    QStackedWidget* m_stackedWidget=nullptr;

signals:

};

#endif // AURACLASSIFYDISPLAYWIDGET01_H
