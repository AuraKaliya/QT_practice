#ifndef COMPONENT_H
#define COMPONENT_H


#include <QVariant>


template<typename LinkClass>
class Component
{
public:
    Component(LinkClass & linkClass):m_linkClass(linkClass),m_value(QVariant())
    {
    }

    inline LinkClass &linkClass()
    {
        return m_linkClass;
    };

    inline QVariant getValue()const
    {
        return m_value;
    };

    template<typename ValueClass>
    ValueClass getValue()
    {
        return getValue().template value<ValueClass>();
    }

    inline void setValue(const QVariant & value){
        m_value.setValue(value);
    };

protected:
    QVariant m_value;
    LinkClass & m_linkClass;

private:

};





#endif // COMPONENT_H
