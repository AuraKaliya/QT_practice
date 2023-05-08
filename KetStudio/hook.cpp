#include "hook.h"
#include <QDebug>

static HHOOK keyHook=nullptr;//钩子对象
static Hook* hook;//Qt界面中调用Hook类的对象
LRESULT CALLBACK keyProc(int nCode,WPARAM wParam,LPARAM lParam){//钩子消息函数，系统消息队列信息会返回到该函数中
    KBDLLHOOKSTRUCT* pkbhs = (KBDLLHOOKSTRUCT*)lParam;//lParam用于判断按键类型
    if(wParam == WM_KEYDOWN){//wParam用于判断事件类型，当前为按键按下事件

        if(pkbhs->vkCode == 0x34 ){//4
            hook->sendSignal(Hook::KEY4);//安装钩子的对象发出按键监听信号
        }
        if(pkbhs->vkCode == 0x33 ){//3
            hook->sendSignal(Hook::KEY3);//安装钩子的对象发出按键监听信号
        }
        if(pkbhs->vkCode == 0x46 ){//F
            hook->sendSignal(Hook::KEYF);//安装钩子的对象发出按键监听信号
        }

       // GetAsyncKeyState(
        if(pkbhs->vkCode == VK_SPACE){//按下space
            hook->sendSignal(Hook::KEYSPACE);
        }
        if(pkbhs->vkCode == VK_LSHIFT){//按下lshift
            hook->sendSignal(Hook::KEYSHIFT);
        }
        if(pkbhs->vkCode == 0x09){//按下lshift
            hook->sendSignal(Hook::KEYTAB);
        }

    }else if(wParam==WM_RBUTTONDOWN)
    {
        if(pkbhs->vkCode ==VK_LBUTTON){//按下右键
            qDebug()<<"123456";
            hook->sendSignal(Hook::MOUSERIGHT);
        }
    }





    return CallNextHookEx(keyHook,nCode,wParam,lParam);//继续原有的事件队列
}

Hook::Hook()
{

}

void Hook::installHook(Hook* h){//安装钩子函数
    keyHook = SetWindowsHookEx(WH_KEYBOARD_LL,keyProc,nullptr,0);
    hook = h;
}
void Hook::unInstallHook(){//删除钩子函数
    UnhookWindowsHookEx(keyHook);
    keyHook = nullptr;
}

void Hook::sendSignal(Type type){//发送信号函数
    emit sendKeyType(type);
}
