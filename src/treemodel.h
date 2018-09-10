#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QVariant>
#include <cstring>
#include "treeitem.h"
// Модель данных для главного дерева
class TreeModel : public QAbstractItemModel
{

    Q_OBJECT

public:
    TreeModel(QObject *parent = nullptr);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    void append_data(tree_item *arg);
    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

private:
    void setupModelData(tree_item *parent);

    tree_item *root_item_m;
};

#endif // TREEMODEL_H
