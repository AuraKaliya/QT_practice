#pragma once

#include "Factory.hpp"


template<class Base>
class Register
{
public:
    Register()=default;
    Register(const QString & objectName,Base* objectClass)
    {
        Factory<Base>* factory=Factory<Base>::GetInstance();
        factory->RegisterObject(objectName,objectClass);
    };
    Register(const QString &objectName,std::function<Base*(QObject*)> objectClass)
    {
        Factory<Base>* factory=Factory<Base>::GetInstance();
        factory->RegisterObject(objectName,objectClass);
    };
    Register(const QString &objectName,std::function<Base*(QWidget*)> objectClass)
    {
        Factory<Base>* factory=Factory<Base>::GetInstance();
        factory->RegisterObject(objectName,objectClass);
    };


};


//#define REGISTER_OBJECT(objectName,baseName) static Register< objectName , baseName > Register_##objectName( #objectName ,createFactoryCreator< objectName , baseName > () );
//#define REGISTER_OBJECT_SINGLE(objectName,baseName) static Register< objectName , baseName > Register_##objectName( #objectName ,createFactoryCreatorSingle< objectName , baseName > () );

#define REGISTER_OBJECT(objectName,baseName) static Register< baseName > Register_##objectName( #objectName ,createFactoryCreator< objectName , baseName > () );
#define REGISTER_OBJECT_SINGLE(objectName,baseName) static Register< baseName > Register_##objectName( #objectName ,createFactoryCreatorSingle< objectName , baseName > () );
#define REGISTER_WIDGET(objectName,baseName) static Register< baseName > Register_##objectName( #objectName ,createWidgetFactoryCreator< objectName , baseName > () );
#define REGISTER_WIDGET_SINGLE(objectName,baseName) static Register< baseName > Register_##objectName( #objectName ,createWidgetFactoryCreatorSingle< objectName , baseName > () );



