#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <QWidget>
#include "manager.h"
#include <QMap>
class UIWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UIWidget(QWidget *parent = nullptr);
    virtual void initWidget(){};
    virtual UIWidget* getWidget();
    virtual void addWidget(UIWidget*w);
    QMap<QString,Manager*> getManager();
    void addManager(QString s,Manager*m);
protected:
    QMap<QString,Manager*> m_managerDictionaryByName;
signals:

};

#endif // UIWIDGET_H
