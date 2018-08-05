#include "app_data_model.h"

app_data_model::app_data_model(QList<apparaturs *> *arg)
{
    app_list = arg;
}
int app_data_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->app_list->count();
}
int app_data_model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return 0;
    }
    return 3;
}
QVariant app_data_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid()){
        if (role == Qt::DisplayRole){
            switch (index.column()) {
            case 0:
                return QVariant(this->app_list->at(index.row())->get_name());
                break;
            case 1:
                return QVariant(this->app_list->at(index.row())->get_type());
                break;
            case 2:
                return QVariant(this->app_list->at(index.row())->get_mnom());
                break;
            default:
                return QVariant();
            }
        }
        if (role == Qt::EditRole){
            return QVariant::fromValue(this->app_list->at(index.row()));
        }
        return QVariant();
    }
    return QVariant();
}
bool app_data_model::app_data_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        if (index.isValid()){
            this->app_list->replace(index.row(), value.value<apparaturs*>());
            return true;
        } else {
            this->app_list->append(value.value<apparaturs*>());
            return true;
        }
    }
    return false;
}
QVariant app_data_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole){
        return QVariant();
    }
    if (orientation != Qt::Horizontal){
        return QVariant();
    }
    else {
        switch (section){
            case 0:
                    return QVariant("Приборы:");
            break;
            case 1:
                     return QVariant("Тип прибора:");
            break;
            case 2:
                    return QVariant("Заводской номер:");
            break;
        }
    }
    return QVariant();
}
Qt::ItemFlags app_data_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::NoItemFlags;
    }
    return flags;
}
bool app_data_model::removeRows(int row, int count, const QModelIndex & parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; i++){
        this->app_list->removeAt(row);
     }
     endRemoveRows();
     this->layoutChanged();
     return true;
}
