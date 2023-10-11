#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>


/*
属性的“名”是唯一的，所以可以通过map来存储。（规定同名属性是唯一确定的类型）
建立属性管理器进行管理，通过传入不同Object的指针进行read和write
*/



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_people=new People;
    updatePropertiesList();

    ui->typeBox->addItem("int");
    ui->typeBox->addItem("QString");
    ui->typeBox->addItem("bool");
    ui->typeBox->addItem("double");
    ui->typeBox->addItem("other");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePropertiesList()
{
    //清空重置
    ui->list->clear();
    /*
    while(ui->list->count())
    {
        QListWidgetItem * delItem = ui->list->takeItem(0);
        if(delItem)//注意需要手动删除
            delete delItem;
        qDebug()<<ui->list->count();
    }

    */
    m_properties.clear();
    m_properties.resize(0);
    m_dynamicProperties.clear();
    m_dynamicProperties.resize(0);




    //获取所有属性
    //将属性名添加到ListWidget中显示
    bool flag=true;
    int i=0;

    const QMetaObject * p=m_people->metaObject();
    //qDebug()<<"neo";
    while(flag)
    {
        QMetaProperty property=p->property(i++);
        if(property.isValid())
        {
            m_properties.append(property);

            QListWidgetItem *item=new QListWidgetItem;
            item->setSizeHint(QSize(ui->list->width(),40));
            item->setBackground(QBrush(Qt::yellow));
            item->setText(property.name());
            //item->setFlags(Qt::ItemIsEnabled);
            item->setCheckState(Qt::Unchecked);
            ui->list->addItem(item);

            //ui->list->addItem(property.name());
        }
        else
        {
            flag=false;
            continue;
        }
    }

    QVector<ModelProperty*> list=m_people->getPropertiesList();
    for(auto& it:list)
    {
        ui->list->addItem(it->propertyName());
    }




    if(m_properties.count())
    {
        m_nowProperties=&m_properties[0];
        ui->list->setCurrentRow(0);
    }


}


void MainWindow::on_updateBtn_clicked()
{
     QVariant var=QVariant::fromValue(ui->propertyEdit->text());
    //进行写入
    if(m_nowProperties!=nullptr)
    {
        if(m_nowProperties->write(m_people,var))
        {
            updatePropertiesList();
        }
        else
        {

            QMessageBox::warning(this,"Update Property","Failed to Update!");
        }
    }else
    {
        m_nowDynamicProperties->setValue(var);
        updatePropertiesList();
    }


}


void MainWindow::on_newBtn_clicked()
{
//    QString name=ui->newEdit->text();
//    if(name.isEmpty()) return;
//    QString type=ui->typeBox->currentText();
//    //m_people->setProperty(name,QVariant());

//    Translator::getInstance()->translate(name,type,m_people);
//    updatePropertiesList();
//    m_people->setProperty("HAHAHA",25);
//    qDebug()<<m_people->metaObject()->indexOfProperty("HAHAHA")
//             <<m_people->metaObject()->property(m_people->metaObject()->indexOfProperty("HAHAHA")).name();
//    qDebug()<<"===";

//    qDebug()<<m_people->metaObject()->indexOfProperty(name.toStdString().c_str())
//             <<m_people->metaObject()->property(m_people->metaObject()->indexOfProperty(name.toStdString().c_str())).name();

//       qDebug()<<"===";
//       qDebug()<<name.toStdString().c_str();


    //全部加到动态属性中

    QString name=ui->newEdit->text();
    if(name.isEmpty()) return;
    QString type=ui->typeBox->currentText();
    m_people->addProperty(new ModelProperty(name,type));
     updatePropertiesList();
}


void MainWindow::on_list_currentRowChanged(int currentRow)
{

    if(!m_properties.count()||!(currentRow+1))return;


    if(currentRow<m_properties.size())
    {
        m_nowProperties=&m_properties[currentRow];

        //获取当前属性
        QString pName=m_nowProperties->name();
        QString pType=m_nowProperties->typeName();
        QString pValue=m_nowProperties->read(m_people).toString();


        //展示
        ui->TipsLabel->setText("属性名："+pName+
                                "\t属性类型："+pType+
                                "\t属性值："+pValue);

        //传递到修改区匹配
        ui->name->setText(pName+" :");
        ui->propertyEdit->setText(pValue);
        int index=ui->typeBox->findText(pType);
        if(!(index+1)){
            ui->typeBox->setCurrentIndex(ui->typeBox->count()-1);
            }
        else {
            ui->typeBox->setCurrentIndex(index);
            }
    }
    else
    {
            m_nowProperties=nullptr;
            m_nowDynamicProperties=m_people->getPropertiesList()[currentRow-m_properties.size()];

            //获取当前属性
            QString pName=m_nowDynamicProperties->propertyName();
            QString pType=m_nowDynamicProperties->propertyType();
            QString pValue=m_nowDynamicProperties->propertyValue().toString();

        //展示
        ui->TipsLabel->setText("属性名："+pName+
                                "\t属性类型："+pType+
                                "\t属性值："+pValue);

        //传递到修改区匹配
        ui->name->setText(pName+" :");
        ui->propertyEdit->setText(pValue);
        int index=ui->typeBox->findText(pType);
        if(!(index+1)){
            ui->typeBox->setCurrentIndex(ui->typeBox->count()-1);
            }
        else {
            ui->typeBox->setCurrentIndex(index);
            }


    }


}

