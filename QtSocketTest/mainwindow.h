#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTcpSocket>
#include <QLabel>
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

    void on_sendMessage_clicked();

    void on_LinkBtn_clicked();

    void on_disLinkBtn_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket* m_socket;

    QLabel * m_status;
};
#endif // MAINWINDOW_H
