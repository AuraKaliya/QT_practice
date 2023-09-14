#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QRandomGenerator>
#include <QtMath>
//生成随机数
class GenerateThread : public QThread
{
    Q_OBJECT
public:
    explicit GenerateThread(QObject *parent = nullptr);
public slots:
    void receiveNumber(const unsigned int & num);
protected:
    void run()override;
signals:
    void sendArray(QVector<int> array);
private:
    unsigned int m_num;
};

class BubSortThread : public QThread
{
    Q_OBJECT
public:
    explicit BubSortThread(QObject *parent = nullptr);

public slots:
    void receiveArray(QVector<int> list);
protected:
    void run()override;
signals:
    void sendArray(QVector<int> array);
private:
    QVector<int> m_array;
};

class QuickSortThread : public QThread
{
    Q_OBJECT
public:
    explicit QuickSortThread(QObject *parent = nullptr);
public slots:
    void receiveArray(const QVector<int> &list);
protected:
    void run()override;
signals:
    void sendArray(QVector<int> array);
private:
    QVector<int> m_array;
};
#endif // MYTHREAD_H
