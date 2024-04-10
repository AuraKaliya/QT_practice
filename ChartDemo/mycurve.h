#ifndef MYCURVE_H
#define MYCURVE_H

#include <QObject>
#include <QtCharts>
#include <QLineSeries>

class MyCurve : public QLineSeries
{
    Q_OBJECT
public:
    explicit MyCurve(QObject *parent = nullptr);
    void init();
signals:
    void mousehovered(const QPointF& point,bool state);
};

#endif // MYCURVE_H
