#include "widget.h"
#include "ui_widget.h"
#include "constvalue.h"

#include <QKeyEvent>

int nowNumber=10;
int Widget::myNumber=10;

int readKeyState(lua_State* pState)
{
    GlobalKeyValue keyValue;
    const char* key=lua_tostring(pState,-1);
    //qDebug()<<"readKeyState  Key:"<<key;
    bool flag=keyValue.getKeyPressedState(key);
    lua_pushboolean(pState,flag);
    return 1;
}

int setNowNumber(lua_State* pState)
{
    int newNumber=lua_tonumber(pState,-1);
    nowNumber+=newNumber;
    lua_pushboolean(pState,true);
    return 1;
}


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    pState= luaL_newstate();
    luaL_openlibs(pState);

    luaL_dofile(pState,"test.lua");
    //lua_pcall(pState, 0, 0, 0);

#if 0
    qDebug()<<"0000000000000000000000";
    L = luaL_newstate();
     luaL_openlibs(L);
    int retLoad = luaL_loadfile(L, "test.lua");
    if (retLoad == 0)
    {
        qDebug()<<"load file success retLoad:"<< retLoad;
    }
    if (retLoad || lua_pcall(L, 0, 0, 0))
    {
         qDebug()<<"error"<< retLoad;
    }
    lua_getglobal(L, "name"); //lua获取全局变量name的值并且返回到栈顶
    const char *name = lua_tostring(L, -1);//次栈顶
    qDebug()<<"Lua arg  name="<<name;
    lua_close(L);
#endif

    tickTimer.setInterval(30);
    connect(&tickTimer,&QTimer::timeout,this,[=](){
        lua_getglobal(pState,"tick");
        lua_pcall(pState,0,0,0);
    });


   timer.setInterval(100);
    connect(&timer,&QTimer::timeout,this,[=](){
        qDebug()<<"nowNumber:"<<nowNumber;
    });


    lua_register(pState,"readKeyState",readKeyState);
    lua_register(pState,"setNowNumber",setNowNumber);

    tickTimer.start();
    timer.start();


}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *e)
{
  //  qDebug()<<e->key() << "Key Pressed";
    qDebug()<<Qt::Key_Up;
    GlobalKeyValue keyValue;
    //目前支持定义0-9：48~57  a-z:65~90
    if(e->key()>=65&&e->key()<=90)
    {
        *(keyValue.keyDictionaryByChar.find(e->key()-65).value())=true;
    }

    if(e->key()>=48&&e->key()<=57)
    {
        *(keyValue.keyDictionaryByNum.find(e->key()-48).value())=true;
    }

}

void Widget::keyReleaseEvent(QKeyEvent *e)
{
    //qDebug()<<"==============================";
    qDebug()<<e->key() << "Key Release";
    //qDebug()<<Qt::Key_Up;
    GlobalKeyValue keyValue;
    //目前支持定义0-9：48~57  a-z:65~90
    if(e->key()>=65&&e->key()<=90)
    {
        *(keyValue.keyDictionaryByChar.find(e->key()-65).value())=false;
    }

    if(e->key()>=48&&e->key()<=57)
    {
        *(keyValue.keyDictionaryByNum.find(e->key()-48).value())=false;
    }

}


void Widget::on_pushButton_clicked()
{
    lua_getglobal(pState, "name"); //lua获取全局变量name的值并且返回到栈顶
    const char *name = lua_tostring(pState, -1);//次栈顶
    qDebug()<<"Lua arg  name2="<<name;
}


Widget *Widget::getThis()
{
    return this;
}

