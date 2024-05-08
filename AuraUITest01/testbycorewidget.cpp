#include "testbycorewidget.h"
#include "qcoreapplication.h"



TestByCoreWidget::TestByCoreWidget(int initNumber, int sumNumber, QWidget *parent)
: TestWidget{initNumber,sumNumber,parent}
{
    m_flag=false;
}

void TestByCoreWidget::start()
{
    m_flag=true;
    qDebug()<<"TestByCoreWidget::start.";
    while(m_nowNumber<m_sumNumber)
    {
        QCoreApplication::processEvents();
        if(!m_flag) break;
        m_nowNumber++;
        m_showNowLabel->setText(QString::number(m_nowNumber));
        QTime time=QTime::currentTime().addMSecs(30);
        while(QTime::currentTime()<time)
        {
            ;
        }
    }
}

void TestByCoreWidget::stop()
{
qDebug()<<"TestByCoreWidget::stop.";
    m_flag=false;
}
