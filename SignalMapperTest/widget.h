#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include <QGridLayout>
#include "cardlabel.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void doClicked(int id);
private:

    Ui::Widget *ui;
    QSignalMapper * m_signalMapper;
    QGridLayout* m_mainLayout;
};
#endif // WIDGET_H
