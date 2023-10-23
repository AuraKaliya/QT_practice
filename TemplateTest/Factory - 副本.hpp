#pragma once

#include<QString>
#include <QMap>
#include <QObject>

template<class T>
class Factory
{
public:

    static Factory<T>* GetInstance()
    {
        if(m_instance==nullptr)
        {
            m_instance=new Factory();
        }
        return m_instance;
    };

    void RegisterObject(const QString &objectName,T* objectClass)
    {
        m_nameToDictionary[objectName]=objectClass;
    };
    void RegisterObject(const QString &objectName,std::function<T*(QWidget*)> objectClass)
    {
        m_factoryCreator.insert(objectName,objectClass);
    };

    T* CreateObject(const QString &objectName,QWidget* parent=nullptr)
    {
        auto it=m_factoryCreator.find(objectName);
        if(it!=m_factoryCreator.end())
        {
            return it.value()(parent);
        }
        else
        {
            return nullptr;
        }
    };
private:

    static Factory<T>* m_instance;

    Factory()=default;

    QMap<QString,T*>m_nameToDictionary;

    QMap<QString,std::function<T*(QWidget*)> >m_factoryCreator;
};


template<class T>
Factory<T>* Factory<T>::m_instance=nullptr;



template <typename T,typename Base>
std::function<Base*(QWidget*)> createFactoryCreator()
{
    return [](QWidget* parent) ->Base*
    {
        return new T(parent);
    };
}

template <typename T,typename Base>
std::function<Base*(QWidget*)> createFactoryCreatorSingle()
{
    return [](QWidget* parent) ->Base*
    {
        return T::GetInstance();
    };
}

// #define INITFACTORY(objectName) static Factory< ##objectName >* Factory_##objectName()::getInstance();
