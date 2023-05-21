#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSize>
#include <Qt>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QTimer>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>
#include <QBitmap>
#include <QPainter>
#include <QRectF>
#include <QGraphicsView>


class TestWidget : public QWidget {
public:
    TestWidget(QWidget* parent = nullptr);   // 构造函数

    bool checkedShow();     // 判断是否需要显示标签
    bool checkedHide();     // 判断是否需要隐藏标签
protected:
//    void enterEvent(QEvent* event) override;        // 重写鼠标进入窗口的事件处理方法
//    void leaveEvent(QEvent* event) override;        // 重写鼠标离开窗口的事件处理方法

    bool eventFilter(QObject *watched, QEvent *event) override;    // 重写事件过滤器方法
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel* label;          // 标签控件指针
    bool m_trackingMouse = false;       // 标记鼠标是否在窗口内，用于鼠标追踪
    QTimer* m_timer;        // 用于标签在隐藏状态下的计时器
    QTimer* m_timer2;       // 用于标签在显示状态下的计时器
    QLabel *m_labelRound;
    QPushButton * m_btn;      //直角梯形的按钮


    void hideLabelAnimated();       // 隐藏标签并使用动画效果
    void showLabelAnimated();       // 显示标签并使用动画效果
};

#endif // TESTWIDGET_H
