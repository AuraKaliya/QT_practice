#include "mycurve.h"

MyCurve::MyCurve(QObject *parent)
    : QLineSeries{parent}
{


//    connect(this,&QLineSeries::hovered,this,[this](const QPointF& point,bool state)
//    {
//        emit mousehovered(point,state);
//    }
//            );

}

void MyCurve::init()
{

    append(0, 2);
    append(1, 4);
    append(2, 6);
    append(3, 8);
    append(4, 6);
    append(5, 4);
    append(6, 2);
}
