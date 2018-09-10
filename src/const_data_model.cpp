#include "const_data_model.h"

const_data_model::const_data_model(const_obj& arg)
{
    _data_list = arg;
}
void const_data_model::set_source_data(const_obj &arg)
{
    _data_list = arg;
}
int const_data_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _data_list.count();
}
int const_data_model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return 0;
    }
    return 3;
}
QVariant const_data_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid()){
        int i{index.row()};
        if (role == Qt::DisplayRole){
               // 1. ИМЯ ПЕРЕМЕННОЙ 2. описание 3. текст */
            switch (index.column()) {
            case 0:
                return QVariant(_data_list.at(i).second);
            case 1:
                return QVariant(_data_list.at(i).first.first);
            case 2:
                return QVariant(_data_list.at(i).first.second);
            default:
                return QVariant();
            }
        }
        if (role == Qt::EditRole){
            tuple_type ret = std::make_tuple(_data_list.at(i).second, _data_list.at(i).first.first, _data_list.at(i).first.second, i);
            return QVariant::fromValue(ret);
        }
        return QVariant();
    }
    return QVariant();
}
bool const_data_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        QPair<QPair<QString, QString>, QString> tmp;
        tuple_type tmpt = value.value<tuple_type>();
        tmp.first.first = std::get<1>(tmpt);
        tmp.first.second = std::get<2>(tmpt);
        tmp.second = std::get<0>(tmpt);
        if (index.isValid()){
            _data_list.replace(std::get<3>(tmpt), tmp);
            return true;
        } else {
            _data_list.append(tmp);
            return true;
        }
    }
    return false;
}
QVariant const_data_model::headerData(int section, Qt::Orientation orientation, int role) const
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
                    return QVariant("Переменная:");
            case 1:
                     return QVariant("Описание:");
            case 2:
                    return QVariant("Текст:");
        }
    }
    return QVariant();
}
Qt::ItemFlags const_data_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::NoItemFlags;
    }
    return flags;
}
bool const_data_model::removeRows(int row, int count, const QModelIndex & parent)
{
    if (row + count > _data_list.count()) return false;
    beginRemoveRows(parent, row, row + count);
    for (int i = row; i < row + count - 1; i++){
        _data_list.removeAt(row);
     }
     endRemoveRows();
     this->layoutChanged();
     return true;
}
const_obj const_data_model::return_data() const
{
    return _data_list;
}
