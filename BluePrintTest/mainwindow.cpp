#include "mainwindow.h"
#include "./ui_mainwindow.h"


//=============test====================

#include "Item/Node/nodeobjectitem.h"
#include "Item/Node/testnode.h"
#include "Item/Node/testendnode.h"
#include "Item/Node/teststartnode.h"
#include "Item/Node/testvaluenode.h"
#include "Object/testobject.h"
#include "Item/Node/testsignalnode.h"
#include "Manager/nodemanager.h"

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
        item->setNodeTitle("SolveNode "+QString::number(NodeManager::nodeId()));
        NodeManager::registerNode(item);
        m_view->scene()->addItem(item);

        NodeObjectItem * item2 =new TestSignalNode();
        item2->setNodeTitle("SignalNode "+QString::number(NodeManager::nodeId()));
        NodeManager::registerNode(item2);
        m_view->scene()->addItem(item2);

        NodeObjectItem * item3 =new TestValueNode();
        item3->setNodeTitle("ValueNode "+QString::number(NodeManager::nodeId()));
        NodeManager::registerNode(item3);
        m_view->scene()->addItem(item3);

        NodeObjectItem * item4 =new TestEndNode();
        item4->setNodeTitle("endNode "+QString::number(NodeManager::nodeId()));
        NodeManager::registerNode(item4);
        m_view->scene()->addItem(item4);

        m_obj =new TestObject();
        BlueprintsSignalManager::bindObjectAndPort("Test",m_obj->objId(),item2->portList()[0]->portId());

        for(auto it:item2->portList())
            qDebug()<<"==== port id"<<it->portId();
    }

    if(e->key() == Qt::Key_O)
    {
        NodeManager::preInit();

    }
    if(e->key() ==Qt::Key_I)
    {
        NodeManager::run();
    }

    if(e->key() ==Qt::Key_U)
    {
        m_obj->setValue(m_obj->value().toInt()+3);
        m_obj->signalMode()->emitSignal("Test");
    }

    if(e->key() ==Qt::Key_Y)
    {
        NodeManager::setSolveFlag(false);
    }
}

