#include "mychart.h"

#include <QPen>
#include <QPixmap>

MyChart::MyChart(QWidget *parent)
    : QChartView{parent}
{
    m_chart=new QChart();
    m_curve=new MyCurve();
    m_toolWidget=new ChartToolWidget(this);
    m_toolWidget->hide();




    //connect=================
    connect(m_curve,&QLineSeries::hovered,this,[this](const QPointF& point,bool state)
    {
        // qDebug()<<"hovered! point:"<<point<< state;
    }
    );
    connect(m_toolWidget,&ChartToolWidget::stateChanged,this,&MyChart::stateChange);
    //connect=================


    setChart(m_chart);
    setRenderHint(QPainter::Antialiasing);
    resize(400, 300);

}

void MyChart::stateChange(State state)
{

    if(state& Move)
    {
        //移动
        m_Q_flag=!m_Q_flag;
    }

    if(state& Select)
    {
        //选取
        m_W_flag=!m_W_flag;
    }

    if(state& Save)
    {
        //保存

        saveToImage();
    }



}

void MyChart::setState(State state)
{
    resetState();
    if(state==None) return;

    if(state& Move)
    {
        //移动
        m_Q_flag=true;
    }

    if(state& Select)
    {
        //选取
        m_W_flag==true;
    }

    if(state& Save)
    {
        //保存
        saveToImage();
    }

}

void MyChart::resetState()
{
    m_Q_flag=false;
    m_W_flag=false;
}

void MyChart::sethighlightPointsInRect(const QRectF &selectRect)
{

    for(auto it:m_highlightCurveList)
    {
        m_chart->removeSeries(it);
        delete it;
        it=nullptr;
    }
    m_highlightCurveList.clear();

    bool startFlag=false;
    bool continueFlag=false;
    MyCurve* tmpCurve;

    const QVector<QPointF> points=m_curve->pointsVector();

    for(auto it:points)
    {
        if(selectRect.contains(it))
        {
            if(!startFlag)
            {
                startFlag=true;
                tmpCurve=new MyCurve();
                tmpCurve->setPen(QPen(Qt::red));
            }

            tmpCurve->append(it);

            if(!continueFlag)
            {
                continueFlag=true;
            }
        }
        else
        {
            continueFlag=false;
        }

        if(startFlag && !continueFlag)
        {
            m_chart->addSeries(tmpCurve);
            m_highlightCurveList.append(tmpCurve);
            startFlag=false;
        }
    }
    if(startFlag)
    {
        m_chart->addSeries(tmpCurve);
        m_highlightCurveList.append(tmpCurve);
    }

    m_chart->createDefaultAxes();
}

void MyChart::addHighlightPointsInRect(const QRectF &selectRect)
{
    bool startFlag=false;
    bool continueFlag=false;
    MyCurve* tmpCurve;

    const QVector<QPointF> points=m_curve->pointsVector();

    for(auto it:points)
    {
        if(selectRect.contains(it) )
        {

            //if(m_highlightPointSet.contains(it)) continue;

            //m_highlightPointSet.insert(it);
            if(!startFlag)
            {
                startFlag=true;
                tmpCurve=new MyCurve();
                tmpCurve->setPen(QPen(Qt::red));
            }
            tmpCurve->append(it);

            if(!continueFlag)
            {
                continueFlag=true;
            }
        }
        else
        {
            continueFlag=false;
        }

        if(startFlag && !continueFlag)
        {

            m_chart->addSeries(tmpCurve);
            m_highlightCurveList.append(tmpCurve);
            startFlag=false;
        }
    }
    if(startFlag)
    {
        m_chart->addSeries(tmpCurve);
        m_highlightCurveList.append(tmpCurve);
    }

    m_chart->createDefaultAxes();


}

void MyChart::init()
{
    m_dragFlag=false;
    m_Q_flag=false;
    m_lineHoverFlag=false;
    m_selectFlag=false;
    m_W_flag=false;
    m_Shift_flag=false;

    m_toolWidget->init();
    m_toolWidget->move(width()-m_toolWidget->width(),0);

    m_curve->init();
    m_curve->setPen(QPen(Qt::black));


    m_chart->legend()->hide();
    m_chart->addSeries(m_curve);
    m_chart->createDefaultAxes();
    m_chart->setTitle(QStringLiteral("Qt Line Chart Example"));


    m_chart->layout()->setContentsMargins(0,0,0,0);
    //m_chart->setMargins(QMargins(0,30,0,0));
    m_chart->setBackgroundRoundness(0);


}

