#ifndef BLUEPRINTSSCENE_H
#define BLUEPRINTSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include "../Manager/nodemanager.h"

class BlueprintsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BlueprintsScene(QObject *parent = nullptr);


protected:



private:
    void preInit();
private:
    NodeManager * m_nodeManager=nullptr;
signals:

};

#endif // BLUEPRINTSSCENE_H
