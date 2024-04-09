#ifndef MODELMOTABAG_H
#define MODELMOTABAG_H

#include <QObject>
#include "../baseClass/componentobject.h"

class ModelMotaBag : public ComponentObject
{
    Q_OBJECT
    Q_PROPERTY(int yellowKey READ yellowKey WRITE setYellowKey NOTIFY yellowKeyChanged)
    Q_PROPERTY(int blueKey READ blueKey WRITE setBlueKey NOTIFY blueKeyChanged)
    Q_PROPERTY(int redKey READ redKey WRITE setRedKey NOTIFY redKeyChanged)

public:
    explicit ModelMotaBag(QObject *parent = nullptr);
    void tick()override;
    int yellowKey() const;
    void setYellowKey(int newYellowKey);

    int blueKey() const;
    void setBlueKey(int newBlueKey);

    int redKey() const;
    void setRedKey(int newRedKey);

signals:

    void yellowKeyChanged();
    void blueKeyChanged();

    void redKeyChanged();

private:
    int m_yellowKey;
    int m_blueKey;
    int m_redKey;
};
REGISTER_OBJECT(ModelMotaBag,ComponentObject)
#endif // MODELMOTABAG_H
