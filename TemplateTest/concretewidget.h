#ifndef CONCRETEWIDGET_H
#define CONCRETEWIDGET_H
#include "basewidget.h"
#include "Registor.hpp"

#include <QDebug>
class ConcreteWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit ConcreteWidget(QWidget *parent = nullptr);
    void debug()override;
protected:

signals:

};

REGISTER_WIDGET(ConcreteWidget,BaseWidget)
#endif // CONCRETEWIDGET_H
