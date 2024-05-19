#ifndef ENTITY_H
#define ENTITY_H


#include <QMap>
#include <QString>

#include "Component.hpp"

//template<typename EntityClass>
class Entity
{
public:
    Entity():m_componentDictionary{}
    {};

    inline void addComponent(QString componentClass,Component<Entity>* component)
    {
        m_componentDictionary[componentClass]=component;
    };

    inline Component<Entity>* getComponent(QString componentClass){
        return m_componentDictionary[componentClass];
    };

    inline bool hasComponent(QString  componentClass)
    {
        return m_componentDictionary.contains(componentClass);
    }

protected:
    QMap<QString,Component<Entity>*> m_componentDictionary;
private:
};






#endif // ENTITY_H
