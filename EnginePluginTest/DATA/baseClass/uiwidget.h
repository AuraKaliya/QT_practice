#ifndef UIWIDGET_H
#define UIWIDGET_H

#include <QWidget>

/*
    引擎的页面的抽象基类，提供构建页面的基础处理方法。

--  Init
--  NowDemo
--  NowUIState
*/

#include <DATA/baseClass/gamedemo.h>

enum UIState{
    Editor=1,
    Player=2
};
class UIWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(GameDemo *nowDemo READ nowDemo WRITE setNowDemo NOTIFY nowDemoChanged)
    Q_PROPERTY(UIState nowUIState READ nowUIState WRITE setNowUIState NOTIFY nowUIStateChanged)
public:



    explicit UIWidget(QWidget *parent = nullptr);
    virtual void init();
    virtual void demoInit();
    virtual void setUIStyle();
    GameDemo *nowDemo() const;
    void setNowDemo(GameDemo *newNowDemo);

    UIState nowUIState() const;
    void setNowUIState(UIState newNowUIState);

private:
    GameDemo* m_nowDemo=nullptr;
    UIState m_nowUIState=Editor;

signals:
    void nowDemoChanged();
    void nowUIStateChanged();
    void actionSend(QString);
    void instructionSend(QString);
    void eventSend(QString);
};

#endif // UIWIDGET_H
