#include "mythread.h"
#include <QElapsedTimer>
#include <QDebug>
GenerateThread::GenerateThread(QObject *parent)
    : QThread{parent}
{

}

void GenerateThread::receiveNumber(const unsigned int & num)
{
    m_num = num;
}

void GenerateThread::run()
{
    qDebug()<<"生成随机数的线程的地址"<<QThread::currentThread();
    QVector <int> list;
    QElapsedTimer time;
    /*
        QElapsedTimer是Qt中提供的一个类，它可以用来计算一段时间的流逝，也就是两个事件或操作之间的时间差。
        它尽可能地使用单调时钟，也就是不受系统时间的影响，更加准确和稳定。
        它可以处理时钟溢出的情况，保证时间的一致性。
        它可以在不同的进程间进行交换，只要它们使用相同的时钟类型。
    */



    time.start();
    for(int i=0;i<m_num;++i)
    {
        list.push_back(QRandomGenerator::global()->bounded(0,100000));
    }
    int milserc =time.elapsed();
    qDebug()<<QThread::currentThread()<<"生成"<<m_num<<"个随机数所用时间："<<milserc<<"毫秒。";
    emit sendArray(list);
}

BubSortThread::BubSortThread(QObject *parent) : QThread{parent}
{

}

void BubSortThread::receiveArray(QVector<int> list)
{
    m_array=list;
}

void BubSortThread::run()
{
    qDebug()<<"冒泡排序的线程的地址"<<QThread::currentThread();
    QElapsedTimer time;
    int temp;
    time.start();
    for(int i=0;i<m_array.size();++i)
    {
        for(int j=0;j<m_array.size()-i-1;++j)
        {
            if(m_array[j]>m_array[j+1])
            {
                temp=m_array[j];
                m_array[j]=m_array[j+1];
                m_array[j+1]=temp;
            }
        }
    }
    int milserc =time.elapsed();
    qDebug()<<QThread::currentThread()<<"冒泡排序所用时间："<<milserc<<"毫秒。";
    emit sendArray(m_array);
}

QuickSortThread::QuickSortThread(QObject *parent) : QThread{parent}
{

}

void QuickSortThread::receiveArray(const QVector<int> &list)
{
    m_array=list;
}

void QuickSortThread::run()
{
    qDebug()<<"快速排序的线程的地址"<<QThread::currentThread();
    QElapsedTimer time;
    time.start();
    std::sort(m_array.begin(),m_array.end());
    int milserc =time.elapsed();
    qDebug()<<QThread::currentThread()<<"快速排序所用时间："<<milserc<<"毫秒。";
    emit sendArray(m_array);
}
