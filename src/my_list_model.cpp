#include "my_list_model.h"

my_list_model::my_list_model(QList<QString> *arg)
{
    this->the_data = arg;
}
int my_list_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return the_data->count();
}
int my_list_model::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}
QVariant my_list_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && (index.row() <= this->the_data->size())){
        if (role == Qt::DisplayRole){
            return QVariant(this->the_data->at(index.row()));
        }
        if (role == Qt::EditRole){
            return QVariant(this->the_data->at(index.row()));
        }
    }
    return QVariant();
}
bool my_list_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        if (index.isValid()){
                this->the_data->replace(index.row(), value.toString());       
        } else {
            this->the_data->append(value.toString());
        }
    }
    return false;
}
QVariant my_list_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation)
    Q_UNUSED(section)
    if (role != Qt::DisplayRole){
        return QVariant();
    }
    return QVariant();
}
Qt::ItemFlags my_list_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractListModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::NoItemFlags;
    }
    return flags;
}
void my_list_model::appendLine(const QString& data)
{
    Q_UNUSED(data)
}
bool my_list_model::removeRows( int row, int count, const QModelIndex &parent)
{
   beginRemoveRows(parent, row, row + count -1);
   for (int i = row; i < row + count; i++){
       the_data->removeAt(row);
    }
    endRemoveRows();
    this->layoutChanged();
    return true;
}
