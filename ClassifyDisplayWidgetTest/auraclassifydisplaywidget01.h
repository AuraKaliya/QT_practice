#ifndef AURACLASSIFYDISPLAYWIDGET01_H
#define AURACLASSIFYDISPLAYWIDGET01_H

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>


//============需要替换成接口文件===============
#include "uiwidget.h"
#include "auraabstractswitchwidget.h"
//============需要替换成接口文件===============


class AuraClassifyDisplayWidget01 : public UIWidget
{
    Q_OBJECT
public:
    explicit AuraClassifyDisplayWidget01(AuraAbstractSwitchWidget* switchWidget,QStackedWidget* stackedWidget,QWidget *parent = nullptr);
    void addWidget(ClickLabel* lb,QWidget* w);
    void initWidget()override;
protected:
    void preInit() ;
private:
    QVBoxLayout* m_mainLayout=nullptr;
    AuraAbstractSwitchWidget* m_switchWidget=nullptr;
    QStackedWidget* m_stackedWidget=nullptr;

signals:

};

#endif // AURACLASSIFYDISPLAYWIDGET01_H
