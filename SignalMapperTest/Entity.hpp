#ifndef ENTITY_H
#define ENTITY_H


#include <QMap>
#include <QString>

#include "Component.hpp"

class Entity
{
public:
    Entity():m_componentDictionary{}
    {};

    inline void addComponent(const QString & componentClass,Component<Entity>* component)
    {
        m_componentDictionary[componentClass]=component;
    };

    inline Component<Entity>* getComponent(const QString & componentClass){
        return m_componentDictionary[componentClass];
    };

    inline bool hasComponent(const QString & componentClass)
    {
        return m_componentDictionary.contains(componentClass);
    }

protected:
    //这个应该为静态量， 通过类似SignalSlotManager的那种方式管理，可以把Key进行组合
    QMap<QString,Component<Entity>*> m_componentDictionary;
private:
};






#endif // ENTITY_H
