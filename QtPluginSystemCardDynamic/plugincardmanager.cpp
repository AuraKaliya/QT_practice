#include "plugincardmanager.h"

#include <QtWidgets/QLabel>
#include <QVariant>
PluginCardManager::PluginCardManager(QObject *parent)
    : QObject{parent}
{
    m_genWidget=Q_NULLPTR;
    m_nowApp=Q_NULLPTR;
    m_cardManager=Q_NULLPTR;
}

PluginCardManager::~PluginCardManager()
{
    if(m_genWidget)
    {
        m_genWidget->deleteLater();
    }
}

void PluginCardManager::initPlugin()
{

}

void PluginCardManager::run()
{
    emit contextSent(QString("Hello this is Plug's run()\n"));
}

QWidget *PluginCardManager::getWidget()
{
    if(!m_genWidget)
    {
        m_genWidget=new QWidget();
        QLabel * label=new QLabel("This is Plugin!",m_genWidget);
        label->setAlignment(Qt::AlignCenter);
        label->adjustSize();
    }
    return m_genWidget;
}

void PluginCardManager::initApp(UIMainWidget *w)
{
    if(!w)
    {
        return;
    }
    else
    {
        m_nowApp=w;
        setNowManager(m_nowApp->getManager().value("CardManager"));
    }

        return;
}

void PluginCardManager::setNowManager(Manager *m)
{
        if(!m)
        {
            return;
        }
        else
        {
            m_cardManager=(CardManager*)m;
            connect(this,&PluginCardManager::contextSent,m_nowApp,[=](QString str){
                m_nowApp->resolveStr(str);
            });
            connect(m_cardManager,&CardManager::cardChoiced,this,[=](Card* c){
                emit contextSent(c->cardIntroduction);
            });
        }
        return;
}
