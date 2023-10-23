#include "myitemmodel.h"

#include <qmimedata.h>

MyItemModel::MyItemModel(QObject *parent)
    : QStandardItemModel(parent)
{
}

Qt::ItemFlags MyItemModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags=QAbstractItemModel::flags(index);
    flags=flags|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled;
    return flags;
}

QMimeData *MyItemModel::mimeData(const QModelIndexList &indexes) const
{
    if(indexes.count()<=0) return nullptr;
    QMimeData *data = new QMimeData;
    data->setData("drag","鼠标拖拽");
    data->setData("name",QStandardItemModel::item(indexes.at(0).row(),0)->text().toLocal8Bit());
    data->setData("score",item(indexes.at(0).row(),1)->text().toLocal8Bit());
return data;
}

bool MyItemModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    QString st=QString::fromLocal8Bit(data->data("name"));
    QString st1=QString::fromLocal8Bit(data->data("score"));

    this->setItem(m_rowCount,0,new QStandardItem(st));
    this->setItem(m_rowCount,1,new QStandardItem(st1));
    m_rowCount++;
    return true;
}


QStringList MyItemModel::mimeTypes() const
{
    QStringList types;
    types << "drag";
    return types;

}
