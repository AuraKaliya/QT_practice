#include "widget.h"
#include "./ui_widget.h"

#include "aurastatelabel01.h"
#include "auraclassifydisplaywidget01.h"
#include "auraswitchwidget01.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_P)
    {

        AuraAbstractSwitchWidget * sw=new AuraSwitchWidget01();

        QStackedWidget * stw=new QStackedWidget();

        AuraClassifyDisplayWidget01* w=new AuraClassifyDisplayWidget01(sw,stw);
        w->initWidget();

        w->addWidget(new ClickLabel("Test1"),new QWidget());
        w->addWidget(new ClickLabel("Test2"),new QWidget());
        w->resize(400,800);
        w->show();
    }
}

