#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <QWidget>

class UIWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UIWidget(QWidget *parent = nullptr);
    virtual ~UIWidget();
    virtual void initWidget();
protected:

    virtual void updateLayout();
    void resizeEvent(QResizeEvent*e)override;
signals:

};

#endif // UIWIDGET_H
