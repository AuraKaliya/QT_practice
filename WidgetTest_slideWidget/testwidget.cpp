#include "testwidget.h"

TestWidget::TestWidget(QWidget* parent) : QWidget(parent)
{
    // 设置默认大小和最小宽度
    //setFixedSize(QSize(900,600));
    resize(QSize(900,600));
    setMinimumWidth(120);

    // 创建标签组件并设置初始属性
    label = new QLabel(this);
    label->setGeometry(-width() / 5, 0, width() / 5, height()); // 标签的初始位置
    label->setAlignment(Qt::AlignCenter);
    label->setText("Hello World!");

    // 设置标签的背景颜色和前景色（即字体颜色）
    QPalette palette = label->palette();
    palette.setColor(label->backgroundRole(), Qt::red);    // 设置背景颜色为红色
    palette.setColor(label->foregroundRole(), Qt::white);  // 设置字体颜色为白色
    label->setAutoFillBackground(true);   // 启用自动填充标签的背景色
    label->setPalette(palette);

    // 隐藏标签
    label->setVisible(false);

    // 将鼠标追踪功能绑定到窗体的focus事件上
    this->installEventFilter(this);

    // 创建定时器并连接信号槽
    m_timer = new QTimer(this);
    m_timer2 = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [=]() {
        if (checkedShow()) {
            showLabelAnimated();
        }
    });
    connect(m_timer2, &QTimer::timeout, this, [=]() {
        if (checkedHide()) {
            hideLabelAnimated();
        }
    });

    m_timer->start(100);




    update();

}

bool TestWidget::checkedShow() {
    // 当鼠标位置在窗体左半边百分之十，且label为隐藏状态时返回true
    QPoint cursorPos = mapFromGlobal(QCursor::pos());
    return ((cursorPos.x() < (this->width() / 10)) && (!label->isVisible())&&(cursorPos.x()>0));
}

bool TestWidget::checkedHide() {
    // 当鼠标位置不在label区域、且label为显示状态时返回true
    QPoint labelPos = label->mapFromGlobal(QCursor::pos());
    return (!label->rect().contains(labelPos) && label->isVisible());
}




bool TestWidget::eventFilter(QObject *obj, QEvent *event) {
    if (obj == this && event->type() == QEvent::FocusIn) {
        // 窗体获取焦点时，启用鼠标追踪功能
        setMouseTracking(true);
    }
    return QWidget::eventFilter(obj, event);
}

void TestWidget::paintEvent(QPaintEvent *event)
{
}
void TestWidget::hideLabelAnimated()
{
    m_timer2->stop();   // 停止计时器
    QPropertyAnimation* animation = new QPropertyAnimation(label, "geometry");   // 创建属性动画对象
    animation->setDuration(500);    // 设置动画持续时间，单位为毫秒
    animation->setStartValue(label->geometry());   // 设置动画开始位置
    QRect endRect = label->geometry();
    endRect.moveLeft(-label->width());
    animation->setEndValue(endRect);    // 设置动画结束位置
    QObject::connect(animation, &QPropertyAnimation::finished, [this]() {
        label->hide();  // 动画完成后隐藏标签
        m_timer->start(100);    // 再次启动计时器
    });
    animation->start(QAbstractAnimation::DeleteWhenStopped);  // 启动动画
}

void TestWidget::showLabelAnimated()
{
    // 停止计时器
    m_timer->stop();
    // 将标签设置为可见
    label->setGeometry(-width() / 5, 0, width() / 5, height());
    label->setVisible(true);

    // 创建一个目标位置对象
    QPoint targetPos = QPoint(0,0);

    // 创建属性动画对象，将标签的位置作为属性
    QPropertyAnimation *animation = new QPropertyAnimation(label, "pos");
    // 当动画完成时，重新启动计时器
    QObject::connect(animation, &QPropertyAnimation::finished, [this]() {
        m_timer2->start(100);
    });
    // 设置动画持续时间，单位为毫秒
    animation->setDuration(500);

    // 设置动画开始位置
    animation->setStartValue(label->pos());

    // 设置动画结束位置
    animation->setEndValue(targetPos);

    // 启动动画
    animation->start();
}
