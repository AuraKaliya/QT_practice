#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "searchblok.h"
#include "slideblock.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


    void paintEvent(QPaintEvent * e)override ;

private:

    QLineEdit * searchLine;
    QPushButton * searchBtn;

    searchblok * searchBlock;

    QScrollArea * area;
    QWidget * showWidget;
    QHBoxLayout* HL;
    QGridLayout* GL;

    slideBlock *slidBtn;

    Ui::Widget *ui;
};
#endif // WIDGET_H
