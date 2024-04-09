#ifndef MODELTOWER_H
#define MODELTOWER_H

#include <QObject>
#include "../baseClass/componentobject.h"

class ModelTower : public ComponentObject
{
    Q_OBJECT
    Q_PROPERTY(unsigned int allLayers READ getAllLayers WRITE setAllLayers NOTIFY allLayersChanged)
    Q_PROPERTY(unsigned int nowLayer READ getNowLayer WRITE setNowLayer NOTIFY nowLayerChanged)

private:
    unsigned int m_allLayers;
    unsigned int m_nowLayer;
    QVector<int> m_layerLinkedList;
    QVector<int> m_layerPreLinkList;

    QMap<int,QPair<int,int> > m_layerUpPos;
    QMap<int,QPair<int,int> > m_layerDownPos;


public:
    explicit ModelTower(QObject *parent = nullptr);

    void tick() override;

    unsigned int getNextLayerId();

    void setLayers( const unsigned int& layers);
    void setNowLayer(const unsigned int& nowLayer);
    void setLinkList(const QVector<int>& layerLinkedList);
    void nextLayer();
    int getNextLayer();
    int getPreLayer();

    unsigned int getAllLayers() const;
    void setAllLayers(unsigned int newAllLayers);

    QVector<int> getLayerLinkedList() const;
    void setLayerLinkedList(const QVector<int> &newLayerLinkedList);

    unsigned int getNowLayer() const;

    void setLinked(int layer,int linkLayer);

    QMap<int, QPair<int, int> > layerUpPos() const;
    void setLayerUpPos(const QMap<int, QPair<int, int> > &newLayerUpPos);

    QMap<int, QPair<int, int> > layerDownPos() const;
    void setLayerDownPos(const QMap<int, QPair<int, int> > &newLayerDownPos);

    QPair<int,int> getUpPos(int layer);
    QPair<int,int> getDownPos(int layer);
    QVector<int> layerPreLinkList() const;
    void setLayerPreLinkList(const QVector<int> &newLayerPreLinkList);

signals:

    void allLayersChanged();
    void layerLinkedListChanged();
    void nowLayerChanged();
};
REGISTER_OBJECT(ModelTower,ComponentObject)
#endif // MODELTOWER_H
