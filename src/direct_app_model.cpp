#include "direct_app_model.h"

direct_app_model::direct_app_model() : QAbstractTableModel()
{
}
int direct_app_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return directory_app::getInstance().count();
}
int direct_app_model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return 0;
    }
    return 6;
}
QVariant direct_app_model::data(const QModelIndex &index, int role) const
{
    if (index.isValid()){
        if (role == Qt::DisplayRole){
            switch (index.column()) {
            case 0:
                return QVariant(directory_app::getInstance().at(index.row()).get_name());
            case 1:
                return QVariant(directory_app::getInstance().at(index.row()).get_mdata());
            case 2:
                return QVariant(directory_app::getInstance().at(index.row()).get_type());
            case 3:
                return QVariant(directory_app::getInstance().at(index.row()).get_mnom());
            case 4:
                return QVariant(directory_app::getInstance().at(index.row()).get_clas());
            case 5:
                return QVariant(directory_app::getInstance().at(index.row()).get_real_ver());
            default:
                return QVariant();
            }
        }
        if (role == Qt::EditRole){
            return QVariant::fromValue(directory_app::getInstance().at(index.row()));
        }
        return QVariant();
    }
    return QVariant();
}
bool direct_app_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        if (index.isValid()){
            directory_app::getInstance().replace(index.row(), value.value<apparaturs>());
            return true;
        } else {
            directory_app::getInstance().append(value.value<apparaturs>());
            return true;
        }
    }
    return false;
}
QVariant direct_app_model::headerData(int section, Qt::Orientation orientation, int role) const
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
                    return QVariant("Название:");
            case 1:
                     return QVariant("Дата Выпуска:");
            case 2:
                    return QVariant("Тип:");
            case 3:
                 return QVariant("Заводской №:");
            case 4:
                 return QVariant("Класс точ.:");
            case 5:
                return QVariant("Дата Поверки:");
        }
    }
    return QVariant();
}
Qt::ItemFlags direct_app_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if( index.isValid() ) {
            flags |= Qt::NoItemFlags;
    }
    return flags;
}
bool direct_app_model::removeRows(int row, int count, const QModelIndex & parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; i++){
       directory_app::getInstance().removeAt(row);
     }
     endRemoveRows();
     this->layoutChanged();
     return true;
}
