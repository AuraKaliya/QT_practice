#include "toolbtn.h"

ToolBtn::ToolBtn(QWidget *parent)
    : QPushButton{parent}
{

}

ToolBtn::ToolBtn(QString str, QWidget *parent):QPushButton{str,parent}
{

}

void ToolBtn::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
}

void ToolBtn::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
    emit clickedMe(this);
}
