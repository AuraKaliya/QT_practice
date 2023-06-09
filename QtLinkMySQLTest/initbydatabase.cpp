#include "initbydatabase.h"



//GPT的解读————————————
/*
这段代码实现了一个单例模式的类InitByDatabase，主要用于初始化数据库连接和读取游戏中角色数据。
头文件#include "initbydatabase.h"表示引用了InitByDatabase类所在的头文件。该类封装了与数据库连接相关的函数。
InitByDatabase::InitByDatabase()是InitByDatabase类的构造函数，定义为空函数体。
InitByDatabase::~InitByDatabase()是InitByDatabase类的析构函数，在析构该类对象时关掉数据库连接。
在InitByDatabase类中使用单例模式，定义静态指针m_instance指向InitByDatabase对象，初始时设为nullptr。
InitByDatabase *InitByDatabase::getInstance()是获取单例对象的方法，如果还未创建对象，则创建一个初始化连接，并将其赋值给m_instance。
bool InitByDatabase::initDatabase()方法是初始化数据库连接的函数，使用QSqlDatabase连接MySQL数据库，设置主机名、数据库名、端口号、用户名和密码，并打开连接，返回连接状态。
void InitByDatabase::initDictionary()方法初始化了一个std::map结构的字典，键为数据表中的列名，值为一个指向字符Reference类中对应成员的函数指针。
QVector<Character*> InitByDatabase::readDataToCharacter()方法读取数据库中的角色数据并存入QVector容器中，通过QSqlQuery查询每个角色数据的相应列值，再通过字典的函数指针设置角色的成员变量。最后将角色指针存入QVector容器中，返回该容器。
总之，这段代码的主要功能是实现数据库的连接和数据读取的操作，并封装在InitByDatabase类里以方便调用。其中使用了单例模式和字典（map）数据结构。
*/
//
InitByDatabase::InitByDatabase()
{

}

InitByDatabase::~InitByDatabase()
{
    db.close();
}
InitByDatabase* InitByDatabase::m_instance = nullptr;
InitByDatabase *InitByDatabase::getInstance()
{
    if(m_instance==nullptr)
    {
        m_instance=new InitByDatabase();
    }
    return m_instance;
}

bool InitByDatabase::initDatabase()
{

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("luck_no_complete_save1");
    db.setPort(3306);

    db.setUserName("root");
    db.setPassword("password");

    bool flag=db.open();
    if(!flag)
    {
        qDebug()<<"Cant Link";
    }else
    {
        qDebug()<<"Link";
    }
    return flag;
}

void InitByDatabase::initDictionary()
{
    m_initFunctionDictionary["CharacterID"]=CharacterReference::setIDByQVariant;
    m_initFunctionDictionary["CharacterName"]=CharacterReference::setNameByQVariant;
    m_initFunctionDictionary["CharacterTitle"]=CharacterReference::setTitleNameByQVariant;

}

 QVector<Character*> InitByDatabase::readDataToCharacter()
{
    QVector <Character*> tmpCharacterList;
    QString strTableNmae="CHARACTERLIST";
    QVector<QString> columName;
    QString str = QString("select  column_name from information_schema.columns where table_name='%1'and TABLE_SCHEMA='%2';").arg(strTableNmae).arg(db.databaseName());

    QSqlQuery query(str,db);
    while(query.next())
    {
        columName.append(query.value(0).toString());
    }

    QSqlQuery query1("select * from "+db.databaseName()+"."+strTableNmae+";",db);
    while (query1.next()) {
        for(int i=0;i<columName.size();++i)
        {
            auto it =m_initFunctionDictionary.find(columName[i]);
            if (it!=m_initFunctionDictionary.end())
            {
                m_initFunctionDictionary.value(columName[i])(query1.value(i));
            }
        }
        Character * tmpCharacter=new Character(ReferenceType::CharacterReference);
        tmpCharacterList<<tmpCharacter;
    }
    return tmpCharacterList;
}
