#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(800,600);

    TestWidget* w1 =new TestByQTimerWidget(0,10000,this);
    w1->setGeometry(0,0,200,600);
    w1->initWidget();

    TestWidget* w2=new TestByCoreWidget(0,10000,this);
    w2->setGeometry(200,0,200,600);
    w2->initWidget();


    TestWidget* w3=new TestByThreadWidget(0,10000,this);
    w3->setGeometry(400,0,200,600);
    w3->initWidget();

    TestByCaculatorWidget* w4=new TestByCaculatorWidget(0,10000,this);
    w4->setGeometry(600,0,200,600);
    w4->initWidget();


#ifdef MOVETOTHREAD
    QThread *t=new QThread();
    w4->caculator()->moveToThread(t);
    t->start();
#endif



}

Widget::~Widget()
{
    delete ui;
}

