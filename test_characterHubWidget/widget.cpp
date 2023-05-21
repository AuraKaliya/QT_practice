#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    resize(450,900);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);

    //上边
//    searchLine=new QLineEdit(this);
//    searchBtn= new QPushButton(this);

//    searchLine->setGeometry(25,50,400,100);
//    searchBtn->setGeometry(325,50,100,100);

    searchBlock=new searchblok();
    searchBlock->setParent(this);
    searchBlock->setGeometry(25,50,400,30);
    //中间
    area= new QScrollArea (this);
    area->setGeometry(25,100,400,650);

    showWidget=new QWidget();
    area->setWidget(showWidget);
    showWidget->setGeometry(0,0,area->width(),area->height());

    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //下方
    slidBtn=new slideBlock();
    slidBtn->setParent(this);

    slidBtn->setRect(QRect(25,775,400,65));
    slidBtn->setGeometry(360,775,65,65);
    slidBtn->setFixPos(slidBtn->pos());


}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e)
{

    QPainter painter(this);
    painter.drawPixmap(this->rect(),QPixmap(":/test_transparency2.png"));


}

