#include "engineplugintest.h"

EnginePluginTest::EnginePluginTest(QObject *parent):QObject{parent}
{
    m_pluginName="EnginePluginTest";

    m_widget=Q_NULLPTR;
    m_rootWidget=Q_NULLPTR;

}

void EnginePluginTest::initPlugin()
{

}

void EnginePluginTest::work()
{
    getWidget()->show();
}

QWidget *EnginePluginTest::getWidget()
{
    if(!m_widget)
    {
        m_widget=new UIWidget();
        m_widget->setWindowTitle("Test Plugin");
        m_dir=new QDir(qApp->applicationDirPath()+"/pluginRes");
        QIcon icon(m_dir->filePath("TestPluginIcon.png"));
        if(icon.isNull())
        {
            qDebug()<<" test plugin  icon null=====";
            qDebug()<<m_dir->path();
        }
        else
        {
            m_widget->setWindowIcon(icon);
        }

        ClickLabel * label=new ClickLabel("This is Test Plugin!",m_widget);
        label->setAlignment(Qt::AlignCenter);
        //label->adjustSize();
        label->move(0,0);
        m_widget->resize(200,200);
        label->resize(200,200);
        connect(label,&ClickLabel::clicked,m_widget,[this](){
            QString str("This is Test Plugin Str!");
            m_widget->emit actionSend(str);
            m_widget->emit instructionSend(str);
            m_widget->emit eventSend(str);
            //qDebug()<<m_dir->path();
        });
    }
    return m_widget;
}

QString EnginePluginTest::getPluginName()
{
    return m_pluginName;
}

void EnginePluginTest::initApp(UIWidget *w)
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
