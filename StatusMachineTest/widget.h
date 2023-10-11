#ifndef WIDGET_H
#define WIDGET_H

#include <QFinalState>
#include <QWidget>

#include <QState>
#include <QStateMachine>
#include "people.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    QStateMachine * m_machine=nullptr;
    QState * m_state1=nullptr;
    QFinalState * m_state2=nullptr;
    QState * m_state11=nullptr;
    QState * m_state111=nullptr;
    QState * m_state112=nullptr;
    QState * m_state12=nullptr;
    QState * m_state121=nullptr;
    QState * m_state122=nullptr;


    People * m_people=nullptr;

};
#endif // WIDGET_H
