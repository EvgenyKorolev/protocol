#include "ver_data_model.h"

ver_data_model::ver_data_model(QList<QPair<QPair<QString, QDate>, QDate> > *arg)
{
    this->ver_list = arg;
}
int ver_data_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->ver_list->count();
}
int ver_data_model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return 0;
    }
    return 3;
}
QVariant ver_data_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && (index.row() <= this->ver_list->count())){
        if (role == Qt::DisplayRole){
            switch (index.column()) {
            case 0:
                return QVariant(this->ver_list->at(index.row()).first.first);
            case 1:
                return QVariant(this->ver_list->at(index.row()).first.second);
            case 2:
                return QVariant(this->ver_list->at(index.row()).second);
            }
        }
        if (role == Qt::EditRole){
            return QVariant::fromValue(this->ver_list->at(index.row()));
        }
    }
    return QVariant();
}
bool ver_data_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        QPair<QPair<QString, QDate>, QDate> tmp;
        tmp.first.first = value.value<ppair_type>().first.first;
        tmp.first.second = value.value<ppair_type>().first.second;
        tmp.second = value.value<ppair_type>().second;
        if (index.isValid()){
            this->ver_list->replace(index.row(), tmp);
            return true;
        } else {
            this->ver_list->append(tmp);
            return true;
        }
    }
    return false;
}
QVariant ver_data_model::headerData(int section, Qt::Orientation orientation, int role) const
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
            return QVariant("Свидетельство о поверке №");
        case 1:
            return QVariant("Дата поверки");
        case 2:
            return QVariant("Дата следующей поверки");
        }
    }
    return QVariant();
}
Qt::ItemFlags ver_data_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::NoItemFlags;
    }
    return flags;
}
bool ver_data_model::removeRows(int row, int count, const QModelIndex & parent)
{
    this->beginRemoveRows(parent, row, row + count -1);
    for (int i = row; i < row + count; i++){
        this->ver_list->removeAt(row);
    }
    this->endRemoveRows();
    this->layoutChanged();
    return true;
}
