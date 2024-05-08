#include "testbyqtimerwidget.h"

TestByQTimerWidget::TestByQTimerWidget(int initNumber, int sumNumber, QWidget *parent)
    : TestWidget{initNumber,sumNumber,parent}
{
    m_timer=new QTimer;

    connect(m_timer,&QTimer::timeout,this,[this](){
        m_nowNumber++;
        m_showNowLabel->setText(QString::number(m_nowNumber));
        if(m_nowNumber>m_sumNumber)
        {
            m_timer->stop();
        }
    });

}

void TestByQTimerWidget::start()
{
    qDebug()<<"TestByQTimerWidget::start.";
    m_timer->setInterval(30);
    m_timer->start();
}

void TestByQTimerWidget::stop()
{
    qDebug()<<"TestByQTimerWidget::stop.";
    m_timer->stop();
}
