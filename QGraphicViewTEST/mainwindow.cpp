#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPen>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iTemp=0;
    scaleValues=3;
    shearValues=3;

    QGraphicsScene * scence =new QGraphicsScene;
    scence->setSceneRect(0,0,1200,1200);
    scence->setBackgroundBrush(Qt::red);
    scence->addText(QString("1234567890"),QFont(QString("SimSun")));

    QPixmap * pix=new QPixmap();
    pix->load("D:/QTF/QGraphicViewTEST/hua.png");
    *pix=pix->scaled(200,200);
    qDebug()<<pix->isNull();

    QPixmap *px2=new QPixmap("D:/QTF/QGraphicViewTEST/hua.png");
    *px2=px2->scaled(50,50);

    QPixmap *px3=new QPixmap("D:/QTF/QGraphicViewTEST/hua2.png");
    *px3=px3->scaled(80,80);

    QPixmap *px4=new QPixmap("D:/QTF/QGraphicViewTEST/Hero1.png");


    it=new GraphicsItem(pix);
    scence->addItem(it);
    it->setPos(200,0);

    it2=new GraphicsItem(px2);
    scence->addItem(it2);
    it2->setPos(0,0);

    it3=new GraphicsItem(px2);
    scence->addItem(it3);
    it3->setPos(52,0);


    it4=new Item2DMap(pix);
    QMap<int,QPixmap*> map=* new QMap<int,QPixmap*>;
    map[101]=pix;
    map[102]=px2;
    map[103]=px3;
    it4->init(10,10,map,102);
    scence->addItem(it4);
    it4->setPos(200,200);


    int startX=0;
    int startY=0;
    int perWidth=32;
    int perHeight=32;
    int xInterval=0;
    int yInterval=1;

    it5=new DynamicItem(pix);
    QVector<QString> stateList;
    stateList<<"Normal"<<"Down"<<"Left"<<"Right"<<"Up";
    QVector<QVector<QPixmap*> > spixList;

    QVector<QVector<int>> spixIdexList;
    spixIdexList<<QVector<int >{0}<<QVector<int >{0,1,2,3}
                 <<QVector<int >{4,5,6,7}<<QVector<int >{8,9,10,11}
                 <<QVector<int >{12,13,14,15};

    int sourceWidth=px4->width();
    int sourceHeight=px4->height();

    qDebug()<<"sourceWidth:"<<sourceWidth;
    qDebug()<<"sourceHeight:"<<sourceHeight;


    //进行切割。
        int nowY=startY;
    //暂时用不上--用于控制切割碎片的
    int pixHeight=qMin(sourceHeight-nowY,perHeight);
    while((nowY+perHeight+yInterval)<=sourceHeight)
    {
        int nowX=startX;
        int pixWidth=qMin(sourceWidth-nowX,perWidth);
        while((nowX+perWidth+xInterval)<=sourceWidth)
        {
            pixList.append(px4->copy(nowX,nowY,perWidth,perHeight));
            nowX+=(xInterval+perWidth);
            qDebug()<<"nowX"<<nowX;
        }
        nowY+=(yInterval+perHeight);

        qDebug()<<"nowY"<<nowY;
    }
    qDebug()<<"pixList:"<<pixList.size();
    qDebug()<<"stateList :"<<stateList.size();
    qDebug()<<"spixIdexList:"<<spixIdexList.size();
    qDebug()<<"spixIdexList0:"<<spixIdexList[0].size();
    qDebug()<<"spixIdexList1:"<<spixIdexList[1].size();

    for(int i=0;i<stateList.size();i++)
    {
        QVector<QPixmap*> px;
        for(auto it:spixIdexList[i])
        {
            qDebug()<<"it"<<it <<pixList[it];
            px.append(&(pixList[it]));
        }
        spixList.append(px);
    }


    it5->initPix(stateList,spixList);
    it5->changeState("Down");


    timer=new QTimer(this);
    timer->setInterval(100);
    connect(timer,&QTimer::timeout,this,[this](){
        it5->pixChanged();
    });

    scence->addItem(it5);
    it5->setPos(400,400);



    view =new QGraphicsView();
    view->move(0,0);
    //view->setBackgroundBrush(Qt::white);
    view->setScene(scence);
    view->setFixedSize(802,802);
    view->centerOn(QPointF(300,300));
    view->setDragMode(QGraphicsView::RubberBandDrag);

    //
    controlFrame=new QFrame;
    CreateControlFrame();
    //view->setVisible(true);
    view->show();









}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    //qDebug()<<"this";
    if(!view->scene()->selectedItems().empty())
    {
        QRect rect;
        rect.setRect(view->scene()->selectedItems()[0]->x(),view->scene()->selectedItems()[0]->y(),0,0);
        for(auto it:view->scene()->selectedItems())
        {
            rect.setX(qMin((int)rect.x(),(int)it->x()));
            rect.setY(qMin((int)rect.y(),(int)it->y()));
            rect.setWidth(qMax((int)rect.width(),(int)(it->x()+it->boundingRect().width()-rect.x())));
            rect.setHeight(qMax((int)rect.height(),(int)(it->y()+it->boundingRect().height()-rect.y())));
        }

        //qDebug()<<"this2";
        QPen pen(Qt::white,3,Qt::DashDotDotLine,Qt::RoundCap,Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawRect(rect);
        //qDebug()<<"---"<<view->scene()->selectionArea().boundingRect();
        painter.end();
    }

}
void MainWindow::CreateControlFrame()
{


}


void MainWindow::on_pushButton_clicked()
{

//    for(auto it:view->scene()->selectedItems())
//    {
//        GraphicsItem* item=static_cast<GraphicsItem*>(it);
//        qDebug()<<view->mapFromScene(item->pos());
//        item->show();
//    }

    it4->setPix(2,3,103);
    it4->setPix(2,4,103);
    it4->setPix(2,1,103);
    timer->start();
}


void MainWindow::on_pushButton_2_clicked()
{
    it5->changeState("Left");
}

