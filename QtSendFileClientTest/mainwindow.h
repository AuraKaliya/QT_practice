#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "sendfile.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#pragma execution_character_set("utf-8")
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void startConnect(unsigned short  port,QString ip);
    void startSend(QString path);
private slots:
    void on_Link_clicked();

    void on_SelectFile_clicked();

    void on_sendBtn_clicked();

private:
    Ui::MainWindow *ui;
    QThread * thread;
    SendFile * worker;
};
#endif // MAINWINDOW_H
