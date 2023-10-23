#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    ui->openGLWidget->draw(MyOpenGLWidget::Rect);
}


void MainWindow::on_action2_triggered()
{
    ui->openGLWidget->draw(MyOpenGLWidget::None);
}

