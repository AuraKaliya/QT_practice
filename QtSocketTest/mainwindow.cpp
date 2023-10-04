#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostAddress>


#pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->port->setText("9999");
    ui->IP->setText("127.0.0.1");
    setWindowTitle("客户端");

    m_socket=new QTcpSocket(this);
    m_status=new QLabel;


    connect(m_socket,&QTcpSocket::readyRead,this,[=](){
        QByteArray data=m_socket->readAll();
        ui->recalled->append("【服务器】"+data);
    });

    connect(m_socket,&QTcpSocket::disconnected,this,[=](){
        m_status->setPixmap(QPixmap(":/f1.png").scaled(QSize(20,20)));
        ui->LinkBtn->setDisabled(false);
        ui->disLinkBtn->setDisabled(true);
        ui->recalled->append("已断开连接...");
    });

    connect(m_socket,&QTcpSocket::connected,this,[=](){
        m_status->setPixmap(QPixmap(":/f2.png").scaled(QSize(20,20)));
        ui->LinkBtn->setDisabled(true);
        ui->disLinkBtn->setDisabled(false);
        ui->recalled->append("已成功连接...");
    });



    //状态栏添加
    m_status->setPixmap(QPixmap(":/f1.png").scaled(QSize(20,20)));
    ui->statusbar->addWidget(new QLabel("连接状态："));
    ui->statusbar->addWidget(m_status);


    //默认断连状态
    ui->disLinkBtn->setDisabled(true);
    ui->LinkBtn->setDisabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_sendMessage_clicked()
{
    QString msg=ui->sendInfo->toPlainText();
    m_socket->write(msg.toUtf8());
    ui->recalled->append("【我】："+msg);
}


void MainWindow::on_LinkBtn_clicked()
{
    QString ip=ui->IP->text();
    unsigned short port=ui->port->text().toUShort();
    m_socket->connectToHost(QHostAddress(ip),port);
}


void MainWindow::on_disLinkBtn_clicked()
{
    m_socket->disconnectFromHost();

}

