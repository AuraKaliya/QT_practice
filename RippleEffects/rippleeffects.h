#ifndef RIPPLEEFFECTS_H
#define RIPPLEEFFECTS_H

#include "RippleEffects_global.h"
#include <QObject>
#include <DATA/baseClass/engineplugin.h>

class RIPPLEEFFECTS_EXPORT RippleEffects:public QObject,public EnginePlugin
{
public:
    RippleEffects();
    void initPlugin()       override;
    void work()             override;
    QWidget* getWidget()    override;
    QString getPluginName() override;
    void initApp(UIWidget*) override;
private:


};

#endif // RIPPLEEFFECTS_H
