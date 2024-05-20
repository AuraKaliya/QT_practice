#ifndef AURASWITCHWIDGET01_H
#define AURASWITCHWIDGET01_H

#include <QWidget>
#include "clicklabel.h"
#include "auraabstractswitchwidget.h"
#include "UIStyle.hpp"

class AuraSwitchWidget01 : public AuraAbstractSwitchWidget
{
    Q_OBJECT
public:
    explicit AuraSwitchWidget01(QWidget *parent = nullptr);
    void addLabel(ClickLabel* label)override;
    void updateLabelState()override;

protected:
   static void labelPaint(QPainter* p,ClickLabel* w);
private:
signals:

};

#endif // AURASWITCHWIDGET01_H
