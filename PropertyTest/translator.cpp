#include "translator.h"

Translator* Translator::m_instance=nullptr;
QMap<QString,QString>Translator::m_propertiesDictionary={};
Translator *Translator::getInstance()
{
    if(m_instance==nullptr)
    {
        m_instance=new Translator;
    }
    return m_instance;
}

void Translator::translateToInt(const QString &str, QVariant &var, QObject *obj)
{
    obj->setProperty(str.toStdString().c_str(),var.toInt());
    m_propertiesDictionary.insert(str,QString("int"));
}

void Translator::translateToStr(const QString& str,QVariant &var, QObject *obj)
{
    obj->setProperty(str.toStdString().c_str(),var.toString());
    m_propertiesDictionary.insert(str,QString("QString"));
}

void Translator::translateToDouble(const QString& str,QVariant &var, QObject *obj)
{
    obj->setProperty(str.toStdString().c_str(),var.toDouble());
    m_propertiesDictionary.insert(str,QString("double"));
}

void Translator::translateToBool(const QString& str,QVariant &var, QObject *obj)
{
    obj->setProperty(str.toStdString().c_str(),var.toBool());
    m_propertiesDictionary.insert(str,QString("bool"));
}

void Translator::translate(const QString& str,const QString& type,QObject*obj)
{

    auto it=m_dictionary.find(type);
    if(it == m_dictionary.end()) it =m_dictionary.find("default");
    qDebug()<<it.key();
    it.value()(str,m_var,obj);

}



Translator::Translator()
{
    m_var.setValue(0);
    m_dictionary.insert("int",translateToInt);
    m_dictionary.insert("QString",translateToStr);
    m_dictionary.insert("double",translateToDouble);
    m_dictionary.insert("bool",translateToBool);
    m_dictionary.insert("default",translateToStr);


}
