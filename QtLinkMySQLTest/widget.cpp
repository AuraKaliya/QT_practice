#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


//    QStringList drivers=QSqlDatabase::drivers();
//    foreach (QString driver,drivers)
//        qDebug()<<driver;





    InitByDatabase* ibd=InitByDatabase::getInstance();

    ibd->initDatabase();
    ibd->initDictionary();
    QVector<Character*> chara=ibd->readDataToCharacter();

    for(auto it:chara)
        it->showInfo();


}

Widget::~Widget()
{
    delete ui;
}

