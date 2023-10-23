#ifndef MYITEMMODEL_H
#define MYITEMMODEL_H

#include <QAbstractItemModel>
#include <QStandardItemModel>

class MyItemModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit MyItemModel(QObject *parent = nullptr);

    //实现拖动功能
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;

    //实现拽入功能
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    QStringList mimeTypes() const override;

private:
    int m_rowCount=0;
};

#endif // MYITEMMODEL_H
