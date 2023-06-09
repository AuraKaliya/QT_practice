#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include "character.h"
#include "initbydatabase.h"

#pragma execution_character_set("utf-8")
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
};
#endif // WIDGET_H
