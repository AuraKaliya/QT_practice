#ifndef UIMAINWIDGET_H
#define UIMAINWIDGET_H


#include "uiwidget.h"

class UIMainWidget : public UIWidget
{
    Q_OBJECT
public:
    explicit UIMainWidget(QWidget *parent = nullptr);
    virtual void initWidget(){};
    virtual void resolveStr(QString str)=0;
signals:

};

#endif // UIMAINWIDGET_H
