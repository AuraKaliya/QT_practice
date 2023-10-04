#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLabel>
#include <QList>

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

private slots:
    void on_listenStart_clicked();

    void on_sendMessage_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer* m_server;
    QTcpSocket* m_nowSocket=nullptr;

    QList <QTcpSocket*> m_socketList;
    QLabel * m_status;

};
#endif // MAINWINDOW_H
