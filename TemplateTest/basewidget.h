#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

class BaseWidget : public QWidget
{
    Q_OBJECT
public:

    explicit BaseWidget(QWidget *parent = nullptr);
    virtual void debug()=0;

protected:

signals:

};

// INITFACTORY( BaseWidget)
#endif // BASEWIDGET_H
