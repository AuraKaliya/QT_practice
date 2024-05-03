#include "clicklabel.h"

ClickLabel::ClickLabel(QWidget *parent)
    : QLabel{parent}
{

}

ClickLabel::ClickLabel(const QString &text, QWidget *parent, Qt::WindowFlags f):QLabel{text,parent,f}
{

}

void ClickLabel::mousePressEvent(QMouseEvent *e)
{

}

void ClickLabel::mouseReleaseEvent(QMouseEvent *e)
{
    emit clicked();
    emit clickedMe(this);
}

void ClickLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);

    int w=width()-2;
    int h=height()-2;

    QPainter painter(this);
    painter.setPen(QPen(Qt::red));
    painter.drawRect(1,1,w,h);

    painter.end();


}



