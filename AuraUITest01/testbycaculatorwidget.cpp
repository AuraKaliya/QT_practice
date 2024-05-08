#include "testbycaculatorwidget.h"


TestByCaculatorWidget::TestByCaculatorWidget(int initNumber, int sumNumber, QWidget *parent)
: TestWidget{initNumber,sumNumber,parent}
{
    m_caculator=new Caculator(initNumber,sumNumber);
    connect(m_caculator,&Caculator::nowNumberChanged,this,[this](int number){
    m_showNowLabel->setText(QString::number(number));
    },Qt::QueuedConnection);

    connect(this,&TestByCaculatorWidget::startWork,m_caculator,&Caculator::start,Qt::QueuedConnection);
    connect(this,&TestByCaculatorWidget::stopWork,m_caculator,&Caculator::stop,Qt::DirectConnection);
}

void TestByCaculatorWidget::start()
{
    qDebug()<<"TestByCaculatorWidget::start .";
    emit startWork();
}

void TestByCaculatorWidget::stop()
{
    qDebug()<<"TestByCaculatorWidget::stop .";
    emit stopWork();
}

Caculator *TestByCaculatorWidget::caculator() const
{
    return m_caculator;
}
