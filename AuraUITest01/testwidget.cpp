#include "testwidget.h"

#include <QTime>

TestWidget::TestWidget(int initNumber, int sumNumber, QWidget *parent)
    : QWidget{parent},m_sumNumber(sumNumber),m_nowNumber(initNumber)
{
    m_showNowLabel=new QLabel (QString::number(m_nowNumber),this);
    m_showSumLabel=new QLabel (QString::number(m_sumNumber),this);
    m_satrtBtn =new QPushButton("Start",this);
    m_stopBtn  =new QPushButton("Stop",this);

    m_breakFlag=false;
}

void TestWidget::initWidget()
{
    connect(m_satrtBtn,SIGNAL(clicked()),this,SLOT(start()));
    connect(m_stopBtn,SIGNAL(clicked()),this,SLOT(stop()));
}

void TestWidget::start()
{
    qDebug()<<"TestWidget::start.";
    m_breakFlag=true;
    while(m_nowNumber<m_sumNumber)
    {
        if(!m_breakFlag) break;
        m_nowNumber++;
        m_showNowLabel->setText(QString::number(m_nowNumber));
        QTime time=QTime::currentTime().addMSecs(30);
        while(QTime::currentTime()<time)
        {
            ;
        }
    }

}

void TestWidget::stop()
{
    qDebug()<<"TestWidget::stop.";
    m_breakFlag=false;
}

void TestWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    m_showNowLabel->setGeometry(0,0,width(),height()/4);
    m_showSumLabel->setGeometry(0,height()/4,width(),height()/4);
    m_satrtBtn->setGeometry(0,height()/2,width(),height()/4);
    m_stopBtn->setGeometry(0,height()*3/4,width(),height()/4);
}
