#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_machine =new QStateMachine(this);
    m_state1=new QState(QState::ParallelStates);
    m_state2=new QFinalState();

    m_state11=new QState(m_state1);

    m_state111=new QState(m_state11);
    m_state112=new QState(m_state11);

    m_state12=new QState(m_state1);

    m_state121=new QState(m_state12);
    m_state122=new QState(m_state12);




    m_people=new People();
    qDebug()<<"Now People's age:"<<m_people->getAge();



    m_state111->assignProperty(m_people,"age",20);
    m_state112->assignProperty(m_people,"age",70);

    m_state11->setInitialState(m_state111);
    //m_state11->assignProperty(m_people,"ageState",People::Teens);


    m_state121->assignProperty(m_people,"sex","男");
    m_state122->assignProperty(m_people,"sex","女");
    m_state12->setInitialState(m_state121);


    m_state1->addTransition(ui->pushButton,SIGNAL(clicked()),m_state2);
    m_state111->addTransition(ui->pushButton_2,SIGNAL(clicked()),m_state112);
    m_state112->addTransition(ui->pushButton_2,SIGNAL(clicked()),m_state111);
    m_state121->addTransition(ui->pushButton_3,SIGNAL(clicked()),m_state122);
    m_state122->addTransition(ui->pushButton_3,SIGNAL(clicked()),m_state121);




    m_machine->addState(m_state1);
    m_machine->addState(m_state2);
    m_machine->setInitialState(m_state1);

    m_machine->start();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    qDebug()<<"end!";
}


void Widget::on_pushButton_2_clicked()
{
    qDebug()<<"People's age:"<<m_people->getAge();
}


void Widget::on_pushButton_3_clicked()
{
    qDebug()<<"People's sex:"<<m_people->getSex();
}

