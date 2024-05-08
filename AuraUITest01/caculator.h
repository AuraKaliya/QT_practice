#ifndef CACULATOR_H
#define CACULATOR_H

#include <QObject>
#include <QDebug>
#include <QTime>

class Caculator : public QObject
{
    Q_OBJECT
public:
    explicit Caculator(int initNumber,int  sumNumber,QObject *parent = nullptr);

    int nowNumber() const;
    int sumNumber() const;



    void start();
    void stop();

    bool flag() const;
    void setFlag(bool newFlag);

private:
    int m_nowNumber;
    int m_sumNumber;
    bool m_flag;
signals:
    void nowNumberChanged(int);
};

#endif // CACULATOR_H
