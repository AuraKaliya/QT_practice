#include "widget.h"
#include "./ui_widget.h"


#include <QPainter>


Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    PieWidget* widget=new PieWidget(4,200,this);
    setCentralWidget(widget);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e)
{

}

