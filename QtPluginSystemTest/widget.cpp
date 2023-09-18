#include "widget.h"
#include "ui_widget.h"

#include <QDir>
#include <QMessageBox>
#include "PluginManagerInterface.h"
Widget::Widget(QWidget *parent)
    : UIMainWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initWidget();
}

Widget::~Widget()
{
    //
    //这里用于自动卸载插件
    //
    delete ui;
}

void Widget::initWidget()
{
    m_cardManager=CardManager::getInstance();
    addManager("CardManager",(Manager*)m_cardManager);
    //只是传基类指针，这个指针指向的实体的内存大小还是子类的。
}

void Widget::resolveStr(QString str)
{
    this->ui->label->setText(this->ui->label->text()+"\n"+str);
}


void Widget::on_pushButton_clicked()
{

    QDir dir(qApp->applicationDirPath());//获取当前程序的执行文件所在路径
    m_loader.setFileName(dir.filePath("QtPluginSystemCardDynamic.dll")); //选择加载的插件，通过传入dll库进行。

    if(!m_loader.load())
    {
        QMessageBox::critical(this,"",m_loader.errorString());
        return;
    }
    PluginManagerInterface* pi= qobject_cast<PluginManagerInterface*>(m_loader.instance());
    //进行强制类型转换，确保是PluginInterface的插件。
    if(pi)
    {
        QWidget* w=pi->getWidget();
        if(w)
        {
            ui->tabWidget->addTab(w,"hello plugin");
            pi->initApp(this);
        }
    }
    //执行具体逻辑

}

void Widget::on_pushButton_2_clicked()
{
    m_cardManager->getNewCard();
}

