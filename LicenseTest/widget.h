#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>

#include "openssltest.h"
#include "openssllicensetest.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(int argc,char** argv,QWidget *parent = nullptr);
    ~Widget();
protected :
    void keyPressEvent(QKeyEvent* e)override;
private:
    Ui::Widget *ui;
    int m_argc;
    char** m_argv;
};
#endif // WIDGET_H
