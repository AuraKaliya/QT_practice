#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <QObject>

class BaseObject : public QObject
{
    Q_OBJECT
public:
    explicit BaseObject(QObject *parent = nullptr);
    virtual void debug()=0;
signals:

};

#endif // BASEOBJECT_H
