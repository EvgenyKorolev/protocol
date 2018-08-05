#include "type_data_model.h"

type_data_model::type_data_model(type_obj& arg)
{
    data_list = arg;
}
void type_data_model::set_source_data(type_obj &arg)
{
    data_list = arg;
}
type_obj type_data_model::return_data() const
{
    return data_list;
}
int type_data_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return data_list.count();
}
int type_data_model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return 0;
    }
    return 4;
}
QVariant type_data_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid()){
        int i{index.row()};
        if (role == Qt::DisplayRole){
               // 1. НАЗВАНИЕ 2. СОДЕРЖАНИЕ 3. ИМЯ ПЕРЕМЕННОЙ */
            QString ret_str;
            switch (index.column()) {
            case 0:
                return QVariant(std::get<0>(data_list.at(i)));
                break;
            case 1:
                if (std::get<1>(data_list.at(i)) == "dig"){
                    ret_str = "число";
                } else if (std::get<1>(data_list.at(i)) == "str"){
                    ret_str = "строка";
                }
                return QVariant(ret_str);
                break;
            case 2:
                return QVariant(std::get<2>(data_list.at(i)));
                break;
            case 3:
                return QVariant(std::get<3>(data_list.at(i)));
                break;
            default:
                return QVariant();
            }
        }
        if (role == Qt::EditRole){
            tuple_type_s ret = std::make_tuple(std::get<0>(data_list.at(i)), std::get<1>(data_list.at(i)), std::get<2>(data_list.at(i)), std::get<3>(data_list.at(i)), i);
            return QVariant::fromValue(ret);
        }
        return QVariant();
    }
    return QVariant();
}
bool type_data_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        tuple_type_s tmpt = value.value<tuple_type_s>();
        std::tuple<QString, QString, QString, QString> tmp = std::make_tuple(std::get<0>(tmpt), std::get<1>(tmpt), std::get<2>(tmpt), std::get<3>(tmpt));
        if (index.isValid()){
            data_list.replace(std::get<4>(tmpt), tmp);
            return true;
        } else {
            data_list.append(tmp);
            return true;
        }
    }
    return false;
}
QVariant type_data_model::headerData(int section, Qt::Orientation orientation, int role) const
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
                    return QVariant("Имя:");
            break;
            case 1:
                    return QVariant("Тип:");
            break;
            case 2:
                     return QVariant("Описание:");
            break;
            case 3:
                    return QVariant("Значение:");
            break;
        }
    }
    return QVariant();
}
Qt::ItemFlags type_data_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::NoItemFlags;
    }
    return flags;
}
bool type_data_model::removeRows(int row, int count, const QModelIndex & parent)
{
    if (row + count - 1 > data_list.count()) return false;
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; i++){
        data_list.removeAt(row);
     }
     endRemoveRows();
     this->layoutChanged();
     return true;
}
