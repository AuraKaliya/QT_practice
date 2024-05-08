#include "caculator.h"



Caculator::Caculator(int initNumber, int sumNumber, QObject *parent)
    : QObject{parent}
{
    m_nowNumber=initNumber;
    m_sumNumber=sumNumber;
    m_flag=false;
}

int Caculator::nowNumber() const
{
    return m_nowNumber;
}

int Caculator::sumNumber() const
{
    return m_sumNumber;
}

void Caculator::start()
{
    qDebug()<<"Caculator::start.";
    m_flag=true;
    while(m_nowNumber<m_sumNumber)
    {
        if(!m_flag) break;
        m_nowNumber++;
        emit nowNumberChanged(m_nowNumber);
        QTime time=QTime::currentTime().addMSecs(30);
        while(QTime::currentTime()<time)
        {
            ;
        }
    }
}

void Caculator::stop()
{
    qDebug()<<"Caculator::stop.";
    m_flag=false;
}

bool Caculator::flag() const
{
    return m_flag;
}

void Caculator::setFlag(bool newFlag)
{
    m_flag = newFlag;
}
