#ifndef INITBYDATABASE_H
#define INITBYDATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QApplication>
#include <QSqlRecord>
#include <QString>
#include <QDebug>
#include <QMap>
#include <QVector>
#include "character.h"

typedef void (*Func)(const QVariant &);
class InitByDatabase
{
public:
    static InitByDatabase *getInstance();

    bool initDatabase();

    void initDictionary();
    QVector<Character*> readDataToCharacter();

private:
    static InitByDatabase* m_instance;
    InitByDatabase();
    ~InitByDatabase();
    QSqlDatabase db;

    QMap<QString,Func> m_initFunctionDictionary;

};

#endif // INITBYDATABASE_H
