#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->IP->setText("127.0.0.1");
    ui->Port->setText("9999");
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);

    thread=new QThread;
    worker=new SendFile;
    worker->moveToThread(thread);


    connect(this,&MainWindow::startConnect,worker,&SendFile::connectServer);
    connect(worker,&SendFile::linked,this,[=](){
        QMessageBox::information(this,"连接服务器","已经成功连接！");

    });
    connect(worker,&SendFile::disLinked,this,[=](){
        thread->quit();
        thread->wait();
        worker->deleteLater();
        thread->deleteLater();
        worker=nullptr;
        thread=nullptr;
    });

    connect(this,&MainWindow::startSend,worker,&SendFile::sendFile);
    connect(worker,&SendFile::curPercent,ui->progressBar,&QProgressBar::setValue);
    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Link_clicked()
{
    QString ip=ui->IP->text();
    unsigned short port =ui ->Port->text().toUShort();
    emit startConnect(port,ip);
}


void MainWindow::on_SelectFile_clicked()
{
    QString path=QFileDialog::getOpenFileName();
    if(path.isEmpty())
    {
        QMessageBox::warning(this,"打开文件","选择文件路径不能为空");
        return;
    }
    ui->filePath->setText(path);
}


void MainWindow::on_sendBtn_clicked()
{
    emit startSend(ui->filePath->text());


}

