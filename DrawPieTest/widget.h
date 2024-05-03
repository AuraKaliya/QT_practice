#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>

#include "piewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent*e)override;


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
