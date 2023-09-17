#include "widget.h"
#include "ui_widget.h"
#include "PluginInterface.h"
#include <QDir>
#include<QMessageBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    if(m_loadr.isLoaded())
    {
        m_loadr.unload();
    }
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QDir dir(qApp->applicationDirPath());
    //获取当前程序的执行路径。
    m_loadr.setFileName(dir.filePath("PluginDemo1.dll"));
    if(!m_loadr.load())
    {
        QMessageBox::critical(this,"",m_loadr.errorString());
        return;
    }
    PluginInterface* pi= qobject_cast<PluginInterface*>(m_loadr.instance());

    if(pi)
    {
        QWidget* w=pi->genWidget();
        if(w)
        {
            ui->tabWidget->addTab(w,"hello plugin");

        }
    }

}

