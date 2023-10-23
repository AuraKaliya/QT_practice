#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "Factory.hpp"
#include "basewidget.h"
#include "baseobject.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    BaseWidget* m_widget=nullptr;
    BaseObject* m_object=nullptr;
};
#endif // WIDGET_H
