#ifndef SLIDEBLOCK_H
#define SLIDEBLOCK_H

#include <QPushButton>
#include <QObject>
#include <QRect>
#include <QMouseEvent>


class slideBlock : public QPushButton
{
    Q_OBJECT
public:
    slideBlock();
    void setRect(QRect rect);
    void mousePressEvent(QMouseEvent * e)override;
    void mouseMoveEvent(QMouseEvent *e)override;
    void mouseReleaseEvent(QMouseEvent * e) override;
    void initPos();
    void resetPos();
    void setMouseStartPos(QPoint newMouseStartPos);

    void setFixPos(QPoint newFixPos);

signals:
    void valueMax();
private:
    QRect m_abRect;
    QPoint m_mouseStartPos;
    QPoint fixPos;
    QPoint m_btnStarPos;
    bool m_isPressed;

};

#endif // SLIDEBLOCK_H
