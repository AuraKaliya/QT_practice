#include "charttoolwidget.h"

ChartToolWidget::ChartToolWidget(QWidget *parent)
    : QWidget{parent}
{
    m_horizontalHint=10;
    m_verticalHint=5;
    m_rowSpace=5;
    m_colSpace=5;


    m_lines=1;
}

void ChartToolWidget::init()
{

    for(auto it=ChartState::s_chartStateList.begin();it!=ChartState::s_chartStateList.end();++it)
    {
        ToolBtn* btn=new ToolBtn(*it,this);
        btn->setVisible(true);
        btn->adjustSize();
        connect(btn,&ToolBtn::clickedMe,this,[this](ToolBtn*b){
            emit stateChanged(ChartState::s_chartStateDictionary.find(b->text()).value());
        });
        m_btnList.append(btn);
    }

    //布局
    reJustSize();
}

void ChartToolWidget::reJustSize()
{

    int perLineCount=m_btnList.size()/m_lines;
    if(m_btnList.size()%m_lines!=0) perLineCount+=1;

    for(int i=0;i<m_btnList.size();++i)
    {
        m_btnList[i]->move(
                 m_horizontalHint+(i%perLineCount)*(m_btnList[i]->width()+m_colSpace),
                 m_verticalHint+(i/perLineCount)*(m_btnList[i]->height()+m_rowSpace)
                 );
    }
    if(m_btnList.size()>1)
    resize(
           2*m_horizontalHint +perLineCount*(m_btnList[0]->width()+m_colSpace)  ,
           2*m_verticalHint+m_lines*(m_btnList[0]->height()+m_rowSpace)
           );
}
