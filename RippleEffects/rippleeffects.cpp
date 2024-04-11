#include "rippleeffects.h"

RippleEffects::RippleEffects()
{
    m_pluginName = "RippleEffects";
}

void RippleEffects::initPlugin()
{

}

void RippleEffects::work()
{

}

QWidget *RippleEffects::getWidget()
{
    if(!m_widget)
        {

        }
    return m_widget;


}

QString RippleEffects::getPluginName()
{
    return m_pluginName;
}

void RippleEffects::initApp(UIWidget *w)
{
    if(!w)
    {
        return ;
    }
    else
    {
        m_rootWidget=w;
        //
        //=====
    }
}
