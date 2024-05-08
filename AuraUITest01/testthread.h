#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTime>

class TestThread : public QThread
{
    Q_OBJECT
public:
    explicit TestThread(int initNumber, int sumNumber,QObject *parent = nullptr);

    int nowNumber() const;
    int sumNumber() const;

    bool flag() const;
    void setFlag(bool newFlag);

protected:
    void run() override;

private:
    int m_nowNumber;
    int m_sumNumber;
    bool m_flag;
signals:
    void nowNumberChanged(int);
};

#endif // TESTTHREAD_H
