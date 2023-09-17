#include "plugindemo1.h"
#include "form.h"

PluginDemo1::PluginDemo1()
{
    m_genWidget=Q_NULLPTR;
}

PluginDemo1::~PluginDemo1()
{
    if(m_genWidget)
    {
        m_genWidget->deleteLater();
    }
}

QWidget *PluginDemo1::genWidget()
{
    if(!m_genWidget)
    {
        m_genWidget=new Form;
        //实例化管理的插件的ui窗体
    }
    return m_genWidget;
}
