#ifndef SCRIPT_H
#define SCRIPT_H
#include <QString>
#include <lua.hpp>
#include <DATA/baseClass/gameobject.h>
#include <DATA/baseClass/gameobjectitem.h>

class Script
{
public:
    Script(QString fileName,GameObject*obj,GameObjectItem*item);
    lua_State* m_lua=nullptr;
    QString m_fileName;
    GameObject* m_obj;
    GameObjectItem * m_item;

};

#endif // SCRIPT_H
