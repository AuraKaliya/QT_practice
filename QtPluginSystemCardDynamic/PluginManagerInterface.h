#ifndef PLUGINMANAGERINTERFACE_H
#define PLUGINMANAGERINTERFACE_H

#include <QWidget>
#include "uimainwidget.h"
#include "manager.h"



#define PluginManagerInterfaceIID "com.auratest.PluginManagerInterface/1.0.0"
//定义插件的IID，类似java中的包命名：组织机构域名加产品名加版本号


class PluginManagerInterface
{
public:
    virtual ~PluginManagerInterface()=default;
    virtual void initPlugin()=0;
    virtual void run()=0;
    virtual QWidget* getWidget()=0;
    virtual void initApp(UIMainWidget*)=0;
    virtual void setNowManager(Manager*m)=0;

};


Q_DECLARE_INTERFACE(PluginManagerInterface,PluginManagerInterfaceIID)
//通过宏将该接口进行声明



#endif // PLUGINMANAGERINTERFACE_H
