#include "my_time_model.h"

my_time_model::my_time_model(QList<QPair<QTime, QTime> > *arg)
{
    this->time_list = arg;
}
int my_time_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->time_list->count();
}
int my_time_model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return 0;
    }
    return 2;
}
QVariant my_time_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && (index.row() <= this->time_list->count())){
        if (role == Qt::DisplayRole){
            switch (index.column()) {
            case 0:
                return QVariant(this->time_list->at(index.row()).first);
            case 1:
                return QVariant(this->time_list->at(index.row()).second);
            }
            return QVariant();
        }
        if (role == Qt::EditRole){
                return QVariant::fromValue(this->time_list->at(index.row()));
            }
            return QVariant();
        }
    return QVariant();
}
bool my_time_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        QPair<QTime, QTime> tmp;
            tmp.first = value.value<pair_type>().first;
            tmp.second = value.value<pair_type>().second;
        if (index.isValid()){
                this->time_list->replace(index.row(), tmp);
                return true;
        } else {
            this->time_list->append(tmp);
            return true;
        }
    }
    return false;
}
QVariant my_time_model::headerData(int section, Qt::Orientation orientation, int role) const
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
                    return QVariant("Начало интервала:");
            case 1:
                    return QVariant("Конец интервала:");
        }
    }
    return QVariant();
}
Qt::ItemFlags my_time_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::NoItemFlags;
    }
    return flags;
}
bool my_time_model::removeRows(int row, int count, const QModelIndex & parent)
{
    this->beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; i++){
        this->time_list->removeAt(row);
     }
     this->endRemoveRows();
     this->layoutChanged();
     return true;
}
