#include "chartstate.h"

QMap<QString,State> ChartState::s_chartStateDictionary{
    {"None",None},
    {"Move",Move},
    {"Select",Select},
    {"Save",Save}
};
QVector<QString> ChartState::s_chartStateList
{
    "Save","Move","Select"
};
ChartState::ChartState()
{

}
