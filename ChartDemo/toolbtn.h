#ifndef TOOLBTN_H
#define TOOLBTN_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
class ToolBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit ToolBtn(QWidget *parent = nullptr);
    explicit ToolBtn(QString str,QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent*e)override;
    void mouseReleaseEvent(QMouseEvent *e)override;
signals:
    void clickedMe(ToolBtn*);
};

#endif // TOOLBTN_H
