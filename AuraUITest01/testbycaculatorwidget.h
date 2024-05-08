#ifndef TESTBYCACULATORWIDGET_H
#define TESTBYCACULATORWIDGET_H

#include <QWidget>
#include "testwidget.h"
#include "caculator.h"

class TestByCaculatorWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit TestByCaculatorWidget(int initNumber,int  sumNumber,QWidget *parent = nullptr);
    Caculator *caculator() const;

public slots:
    void start()override;
    void stop()override;
private:
    Caculator* m_caculator;
signals:
    void startWork();
    void stopWork();
};

#endif // TESTBYCACULATORWIDGET_H
