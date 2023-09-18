#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPluginLoader>

#include "uimainwidget.h"
#include "cardmanager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public UIMainWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initWidget()override final;
    void resolveStr(QString str)override final;


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    CardManager* m_cardManager;
    QPluginLoader m_loader;
};
#endif // WIDGET_H
