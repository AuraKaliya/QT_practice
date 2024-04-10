#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setFixedSize(800,600);

    //m_toolWidget=new ChartToolWidget(this);
    //m_toolWidget->init();
    //m_toolWidget->move(0,0);


    m_chart=new MyChart(this);
    m_chart->init();
    m_chart->move(0,0);
    //m_chart->setGeometry(0,m_toolWidget->height()+5,400,300);



    //connect(m_toolWidget,&ChartToolWidget::stateChanged,m_chart,&MyChart::stateChange);
}

Widget::~Widget()
{
    delete ui;
}

