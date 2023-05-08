#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);



    this->releaseKeyboard();

    nowSoundName=QString("HT");

    KeyName<<QString("right")<<QString("shift")
          <<QString("space")<<QString("4")
         <<QString("tab")<<QString("3")<<QString("F");
    loadMedia();

    hook.installHook(&hook);
    qRegisterMetaType<Hook::Type>("Type");
    connect(&hook,&Hook::sendKeyType,this,&Widget::checkType);

    QIcon ico=QIcon(":/s.ico");
    trayIcon=new QSystemTrayIcon(this);
    setWindowIcon(ico);
    trayIcon->setIcon(ico);

    trayIcon->show();

    connect(trayIcon,&QSystemTrayIcon::activated,this,&Widget::icon_active);






}

Widget::~Widget()
{
    delete ui;
     hook.unInstallHook();
}

void Widget::loadMedia()
{
    for(int i=0;i<KeyName.size();i++)
    {
        QMediaPlayer * tmpMedia=new QMediaPlayer(this);
        QMediaPlaylist * tmpList=new QMediaPlaylist(this);
        tmpList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        tmpList->addMedia(QUrl("qrc:/"+nowSoundName+KeyName[i]+".mp3"));
        //tmpMedia->setMedia(QUrl("qrc:/"+nowSoundName+KeyName[i]+".mp3"));
        //QString tmpstr="/"+nowSoundName+KeyName[i]+".mp3";
       // qDebug()<<tmpstr;
        //tmpMedia->setMedia(QUrl::fromLocalFile(tmpstr));
        tmpMedia->setPlaylist(tmpList);
        tmpMedia->setVolume(80);
        soundMap.insert(KeyName[i],tmpMedia);
    }
}

void Widget::keyPressEvent(QKeyEvent *e)
{


    if(e->key()==Qt::Key_4)
    {
        qDebug()<<"4!!!";
        auto it=soundMap.find(QString("4"));
        it.value()->play();
    }

    if(e->key()==Qt::Key_Shift)
    {
        qDebug()<<"Key_Shift!!!";
        auto it=soundMap.find(QString("shift"));
        it.value()->play();
    }

    if(e->key()==Qt::Key_Space)
    {
         qDebug()<<"Key_Space!!!";
        auto it=soundMap.find(QString("space"));
        it.value()->play();
    }


}

void Widget::keyReleaseEvent(QKeyEvent *)
{

}

void Widget::mousePressEvent(QMouseEvent *e )
{
    if(e->button()==Qt::RightButton)
    {
         qDebug()<<"RightButton!!!";
        auto it=soundMap.find(QString("right"));
        qDebug()<<it.value()->mediaStatus();
        it.value()->play();
    }

}

void Widget::closeEvent(QCloseEvent * e)
{
    if(trayIcon->isVisible())
    {
        this->hide();
        trayIcon->showMessage("在这里!","双击显示!");
        e->ignore();
    }else
    {
        e->accept();
    }

}

void Widget::icon_active(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
    {
        this->shows();
        this->setVisible(true);
    }
        break;
    }


}

void Widget::shows()
{
    this->setVisible(true);

}

void Widget::checkType(Hook::Type type)
{
    switch (type) {
    case Hook::KEY4:
    {auto it=soundMap.find(QString("4"));
        it.value()->play();}
        break;
    case Hook::KEYSPACE:
    {
        auto it=soundMap.find(QString("space"));
        it.value()->play();
    }
        break;
    case Hook::KEYSHIFT:
    {auto it=soundMap.find(QString("shift"));
        it.value()->play();}
        break;
    case Hook::MOUSERIGHT:
    {
        auto it=soundMap.find(QString("right"));
        it.value()->play();
    }

        break;

    case Hook::KEYTAB:
    {
        auto it=soundMap.find(QString("tab"));
        it.value()->play();
    }
    break;

    case Hook::KEY3:
    {
        auto it=soundMap.find(QString("3"));
        it.value()->play();
    }
    break;
    case Hook::KEYF:
    {
        auto it=soundMap.find(QString("F"));
        it.value()->play();
    }
    break;

    }

}


void Widget::on_pushButton_clicked()
{
    trayIcon->setVisible(false);
    this->close();
}
