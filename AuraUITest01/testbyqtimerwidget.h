#ifndef TESTBYQTIMERWIDGET_H
#define TESTBYQTIMERWIDGET_H

#include <QWidget>
#include "testwidget.h"

class TestByQTimerWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit TestByQTimerWidget(int initNumber,int  sumNumber,QWidget *parent = nullptr);
public slots:
    void start()override;
    void stop()override;
private:
    QTimer *m_timer=nullptr;
signals:

};

#endif // TESTBYQTIMERWIDGET_H
