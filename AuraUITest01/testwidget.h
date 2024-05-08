#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include <QTimer>

#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>

class TestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestWidget(int initNumber,int  sumNumber,QWidget *parent = nullptr);
    void initWidget();



public slots:
    virtual void start();
    virtual void stop();

protected:
    void resizeEvent(QResizeEvent* e)override;
protected:
    QPushButton * m_satrtBtn     =nullptr;
    QPushButton * m_stopBtn =nullptr;
    QLabel * m_showNowLabel =nullptr;
    QLabel * m_showSumLabel =nullptr;

    int m_sumNumber;
    int m_nowNumber;

    bool m_breakFlag;
signals:

};

#endif // TESTWIDGET_H
