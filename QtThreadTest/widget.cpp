#include "widget.h"
#include "ui_widget.h"
# include "mythread.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    GenerateThread * gen =new GenerateThread;
    BubSortThread* bub=new BubSortThread;
    QuickSortThread *quick=new QuickSortThread;


    connect(this,&Widget::starting,gen,&GenerateThread::receiveNumber);

    connect(ui->startBtn,&QPushButton::clicked,[=](){
        emit starting(10000);
        gen->start();
    });

    connect(gen,&GenerateThread::sendArray,bub,&BubSortThread::receiveArray);
    connect(gen,&GenerateThread::sendArray,quick,&QuickSortThread::receiveArray);
    connect(gen,&GenerateThread::sendArray,this,[=](QVector<int> list){
        bub->start();
        quick->start();
        for(const auto & it:list)
        {
            ui->randomList->addItem(QString::number(it));
        }
    });
    connect(bub,&BubSortThread::sendArray,this,[=](QVector<int> list){

        for(const auto & it:list)
        {
            ui->buboList->addItem(QString::number(it));
        }
    });
    connect(quick,&QuickSortThread::sendArray,this,[=](QVector<int> list){
        for(const auto & it:list)
        {
            ui->quickList->addItem(QString::number(it));
        }
    });
}

Widget::~Widget()
{
    delete ui;
}

