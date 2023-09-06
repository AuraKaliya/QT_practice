#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QString url("C:/Users/Aura/Desktop/素材/image1.png");
    QPixmap pix(url);
    qDebug()<<pix.isNull();
    //setFixedSize(800,800);


    label1=new ClickLabel(this);
    label1->setGeometry(0,0,100,200);
    label1->setStyleSheet("background-color:red");
    label1->setStyleSheet("border-image:url("+url+")");

    label1->setVisible(true);
    label2=new QLabel(this);
    label2->setGeometry(0,0,100,200);
    label2->setStyleSheet("background-color:yellow");

    label1->showFullScreen();
    label1->setParent(nullptr);
    label2->setParent(nullptr);
    scene= new QGraphicsScene(this);
    QGraphicsProxyWidget* proxy = scene->addWidget(label1);
    QGraphicsProxyWidget* proxy2 = scene->addWidget(label2);

    QGraphicsView* view = new QGraphicsView(scene,this);

    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setWindowOpacity(0);
    view->setStyleSheet("background: transparent;border:0px");
    view->setWindowFlags(Qt::FramelessWindowHint);

    //QPoint point(50,400);
    //view->resize(500,500);
    //QPoint point(50,0);
    QPointF points(50,400);
    //QPointF scenePoint = view->mapToScene(point);
    //qDebug()<<scenePoint;
    //proxy->setTransformOriginPoint(scenePoint);
    qDebug()<<"-------------"<<proxy->geometry() <<view->geometry();

    proxy->setTransformOriginPoint(points);
    proxy2->setTransformOriginPoint(points);

    qDebug()<<"----"<<view->mapFromParent(label1->pos());
    proxy->setRotation(-45);
    proxy2->setRotation(45);


    //label1->move(500,300);
    //label1->move(300-(400*qSin(-25)),300+(400*(1-qCos(-25))));





    //view->setScene(scene);
    //view->show();

//    // 创建一个QLabel对象
//    QLabel* label = new QLabel("Hello, world!");
//    // 创建一个QGraphicsProxyWidget对象，并将其添加到图形场景中
//    QGraphicsScene* scene = new QGraphicsScene;
//    QGraphicsProxyWidget* proxy = scene->addWidget(label);
//    // 设置代理的位置和旋转角度
//    proxy->setPos(100, 100);
//    proxy->setRotation(45);
//    // 创建一个QGraphicsView对象，并将其设置为显示图形场景
//    QGraphicsView* view = new QGraphicsView;
//    view->setScene(scene);
//    view->show();


    connect(label1,&ClickLabel::clicked,[=](){
        qDebug()<<"This Clicked";
    });

//    // 创建一个QLabel对象
//    QLabel* label = new QLabel("Hello, world!");
//    // 创建一个QGraphicsProxyWidget对象，并将其添加到图形场景中
//    QGraphicsScene* scene = new QGraphicsScene;
//    QGraphicsProxyWidget* proxy = scene->addWidget(label);
//    // 设置代理的旋转角度为45度
//    proxy->setRotation(45);
//    // 创建一个QGraphicsView对象，并将其设置为显示图形场景
//    QGraphicsView* view = new QGraphicsView;
//    view->setScene(scene);
//    view->show();
    // 使用不同的参数调用setPos()方法
   // proxy->setPos(0, 0); // 将代理小部件移动到(0, 0)的位置
   //proxy->setPos(100, 100); // 将代理小部件移动到(100, 100)的位置
    //proxy->setPos(QPointF(200, 200)); // 将代理小部件移动到(200, 200)的位置




}

Widget::~Widget()
{
    delete ui;
}

