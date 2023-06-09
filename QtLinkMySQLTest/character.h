#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include "characterreference.h"
#include <QDebug>

#pragma execution_character_set("utf-8")


// GPT的解读
/*
这是一个名为Character的类，主要用于存储和管理游戏中角色的信息。该类包含了三个成员变量，分别是int类型的ID、QString类型的name和titleName。其中ID为角色的唯一标识符，name为角色的名称，titleName为角色的头衔。

这个类提供了默认构造函数和带参构造函数。默认构造函数没有参数，不做任何操作。带参构造函数接收一个ReferenceType参数，并重载了该参数类型的构造函数。该构造函数根据传入的参数类型，在构造角色对象时提供相应的数据源，以便初始化角色的ID、name和titleName成员变量。

除了构造函数和成员变量的声明和定义之外，该类还提供了get和set方法用于访问和修改成员变量的值，并且提供了一个showInfo方法，用于打印角色的信息，方便调试。

需要注意的是，该类中的ReferenceType枚举类表示数据源的类型，由于该类中只有一个数据源，因此我们只定义了一个CharacterReference成员对象，如果有多个数据源，可以根据需要增加不同的数据源成员。
*/
//





enum class ReferenceType{
  CharacterReference,
};
class Character
{
public:
    Character();
    Character(ReferenceType);

    //------------------可去掉-------------------------//
    int ID() const;
    void setID(int newID);

    QString name() const;
    void setName(const QString &newName);

    QString titleName() const;
    void setTitleName(const QString &newTitleName);
    void showInfo();
private:
    int m_ID;
    QString m_name;
    QString m_titleName;
};

#endif // CHARACTER_H
