#ifndef MANAGER_H
#define MANAGER_H

#include<QWidget>
#include<QVector>
#include <QVariant>

class Manager:public QObject
{
    Q_OBJECT
public:
    virtual ~Manager()=default;
    virtual void initManager(){};
    virtual void addObject(QVariant var){};
    virtual QVariant findByID(int id){return QVariant();};
    virtual QVariant findByName(QString name){return QVariant();};
    inline Manager* getMe(){return (Manager*)this;};
signals:
    void me(Manager*);
};

#endif // MANAGER_H
