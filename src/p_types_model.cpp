#include "p_types_model.h"

p_types_model::p_types_model()
{

}
int p_types_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->mdata.count();
}
int p_types_model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return 0;
    }
    return 2;
}
QVariant p_types_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && (index.row() <= this->mdata.count())){
        if (role == Qt::DisplayRole){
            switch (index.column()) {
            case 0:
                return QVariant(std::get<0>(this->mdata.at(index.row())));
            case 1:
                return QVariant(std::get<1>(this->mdata.at(index.row())));
            }
            return QVariant();
        }
        if (role == Qt::EditRole){
                return QVariant::fromValue(this->mdata.at(index.row()));
            }
            return QVariant();
        }
    return QVariant();
}
bool p_types_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        std::tuple<QString, QString, QString> tmp{std::make_tuple(std::get<0>(value.value<tuple_qss>()), std::get<1>(value.value<tuple_qss>()), std::get<2>(value.value<tuple_qss>()))};
        if (index.isValid()){
                this->mdata.replace(index.row(), tmp);
                return true;
        } else {
            this->mdata.append(tmp);
            return true;
        }
    }
    return false;
}
QVariant p_types_model::headerData(int section, Qt::Orientation orientation, int role) const
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
                    return QVariant("Название набора:");
            case 1:
                    return QVariant("Описание:");
        }
    }
    return QVariant();
}
Qt::ItemFlags p_types_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::NoItemFlags;
    }
    return flags;
}
bool p_types_model::removeRows(int row, int count, const QModelIndex & parent)
{
    this->beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; i++){
        this->mdata.removeAt(row);
     }
     this->endRemoveRows();
     this->layoutChanged();
     return true;
}
