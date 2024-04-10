#ifndef MYCHART_H
#define MYCHART_H

#include <QWidget>
#include <QChartView>
#include <QtCharts>
#include "mycurve.h"
#include "ChartState.h"

#include <QWheelEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>

#include "charttoolwidget.h"



class MyChart : public QChartView
{
    Q_OBJECT
public:


public:
    explicit MyChart(QWidget *parent = nullptr);


    void sethighlightPointsInRect(const QRectF & selectRect);
    void addHighlightPointsInRect(const QRectF & selectRect);
    void init();
public slots:
    void stateChange(State state);
    void setState(State state);
    void resetState();
    void saveToImage();

protected:

    void        mousePressEvent(QMouseEvent*e)     override;
    void        mouseMoveEvent(QMouseEvent*e)      override;
    void        mouseReleaseEvent(QMouseEvent*e)   override;
    void        wheelEvent(QWheelEvent *e)         override;
    void        keyPressEvent(QKeyEvent *e)        override;
    void        keyReleaseEvent(QKeyEvent* e)      override;
    void        paintEvent(QPaintEvent* e)         override;
    void        enterEvent(QEvent *e)              override;
    void        leaveEvent(QEvent *e)              override;


private:
    void toolWidgetHide();
    void toolWidgetShow();





    QChart * m_chart=nullptr;
    MyCurve * m_curve=nullptr;
    ChartToolWidget* m_toolWidget=nullptr;


    QVector<MyCurve*> m_highlightCurveList;
    //QSet<QPointF> m_highlightPointSet;


    QPoint m_dragStartPos;
    QPoint m_dragEndPos;

    QPointF m_selectStartPos;
    QPointF m_selectEndPos;
    QRectF  m_selectRect;

    QPointF m_chartStartPos;
    QPointF m_chartEndPos;
    QRectF  m_chartSelectRect;


    bool m_Q_flag;
    bool m_W_flag;
    bool m_Shift_flag;
    bool m_selectFlag;
    bool m_lineHoverFlag;
    bool m_dragFlag;

signals:

};











#endif // MYCHART_H
