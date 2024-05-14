#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "View/blueprintsview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent*e)override;
private:
    Ui::MainWindow *ui;

    BlueprintsView * m_view =nullptr;
};
#endif // MAINWINDOW_H
