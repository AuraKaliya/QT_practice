#ifndef PLUGINCARDMANAGER_H
#define PLUGINCARDMANAGER_H

#include "cardmanager.h"
#include <QtWidgets/QtWidgets>
#include <QObject>
#include "PluginManagerInterface.h"
#include "QtPluginSystemCardDynamic_global.h"


class QTPLUGINSYSTEMCARDDYNAMIC_EXPORT PluginCardManager : public QObject,public PluginManagerInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginManagerInterfaceIID)
    Q_INTERFACES(PluginManagerInterface)
public:
    explicit PluginCardManager(QObject *parent = nullptr);
    ~PluginCardManager()override;
    void initPlugin()override;
    void run()override;
    QWidget* getWidget()override;
    void initApp(UIMainWidget*)override;
    void setNowManager(Manager*m)override;

signals:
    void contextSent(QString);
private:
    QWidget * m_genWidget;
    UIMainWidget* m_nowApp;
    CardManager* m_cardManager;
};

#endif // PLUGINCARDMANAGER_H