void MyChart::saveToImage()
{

toolWidgetHide();
    QPixmap pixmap = grab();
    pixmap.save("chart.png");
toolWidgetShow();

}

void MyChart::mousePressEvent(QMouseEvent *e)
{
    if(m_Q_flag)
    {
        m_dragFlag=true;
    }

    if(m_W_flag)
    {
        //qDebug()<<"SELSECT~ pressed~";
        m_selectFlag=true;
    }


    m_dragStartPos=e->pos();
    m_selectStartPos=e->pos();
    m_chartStartPos=m_chart->mapToValue(e->pos());

    //check=================
    //qDebug()<<"StartPos:"<<m_selectStartPos;
    //qDebug()<<"CharStartPos:"<<m_chartStartPos;
    //check=================

    QChartView::mousePressEvent(e);
}

void MyChart::mouseMoveEvent(QMouseEvent *e)
{

    if(m_dragFlag)
    {
        m_dragEndPos=e->pos();
        auto dx=m_dragEndPos.x()-m_dragStartPos.x();
        auto dy=m_dragEndPos.y()-m_dragStartPos.y();
        m_chart->scroll(-dx,dy);
        m_dragStartPos=e->pos();
    }
    if(m_selectFlag)
    {
        //qDebug()<<"SELSECT~ move~";
        m_selectEndPos=e->pos();
        m_chartEndPos=m_chart->mapToValue(e->pos());
        //drawSelect();
        //qDebug()<<"ePos"<<m_selectEndPos;
        m_selectRect=QRectF(m_selectStartPos,m_selectEndPos);
        m_chartSelectRect=QRectF(m_chartStartPos,m_chartEndPos);
        viewport()->update();
    }





    QChartView::mouseMoveEvent(e);
}

void MyChart::mouseReleaseEvent(QMouseEvent *e)
{

    m_dragFlag=false;
    m_selectFlag=false;
    if(m_Shift_flag)
    {
        addHighlightPointsInRect(m_chartSelectRect);
    }
    else
    {
        sethighlightPointsInRect(m_chartSelectRect);
    }

    //check=================
    //qDebug()<<"m_selectEndPos:"<<m_selectEndPos;
    //check=================

    viewport()->repaint();

    QChartView::mouseReleaseEvent(e);
}

void MyChart::wheelEvent(QWheelEvent *e)
{
    double factor = std::pow(1.1, e->delta() / 240.0);
    m_chart->zoom(factor);
    QChartView::wheelEvent(e);
}

void MyChart::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Q)
    {
        //qDebug()<<" Q is Pressed!";
        m_Q_flag=!m_Q_flag;
    }

    if(e->key()==Qt::Key_W)
    {
        //qDebug()<<" W is Pressed!";
        m_W_flag=!m_W_flag;
    }

    if(e->key()==Qt::Key_Shift)
    {
        m_Shift_flag=true;
    }

    if(e->key()==Qt::Key_P)
    {
        saveToImage();
    }
}

void MyChart::keyReleaseEvent(QKeyEvent *e)
{
    m_Shift_flag=false;
}

void MyChart::paintEvent(QPaintEvent *e)
{
    QChartView::paintEvent(e);

    QPainter p(viewport());
    if(m_selectFlag)
    {
        p.setPen(QPen(Qt::red));
        //p.drawRect(QRectF(m_selectStartPos,m_selectEndPos));
        p.drawRect(m_selectRect);
    }
    p.end();

}

void MyChart::enterEvent(QEvent *e)
{

    toolWidgetShow();

}

void MyChart::leaveEvent(QEvent *e)
{
    toolWidgetHide();
}

void MyChart::toolWidgetHide()
{
    m_toolWidget->hide();

}

void MyChart::toolWidgetShow()
{
    m_toolWidget->show();
}

