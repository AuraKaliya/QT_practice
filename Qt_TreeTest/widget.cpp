#include "widget.h"
#include "ui_widget.h"

#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QStringList>
#include <QString>
#include <QList>
#include <QAbstractItemView>

#include "myproxymodel.h"
#include "myitemmodel.h"
#include "myview.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("哈哈哈哈哈哈哈");
    setWindowFlags(windowFlags()& -Qt::WindowMinMaxButtonsHint);


    QPixmap *pPhoto1=new QPixmap(":/Image_90008.png");
    QPixmap *pPhoto2=new QPixmap(":/Image_90009.png");
    QPixmap *pPhoto3=new QPixmap(":/Image_90010.png");
    QIcon *ico1=new QIcon;
    QIcon *ico2=new QIcon;
    QIcon *ico3=new QIcon;
    ico1->addPixmap(*pPhoto1);
    ico2->addPixmap(*pPhoto2);
    ico3->addPixmap(*pPhoto3);


    QStandardItemModel * model=new QStandardItemModel();

    //设置列项头
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("图片")<<QStringLiteral("位置"));

    for(int i=0;i<5;i++)
    {
        QList<QStandardItem*> items1;
        QStandardItem* item1=new QStandardItem(*ico1,QString("image"+QString::number(i)));
        QStandardItem* item2=new QStandardItem("****一级节点****");
        items1<<item1<<item2;
        model->appendRow(items1);

        for(int j=0;j<5;j++)
        {
            QList<QStandardItem*> items2;
            QStandardItem* item3=new QStandardItem(*ico2,QString("imageer"+QString::number(i+j)));
            QStandardItem* item4=new QStandardItem("****二级节点****");
            items2<<item3<<item4;
            item1->appendRow(items2);

            for(int k=0;k<5;k++)
            {
                QList<QStandardItem*> items3;
                QStandardItem* item5=new QStandardItem(*ico3,QString("imageer"+QString::number(i+j+k)));
                QStandardItem* item6=new QStandardItem("****三级节点****");
                items3<<item5<<item6;
                item3->appendRow(items3);

            }

        }

    }




    //test
   // ui->treeView->setDragDropMode(QAbstractItemView::InternalMove);    //设置可拖拽模式    --性能不太行
    //ui->treeView->setModel(model);

    // 创建底层模型
    QStandardItemModel *sourceModel=new QStandardItemModel;
    sourceModel->appendRow(new QStandardItem("Item 1"));
    sourceModel->appendRow(new QStandardItem("Item 2"));
    sourceModel->appendRow(new QStandardItem("Item 3"));
    sourceModel->appendRow(new QStandardItem("Item 4"));
    sourceModel->appendRow(new QStandardItem("Item 5"));



    //创建自定义底层模型
    MyItemModel * mySourceModel=new MyItemModel;
    mySourceModel->setColumnCount(2);
    mySourceModel->setRowCount(4);
    mySourceModel->setItem(0,0,new QStandardItem("球球"));
    mySourceModel->setItem(0,1,new QStandardItem("99"));
    mySourceModel->setItem(1,0,new QStandardItem("猪小明"));
    mySourceModel->setItem(1,1,new QStandardItem("59"));
    mySourceModel->setItem(2,0,new QStandardItem("锅盖"));
    mySourceModel->setItem(2,1,new QStandardItem("111"));
    mySourceModel->setItem(3,0,new QStandardItem("闰土"));
    mySourceModel->setItem(3,1,new QStandardItem("999"));
    //mySourceModel->setHorizontalHeaderItem(0,new QStandardItem("姓名"));
    //mySourceModel->setHorizontalHeaderItem(1,new QStandardItem("成绩"));
    mySourceModel->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("姓名")<<QStringLiteral("成绩"));

    ui->treeView->setModel(mySourceModel);
    ui->treeView->setDragDropMode(QAbstractItemView::DragDrop);


     MyItemModel * mySourceModel2=new MyItemModel;
    mySourceModel2->setColumnCount(2);
    mySourceModel2->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("姓名")<<QStringLiteral("成绩"));
    //mySourceModel2->setHorizontalHeaderItem(1,new QStandardItem("成绩"));
    ui->listView_2->setModel(mySourceModel2);
    ui->listView_2->setDragDropMode(QAbstractItemView::DropOnly);




#if 0

    // 创建自定义代理模型
    MyProxyModel *proxyModel=new MyProxyModel;
    proxyModel->setSourceModel(sourceModel);

    // 创建视图组件

    ui->listView->setModel(proxyModel);

#endif




    MyView * view=new MyView(this);
    view->setVisible(true);
    QStandardItemModel* testModel=new QStandardItemModel(3,3);

    testModel->setData(testModel->index(0,0),"aaa");
    testModel->setData(testModel->index(0,1),"aaa");
    testModel->setData(testModel->index(0,2),"aaa");
    testModel->setData(testModel->index(1,0),"aaa");
    testModel->setData(testModel->index(1,1),"aaa");
    testModel->setData(testModel->index(1,2),"aaa");
    testModel->setData(testModel->index(2,0),"aaa");
    testModel->setData(testModel->index(2,1),*ico2,Qt::DecorationPropertyRole);

    QLabel *p=new QLabel("111",view);
    p->setAutoFillBackground(1);
    p->setAlignment(Qt::AlignCenter);
    p->resize(111,20);

    view->setModel(testModel);
    view->setGeometry(0,0,333,222);



}

Widget::~Widget()
{
    delete ui;
}

