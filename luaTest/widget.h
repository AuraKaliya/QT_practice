#ifndef WIDGET_H
#define WIDGET_H

#include <QTimer>
#include <QWidget>
#include <lua.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    Widget* getThis();
    static int myNumber;
protected:
    void keyPressEvent(QKeyEvent*e)override;
    void keyReleaseEvent(QKeyEvent*e)override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;

    QTimer tickTimer;
    QTimer timer;
    lua_State *pState=nullptr;
    lua_State *L=nullptr;
};
#endif // WIDGET_H
