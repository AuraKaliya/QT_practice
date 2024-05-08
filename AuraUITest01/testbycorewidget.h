#ifndef TESTBYCOREWIDGET_H
#define TESTBYCOREWIDGET_H

#include <QWidget>
#include "testwidget.h"
#include <QCoreApplication>
#include <QTime>
class TestByCoreWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit TestByCoreWidget(int initNumber,int  sumNumber,QWidget *parent = nullptr);

public slots:
    void start()override;
    void stop()override;
private:
    bool m_flag;
signals:

};

#endif // TESTBYCOREWIDGET_H
