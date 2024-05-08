#ifndef TESTBYTHREADWIDGET_H
#define TESTBYTHREADWIDGET_H

#include <QWidget>
#include "testwidget.h"
#include "testthread.h"


class TestByThreadWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit TestByThreadWidget(int initNumber,int  sumNumber,QWidget *parent = nullptr);

public slots:
    void start()override;
    void stop()override;

private:
    TestThread * m_thread;
signals:

};

#endif // TESTBYTHREADWIDGET_H
