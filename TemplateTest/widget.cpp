#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_widget=Factory<BaseWidget>::GetInstance()->CreateWidget("ConcreteWidget");
    m_widget->debug();

    m_object=Factory<BaseObject>::GetInstance()->CreateObject("ConcreteObject");
    m_object->debug();
}

Widget::~Widget()
{
    delete ui;
}

