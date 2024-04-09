#include "pixsource.h"
#include <QDebug>
PixSource::PixSource(int  id,QPixmap *pix, Type type, QObject *parent)
    : QObject{parent}
{
    m_id=id;
    m_pix=pix;
    m_type=type;


    if(m_type==DynamicPix)
    {
        setPerPixSize(32,32);
        setPerInterval(0,0);
    }


}

PixSource::PixSource(int id, QString pixPath, Type type, QObject *parent): QObject{parent}
{
    m_id=id;
    QPixmap* pix=new QPixmap(pixPath);
    if(!pix->isNull())
    {
        m_pix=pix;
    }
    else
    {
        qDebug()<<"ERROR : PixSource:Path is null!";
    }

    m_type=type;

    if(m_type==DynamicPix)
    {
        setPerPixSize(32,32);
        setPerInterval(0,0);
    }

}

void PixSource::setPerPixSize(int perW, int perH)
{
    m_perW=perW;
    m_perH=perH;
}

void PixSource::setPerInterval(int xInterval, int yInterval)
{
    m_XInterval=xInterval;
    m_YInterval=yInterval;
}

void PixSource::setPixSize(int width, int height)
{
    if(m_pix!=nullptr)
    {
    }
}

int PixSource::getPerW() const
{
    return m_perW;
}

int PixSource::getPerH() const
{
    return m_perH;
}

QPixmap* PixSource::pix() const
{
    return m_pix;
}

PixSource::Type PixSource::type() const
{
    return m_type;
}

QString PixSource::pixStateList() const
{
    return m_pixStateList;
}

void PixSource::setPixStateList(const QString &newPixStateList)
{
    m_pixStateList = newPixStateList;

    //进行分割
    QVector<QString> vector;
    for(auto it:m_pixStateList.split(","))
    {
        vector.append(it);
    }

    setStateList(vector);

}

QString PixSource::pixIndexList() const
{
    return m_pixIndexList;
}

void PixSource::setPixIndexList(const QString &newPixIndexList)
{
    m_pixIndexList = newPixIndexList;

    QVector<QVector<int >> vector;

    for(auto it:newPixIndexList.split("|"))
    {
        QVector<int> var;
        for(auto it2:it.split(","))
        {
            var.append(it2.toInt());
        }
        vector.append(var);
    }

    setStateIndexList(vector);
}

QVector<QString> PixSource::stateList() const
{
    return m_stateList;
}

void PixSource::setStateList(const QVector<QString> &newStateList)
{
    m_stateList = newStateList;
}

QVector<QVector<int> > PixSource::stateIndexList() const
{
    return m_stateIndexList;
}

void PixSource::setStateIndexList(const QVector<QVector<int> > &newStateIndexList)
{
    m_stateIndexList = newStateIndexList;
}

int PixSource::id() const
{
    return m_id;
}

int PixSource::XInterval() const
{
    return m_XInterval;
}

int PixSource::YInterval() const
{
    return m_YInterval;
}
