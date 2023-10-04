#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "socketwidget.h"

#pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->port->setText("9999");
    setWindowTitle("服务器");
    m_server=new QTcpServer(this);
    m_status=new QLabel;

    connect(m_server,&QTcpServer::newConnection,this,[=](){
        QTcpSocket* socket=m_server->nextPendingConnection();
        m_socketList.append(socket);
        //SocketWidget socketWidget(socket);
        ui->socketList->addItem(QString::number(QRandomGenerator::global()->bounded(200)));
        connect(ui->socketList,&QListWidget::currentRowChanged,this,[=](int row){
            m_nowSocket=m_socketList[row];
            ui->NowSocket->setText("NowSocket:"+ui->socketList->currentItem()->text());
        });


        m_status->setPixmap(QPixmap(":/f2.png").scaled(QSize(20,20)));
        //检测是否可接收数据
        connect(socket,&QTcpSocket::readyRead,this,[=](){
            QByteArray data=socket->readAll();
            ui->recalled->append("客户端say："+QString(data));
        });

        connect(socket,&QTcpSocket::disconnected,this,[=](){
            socket->close();
            socket->deleteLater();
        });

    });



    //状态栏添加
    m_status->setPixmap(QPixmap(":/f1.png").scaled(QSize(20,20)));
    ui->statusbar->addWidget(new QLabel("连接状态："));
    ui->statusbar->addWidget(m_status);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listenStart_clicked()
{
    unsigned short port=ui->port->text().toUShort();
    m_server->listen(QHostAddress::Any,port);
    ui->listenStart->setDisabled(true);

}


void MainWindow::on_sendMessage_clicked()
{
    if(m_nowSocket!=nullptr)
    {
        QString msg=ui->sendInfo->toPlainText();
        m_nowSocket->write(msg.toUtf8());
        ui->recalled->append("服务器To"+ui->socketList->currentItem()->text()+":"+msg);
    }

}

