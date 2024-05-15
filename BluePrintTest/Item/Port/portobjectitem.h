#ifndef PORTOBJECTITEM_H
#define PORTOBJECTITEM_H

#include "qcolor.h"

#include <QObject>
#include <QRect>
#include <QSet>
#include <QVariant>

class NodeObjectItem;
class PortObjectItem : public QObject
{
public:

    //端口类型
    //=========================待更新=============================
    //后续需要改为    连接类型link/data   和  流类型  in/out
    //=========================待更新=============================
    enum PortType{
        NoneType,
        Input,
        Output,
        InLink,
        OutLink
    };

    //端口数据类型
    enum PortDataType{
        NoneDataType,
        Int,
        Bool,
        String,
        Double,
        Float,
    };
private:
    Q_OBJECT

    Q_PROPERTY(unsigned int portId READ portId WRITE setPortId NOTIFY portIdChanged)
    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)
    Q_PROPERTY(QVariant portValue READ portValue WRITE setPortValue NOTIFY portValueChanged)
    Q_PROPERTY(QString portTip READ portTip WRITE setPortTip NOTIFY portTipChanged)
    Q_PROPERTY(PortType portType READ portType WRITE setPortType NOTIFY portTypeChanged)
    Q_PROPERTY(PortDataType portDataType READ portDataType WRITE setPortDataType NOTIFY portDataTypeChanged)


public:
    static QColor getColorByDataType(PortObjectItem::PortDataType type);

public:
    explicit PortObjectItem(QObject *parent = nullptr);
    //void initPort(QString name,PortType type,QSet<PortDataType> assertdataType);
    void initPort(QString name,PortType type,PortDataType dataType);
    void addDataType(PortDataType dataType);


    unsigned int portId() const;
    void setPortId(unsigned int newPortId);

    QString portName() const;
    void setPortName(const QString &newPortName);

    QVariant portValue() const;
    void setPortValue(const QVariant &newPortValue);

    QString portTip() const;
    void setPortTip(const QString &newPortTip);

    NodeObjectItem *linkNode() const;
    void setLinkNode(NodeObjectItem *newLinkNode);

    PortObjectItem::PortType portType() const;
    void setPortType(PortType newPortType);

    bool linkPortState() const;
    void setLinkPortState(bool newLinkPortState);

    QRect portRect() const;
    void setPortRect(QRect newPortRect);

    PortObjectItem::PortDataType portDataType() const;
    void setPortDataType(PortDataType newPortDataType);

    PortObjectItem *linkPort() const;
    void setLinkPort(PortObjectItem *newLinkPort);

protected:
    QSet<PortDataType> m_assertDataTypeSet;

    unsigned int m_portId;
    QString m_portName;
    QVariant m_portValue;
    QString m_portTip;
    PortType m_portType;
    PortDataType m_portDataType;

private:
    static QMap<PortObjectItem::PortDataType,QColor> m_typeColorDictionary;
    static QMultiMap<PortObjectItem::PortDataType,PortObjectItem::PortDataType> m_assertDataTypeDictionary;
private:
    //数据准备状态
    bool m_dataState;
    NodeObjectItem * m_linkNode=nullptr;
    PortObjectItem * m_linkPort=nullptr;

    bool m_linkPortState;

    QRect m_portRect;





signals:

    void portIdChanged();
    void portNameChanged();
    void portValueChanged();
    void portTipChanged();
    void portTypeChanged();
    void portDataTypeChanged();
};

#endif // PORTOBJECTITEM_H
