#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

#include "Entity.hpp"

/*
            base

*/


class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickLabel(QWidget *parent = nullptr);
    explicit ClickLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void mouseReleaseEvent(QMouseEvent* e)override;

    Entity& entity();

    void setDrawFunction(const std::function<void (QPainter *, ClickLabel *)> & newDrawFunction);
    bool isDrawFunctionEmpty();
protected:
    void paintEvent(QPaintEvent*e)override;
private:
    void preInit();
protected:
    Entity m_entity;

private:
    std::function<void(QPainter*,ClickLabel*)> m_drawFunction;
    bool drawFunctionFlag;

signals:
    void clickedMe(ClickLabel*);
    void clicked();
};

#endif // CLICKLABEL_H
