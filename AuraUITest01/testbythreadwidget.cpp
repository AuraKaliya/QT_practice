#include "testbythreadwidget.h"

TestByThreadWidget::TestByThreadWidget(int initNumber, int sumNumber, QWidget *parent)
    : TestWidget{initNumber,sumNumber,parent}
{
    m_thread=new TestThread(initNumber,sumNumber,this);

    connect(m_thread,&TestThread::nowNumberChanged,this,[this](int number){
            m_showNowLabel->setText(QString::number(m_thread->nowNumber()));
    },Qt::QueuedConnection);
}

void TestByThreadWidget::start()
{
    qDebug()<<"TestByThreadWidget::start.";
    qDebug()<<"TestByThreadWidget::start | now Thread : "<<QThread::currentThread();
    m_thread->setFlag(true);
    m_thread->start();
}

void TestByThreadWidget::stop()
{
    qDebug()<<"TestByThreadWidget::stop.";
    m_thread->setFlag(false);
}

