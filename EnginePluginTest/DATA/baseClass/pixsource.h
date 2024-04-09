#ifndef PIXSOURCE_H
#define PIXSOURCE_H

#include <QObject>
#include <QPixmap>

class PixSource : public QObject
{
    Q_OBJECT
public:
    enum Type{
        StaticPix,
        DynamicPix
    };

    explicit PixSource(int  id,QPixmap *pix,Type type,QObject *parent = nullptr);
    explicit PixSource(int id,QString pixPath,Type type,QObject *parent = nullptr);
    void setPerPixSize(int perW,int perH);
    void setPerInterval(int xInterval,int yInterval);
    void setPixSize(int width,int height);
    int getPerW() const;

    int getPerH() const;

    QPixmap* pix() const;

    PixSource::Type type() const;

    QString pixStateList() const;
    void setPixStateList(const QString &newPixStateList);

    QString pixIndexList() const;
    void setPixIndexList(const QString &newPixIndexList);

    QVector<QString> stateList() const;
    void setStateList(const QVector<QString> &newStateList);

    QVector<QVector<int> > stateIndexList() const;
    void setStateIndexList(const QVector<QVector<int> > &newStateIndexList);

    int id() const;

    int XInterval() const;

    int YInterval() const;

private:
    QPixmap *m_pix;
    Type m_type;

    int m_id=0;
    int m_perW;
    int m_perH;

    int m_XInterval=0;
    int m_YInterval=0;

    QString m_pixStateList;
    QString m_pixIndexList;

    QVector <QString> m_stateList;
    QVector<QVector<int> > m_stateIndexList;

signals:

};

#endif // PIXSOURCE_H
