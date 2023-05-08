#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QList>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>
#include <QMap>
#include <QDebug>
#include <QtGui>
#include <QSystemTrayIcon>

#include "hook.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


    void loadMedia();



  void keyPressEvent(QKeyEvent *);
  void keyReleaseEvent(QKeyEvent*);
  void  mousePressEvent(QMouseEvent *);

  void closeEvent(QCloseEvent*);
private:
    Ui::Widget *ui;

    QList<QMediaPlayer*> soundList;
    QList<QString> KeyName;
    QString nowSoundName;
    QMap<QString,QMediaPlayer*> soundMap;

    Hook hook;

    QSystemTrayIcon * trayIcon;
 private slots:
    void icon_active(QSystemTrayIcon::ActivationReason reason);
    void shows();
    void checkType(Hook::Type);
    void on_pushButton_clicked();
};
#endif // WIDGET_H
