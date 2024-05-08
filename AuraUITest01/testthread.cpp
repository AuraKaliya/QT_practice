#include "testthread.h"


TestThread::TestThread(int initNumber, int sumNumber, QObject *parent)
    : QThread{parent},m_nowNumber(initNumber),m_sumNumber(sumNumber),m_flag(false)
{

}

int TestThread::nowNumber() const
{
    return m_nowNumber;
}

int TestThread::sumNumber() const
{
    return m_sumNumber;
}

void TestThread::run()
{
    qDebug()<<"TestThread::run | now Thread : "<<QThread::currentThread();
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

bool TestThread::flag() const
{
    return m_flag;
}

void TestThread::setFlag(bool newFlag)
{
    m_flag = newFlag;
}
