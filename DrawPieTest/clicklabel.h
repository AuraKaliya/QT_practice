#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickLabel(QWidget *parent = nullptr);
    explicit ClickLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void mousePressEvent(QMouseEvent* e)override;
    void mouseReleaseEvent(QMouseEvent* e)override;
    void paintEvent(QPaintEvent* e)override;
signals:
    void clickedMe(ClickLabel*);
    void clicked();
};

#endif // CLICKLABEL_H
