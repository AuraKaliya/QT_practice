#include "myproxymodel.h"

#include <QMimeData>
#include <QStandardItemModel>

MyProxyModel::MyProxyModel(QObject *parent)
    : QAbstractProxyModel {parent}
{

}

QModelIndex MyProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    // 将代理模型索引映射到底层模型的索引
    if (proxyIndex.isValid()) {
        return sourceModel()->index(proxyIndex.row() , proxyIndex.column());
    }
    return QModelIndex();
}

QModelIndex MyProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    // 将底层模型的索引映射到代理模型的索引
    if (sourceIndex.isValid()) {
        return index(sourceIndex.row(), sourceIndex.column());
    }
    return QModelIndex();
}

QModelIndex MyProxyModel::index(int row, int column, const QModelIndex &parent) const
{
    // 创建代理模型的索引
    if (row >= 0 && column >= 0 && row < rowCount(parent) && column < columnCount(parent)) {
        return createIndex(row, column);
    }
    return QModelIndex();
}

QModelIndex MyProxyModel::parent(const QModelIndex &child) const
{
    // 返回代理模型中的根节点索引
    return QModelIndex();
}

int MyProxyModel::rowCount(const QModelIndex &parent) const
{
    // 返回代理模型的行数
    if (parent.isValid())
        return 0;
    return sourceModel()->rowCount() ;
}

int MyProxyModel::columnCount(const QModelIndex &parent) const
{
    // 返回代理模型的行数
    if (parent.isValid())
        return 0;
    return sourceModel()->rowCount();
}


