#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTcpSocket>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_server=new    QTcpServer(this);

    connect(m_server,&QTcpServer::newConnection,this,[=]() {
        QTcpSocket * socket=m_server->nextPendingConnection();
        RecvFile * recv=new RecvFile(socket);
        recv->start();

        connect(recv,&RecvFile::over,this,[=]()mutable{
            recv->exit();
            recv->wait();
            recv->deleteLater();
            recv=nullptr;
            QMessageBox::information(this,"文件接收","接收完毕！");
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LinkStart_clicked()
{
    unsigned short port =ui->port->text().toUShort();
    m_server->listen(QHostAddress::Any,port);
}

