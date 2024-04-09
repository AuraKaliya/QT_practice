#ifndef MODELBAG_H
#define MODELBAG_H

#include <QObject>

#include "../baseClass/componentobject.h"

/*
    bag--背包模块
    需要有几个功能
    1. 物品id 物品的名称 数量
    2. 根据名称找物品 根据id找物品  返回数量
    3. 增加物品  id 名称 数量
    4. 删除物品  id/名称 数量

*/


class ModelBag : public ComponentObject
{
    Q_OBJECT

    Q_PROPERTY(int bagSize READ bagSize WRITE setBagSize NOTIFY bagSizeChanged)

public:
    explicit ModelBag(QObject *parent = nullptr);
    void tick()override;

    int bagSize() const;
    void setBagSize(int newBagSize);

signals:

    void bagSizeChanged();
private:
    int m_bagSize;
};

#endif // MODELBAG_H
