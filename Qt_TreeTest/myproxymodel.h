#ifndef MYPROXYMODEL_H
#define MYPROXYMODEL_H

#include <QObject>


#include <QAbstractProxyModel>


class MyProxyModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    explicit MyProxyModel(QObject *parent = nullptr);

    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override ;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override ;


private:
    int m_rowCount;
signals:

};

#endif // MYPROXYMODEL_H
