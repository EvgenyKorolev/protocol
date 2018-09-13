#include "treemodel.h"

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    root_item_m = new tree_item();
}
TreeModel::~TreeModel()
{
    delete root_item_m;
}
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!this->hasIndex(row, column, parent)) return QModelIndex();

    tree_item *parentItem;

    if (!parent.isValid()) parentItem = this->root_item_m;
    else
        parentItem = static_cast<tree_item*>(parent.internalPointer());

    tree_item *childItem = parentItem->child(row);
    if (childItem != nullptr)
        return this->createIndex(row, column, childItem);
    else
        return QModelIndex();
}
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()) return QModelIndex();

    tree_item *ThisItem = static_cast<tree_item*>(index.internalPointer());
    if (ThisItem->get_status() == "root") return QModelIndex();
    tree_item *parentItem = ThisItem->parent();
    return this->createIndex(ThisItem->row(), 0, parentItem);
}
int TreeModel::rowCount(const QModelIndex &parent) const
{
    tree_item *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = root_item_m;
    else
        parentItem = static_cast<tree_item*>(parent.internalPointer());

    return parentItem->childCount();
}
int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<tree_item*>(parent.internalPointer())->columnCount();
    else
        return root_item_m->columnCount();
}
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (role == Qt::EditRole){
        tree_item *item = static_cast<tree_item*>(index.internalPointer());
        return item->data(0, Qt::EditRole);
    }
    if (role == Qt::DisplayRole) {
     tree_item *item = static_cast<tree_item*>(index.internalPointer());
     return QVariant(item->data(index.column()));
    }
    if (role == Qt::UserRole){
        tree_item *item = static_cast<tree_item*>(index.internalPointer());
        return QVariant(item->data(1, Qt::UserRole));
    }
    return QVariant();
}
QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return root_item_m->data(section, role);

    return QVariant();
}
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
}
bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    const char *c_kli = "klient*";
    const char *c_ord = "order*";
    const char *c_cp = "cp*";
    const char *c_ktp = "ktp*";
    const char *c_prot = "protocol*";
    const char *c_tmp = value.typeName();
    if (role == Qt::EditRole){
        if (strcmp(c_tmp, c_kli) == 0){
            this->root_item_m->create_cild(value.value<klient*>());
            return true;
        }
        if (strcmp(c_tmp, c_ord) == 0){
           index.data(Qt::EditRole).value<tree_item*>()->create_cild(value.value<order*>());
           return true;
        }
        if (strcmp(c_tmp, c_cp) == 0){
                index.data(Qt::EditRole).value<tree_item*>()->create_cild(value.value<cp*>());
                return true;
        }
        if (strcmp(c_tmp, c_ktp) == 0){
                index.data(Qt::EditRole).value<tree_item*>()->create_cild(value.value<ktp*>());
                return true;
        }
        if (strcmp(c_tmp, c_prot) == 0){
            index.data(Qt::EditRole).value<tree_item*>()->create_cild(value.value<protocol*>());
            return true;
        }
    }
    // -=-=-=-=-=-=-=-=-=-=-=++========0-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    return false;
}
bool TreeModel::removeRows( int row, int count, const QModelIndex &parent)
{
    if (parent.isValid()){
        beginRemoveRows(parent, row, row + count -1);
       for (int i = row; i < row + count; i++){
          parent.data(Qt::EditRole).value<tree_item*>()->remove_child(i);
       }
    endRemoveRows();
    this->layoutChanged();
    return true;
    }
    return false;
}
void TreeModel::setupModelData(tree_item *parent)
{
    Q_UNUSED(parent)
}
