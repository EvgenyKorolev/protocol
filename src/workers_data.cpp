#include "workers_data.h"

workers_data::workers_data(QList<worker> *arg)
{
    this->work_list = arg;
}
int workers_data::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->work_list->count();
}
int workers_data::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return 0;
    }
    return 4;
}
QVariant workers_data::data(const QModelIndex &index, int role) const
{
    if (index.isValid()){
        if (role == Qt::DisplayRole){
            switch (index.column()) {
            case 0:
                return QVariant(this->work_list->at(index.row()).get_surname());
            case 1:
                return QVariant(this->work_list->at(index.row()).get_name());
            case 2:
                return QVariant(this->work_list->at(index.row()).get_fname());
            case 3:
                return QVariant(this->work_list->at(index.row()).get_position());
            default:
                return QVariant();
            }
        }
        if (role == Qt::EditRole){
            return QVariant::fromValue(this->work_list->at(index.row()));
        }
        return QVariant();
    }
    return QVariant();
}
bool workers_data::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        if (index.isValid()){
            this->work_list->replace(index.row(), value.value<worker>());
            return true;
        } else {
            this->work_list->append(value.value<worker>());
            return true;
        }
    }
    return false;
}
QVariant workers_data::headerData(int section, Qt::Orientation orientation, int role) const
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
                    return QVariant("Фамилия");
            case 1:
                     return QVariant("Имя");
            case 2:
                    return QVariant("Отчество");
            case 3:
                    return QVariant("Должность");
        }
    }
    return QVariant();
}
Qt::ItemFlags workers_data::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::NoItemFlags;
    }
    return flags;
}

bool workers_data::removeRows(int row, int count, const QModelIndex & parent)
{
    beginRemoveRows(parent, row, row + count +1);
    for (int i = row; i < row + count; i++){
        this->work_list->removeAt(row);
    }
    endRemoveRows();
    this->layoutChanged();
    return true;
}
