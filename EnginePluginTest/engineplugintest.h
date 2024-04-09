#ifndef ENGINEPLUGINTEST_H
#define ENGINEPLUGINTEST_H

#include "EnginePluginTest_global.h"
#include <DATA/baseClass/engineplugin.h>
#include <QLabel>
#include <QDir>
#include "QApplication"
#include <DATA/baseClass/clicklabel.h>

class ENGINEPLUGINTEST_EXPORT EnginePluginTest: public QObject,public EnginePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginManagerInterfaceIID)
    Q_INTERFACES(EnginePlugin)
public:
    EnginePluginTest(QObject *parent=nullptr);
    void initPlugin()override;
    void work()override;
    QWidget* getWidget()override;
    QString getPluginName()override;
    void initApp(UIWidget*w)override;
protected:

private:
    UIWidget * m_widget;
    UIWidget* m_rootWidget;
    QString m_pluginName;
    QDir* m_dir;

};

#endif // ENGINEPLUGINTEST_H
