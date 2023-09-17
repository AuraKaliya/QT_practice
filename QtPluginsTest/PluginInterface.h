#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QWidget>


#define PluginInterfaceIID "com.auratest.PluginInterface/1.0.0"
//定义插件的IID，类似java中的包命名：组织机构域名加产品名加版本号

class PluginInterface{
public:
    virtual ~PluginInterface()=default;
    virtual QWidget * genWidget()=0;
};
//接口类纯虚函数和虚析构。


Q_DECLARE_INTERFACE(PluginInterface,PluginInterfaceIID)
//通过宏将该接口进行声明

#endif // PLUGININTERFACE_H
