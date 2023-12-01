#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFrame>
#include <QBrush>
#include <QFont>

#include <QGridLayout>
#include <math.h>
#include <QGroupBox>

#include <QDebug>

#include "graphicsitem.h"
#include "item2dmap.h"
#include "dynamicitem.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void CreateControlFrame();

protected:
    void paintEvent(QPaintEvent* e)override;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    int iTemp;
    qreal scaleValues;
    qreal shearValues;

    QGraphicsView *view;
    QFrame *controlFrame;
    GraphicsItem * it;
    GraphicsItem * it2;
    GraphicsItem * it3;
    Item2DMap* it4;
    DynamicItem * it5;

    QVector<QPixmap> pixList;
    Ui::MainWindow *ui;
    QTimer* timer;
};
#endif // MAINWINDOW_H
