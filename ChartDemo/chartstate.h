#ifndef CHARTSTATE_H
#define CHARTSTATE_H
#include <QMap>
#include <QString>
#include <QVector>
    //1 2 4 8 ...
enum State{
           None=0,
           Move=1,
           Select=2,
           Save=4
       };

class ChartState
{
public:

static QMap<QString,State> s_chartStateDictionary;
static QVector<QString> s_chartStateList;
    ChartState();
};

#endif // CHARTSTATE_H
