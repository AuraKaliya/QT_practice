#ifndef PLUGINDEMO1_H
#define PLUGINDEMO1_H

#include "PluginDemo1_global.h"
#include "PluginInterface.h"

class PLUGINDEMO1_EXPORT PluginDemo1:public QObject,public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginInterfaceIID)
    Q_INTERFACES(PluginInterface)

    //元对象注册
    //设置当前插件的元数据并对外提供实例
    //进行插件接口的ID校验

public:
    PluginDemo1();
    ~PluginDemo1();
    QWidget* genWidget()override;
private:
    QWidget* m_genWidget;
};

#endif // PLUGINDEMO1_H
