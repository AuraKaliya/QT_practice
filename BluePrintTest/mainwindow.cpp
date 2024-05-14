#include "mainwindow.h"
#include "./ui_mainwindow.h"


//=============test====================

#include "Item/Node/nodeobjectitem.h"
#include "Item/Node/testnode.h"
#include <QKeyEvent>
//=============test====================




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,600);
    m_view=new BlueprintsView(this);

    setCentralWidget(m_view);






}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_P)
    {

        NodeObjectItem * item =new TestNode();
        item->setNodeTitle("TestNode1");


        m_view->scene()->addItem(item);

    }
}

