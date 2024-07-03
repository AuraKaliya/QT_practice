#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_mainLayout =new QGridLayout();
    setLayout(m_mainLayout);

    m_signalMapper =new QSignalMapper(this);


    //1. 继承式，功能延申
    for(int i=0;i<3;++i)
    {
        CardLabel * label =new CardLabel(i,this);
        label->setText("Inherit:"+QString::number(i));
        connect(label,&CardLabel::clickedCard,this,&Widget::doClicked);
        m_mainLayout->addWidget(label, i / 3, i % 3);
    }

    //2.组件式，功能组合
    for(int i=3;i<6;++i)
    {
        ClickLabel *label =new ClickLabel(this);
        label->setText("Component:"+QString::number(i));

        auto& entity =label->entity();
        entity.addComponent("Id",new Component<Entity>(entity));

        auto component =entity.getComponent("Id");
        if(!component)
        {
            qDebug()<<"Connect:Error no have this component.";
        }

        component->setValue(QVariant(i));

        //check
        //qDebug()<<"Check 1 entity:"<<&entity<<" |component "<<component <<entity.hasComponent("Id");


        connect(label,&ClickLabel::clicked,this,[this,label](){
            auto& entity =label->entity();
            auto component =entity.getComponent("Id");

            //check
            //qDebug()<<"Check 2 entity:"<<&entity<<" |component "<<component <<entity.hasComponent("Id");

            if(!component)
            {
                qDebug()<<"Click:Error no have this component.";
                return;
            }
            doClicked(component->getValue<int>());
        });

        m_mainLayout->addWidget(label, i / 3, i % 3);
    }


    //3.SignalMapper式，link+注册
    connect(m_signalMapper,SIGNAL(mappedInt(int)),this,SLOT(doClicked(int)));
    for(int i=6;i<9;++i)
    {
        ClickLabel *label =new ClickLabel(this);
        label->setText("Link:"+QString::number(i));

        connect(label,SIGNAL(clicked()),m_signalMapper,SLOT(map()));
        m_signalMapper->setMapping(label,i);

        m_mainLayout->addWidget(label, i / 3, i % 3);
    }

}

Widget::~Widget()
{
    delete ui;
}

void Widget::doClicked(int id)
{
    qDebug()<<"Clicked label ,id ="<<id;
}
