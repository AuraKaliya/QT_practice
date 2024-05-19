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

protected:
    Entity m_entity;
signals:
    void clickedMe(ClickLabel*);
    void clicked();
};

#endif // CLICKLABEL_H
