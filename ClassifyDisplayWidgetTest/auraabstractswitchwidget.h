#ifndef AURAABSTRACTSWITCHWIDGET_H
#define AURAABSTRACTSWITCHWIDGET_H

#include <QVector>

#include "uiwidget.h"

#include "clicklabel.h"

/*
    接口类   用于切换的Widget
    1. addLabel  添加切换目标按钮
    2. nowIndex  当前idx
    3. updateLabelState 更新
*/
/*
    应该只实现为接口
*/
class AuraAbstractSwitchWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit AuraAbstractSwitchWidget(QWidget *parent = nullptr);


    virtual void addLabel(ClickLabel* label);
    ClickLabel* getLabel(int index);
    int nowIndex() const;


public slots:
    void setNowIndex(int newNowIndex);
    void updateLayout()override;
    virtual void updateLabelState();
protected:
    QVector<ClickLabel*> m_labelList;
    int m_nowIndex;
    int m_preIndex;

signals:
    void nowIndexChanged(int);
};

#endif // AURAABSTRACTSWITCHWIDGET_H
