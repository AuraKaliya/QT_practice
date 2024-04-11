#ifndef ENGINEPLUGIN_H
#define ENGINEPLUGIN_H

#include <QWidget>
#include "uiwidget.h"


#define PluginManagerInterfaceIID "aura.engine.Plugin/1.0.0"
//定义插件的IID，类似java中的包命名：组织机构域名加产品名加版本号

class EnginePlugin
{
public:
    EnginePlugin()=default;
    virtual ~EnginePlugin()=default;
    virtual void initPlugin()=0;
    virtual void work()=0;
    virtual QWidget* getWidget()=0;
    virtual QString getPluginName()=0;
    virtual void initApp(UIWidget*)=0;
protected:
    QString m_pluginName    ="Default"    ;
    QWidget* m_widget       =nullptr      ;
    UIWidget* m_rootWidget  =nullptr      ;
};

Q_DECLARE_INTERFACE(EnginePlugin,PluginManagerInterfaceIID)
//通过宏将该接口进行声明

#endif // ENGINEPLUGIN_H
