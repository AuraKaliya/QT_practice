#ifndef CHARTTOOLWIDGET_H
#define CHARTTOOLWIDGET_H

#include <QWidget>
#include <QVector>
#include <QMap>
#include <QPushButton>

#include "ChartState.h"
#include "toolbtn.h"

class ChartToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChartToolWidget(QWidget *parent = nullptr);
    void init();
    void reJustSize();
private:
    QVector<ToolBtn*> m_btnList;


    //布局====
    int m_horizontalHint;
    int m_verticalHint;
    int m_lines;

    int m_rowSpace;
    int m_colSpace;





signals:
    void stateChanged(State s);
};

#endif // CHARTTOOLWIDGET_H
