#ifndef CHARACTERREFERENCE_H
#define CHARACTERREFERENCE_H

#include <QString>
#include <QSqlQuery>
#include <QDebug>


//GPT的解读
/*
这是一个名为CharacterReference的类，通过单例模式提供了角色信息的数据源。该类中有三个静态成员变量，分别是int类型的m_ID、QString类型的m_name和m_titleName。这些变量用于存储角色的ID、name和titleName信息。

该类提供了一个getInstance静态方法，返回一个CharacterReference类型的指针，用于获取类的唯一实例。该方法使用了懒汉式单例模式的实现方式，即在第一次调用时才创建实例。在类的内部定义了一个私有构造函数，以保证该类不能被外部直接实例化。

此外，该类还提供了get和set方法用于访问和修改成员变量的值，其中set方法重载了QVariant类型参数的版本，方便从数据库中读取数据并设置相应的成员变量。最后，该类还提供了一个show方法用于在控制台输出角色信息，方便测试和调试。

*/
//



 class CharacterReference
{
public:

    static CharacterReference* getInstance();

    int ID();
    static void setID(int newID);
    static void setIDByQVariant(const QVariant &value);
    QString name();
    static void setName(const QString &newName);
    static void setNameByQVariant(const QVariant &value);
    QString titleName();
    static void setTitleName(const QString &newTitleName);
    static void setTitleNameByQVariant(const QVariant &value);
    static void show();
private:
    CharacterReference();

    static CharacterReference* m_instance;

    static int m_ID;
    static QString m_name;
    static QString m_titleName;
};

#endif // CHARACTERREFERENCE_H
