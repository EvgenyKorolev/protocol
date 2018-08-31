#include "ask_model.h"

ask_model::ask_model(const QList<tuple_qss5> &arg) : QAbstractTableModel ()
{
    ask_set = arg;
}
int ask_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->ask_set.count();
}
int ask_model::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()){
        return 0;
    }
    return 2;
}
QVariant ask_model::data(const QModelIndex &index, int role) const
{
                      //Имя типа Описание Имя переменной Класс Значение
     //QList<std::tuple<QString, QString, QString, QString, QString>>
    if (index.isValid()){
        if (role == Qt::DisplayRole){
            switch (index.column()) {
            case 0:
                return QVariant(std::get<2>(this->ask_set.at(index.row())));
            case 1:
                return QVariant(std::get<4>(this->ask_set.at(index.row())));
            default:
                return QVariant();
            }
        }
        if (role == Qt::EditRole){
            return QVariant::fromValue(this->ask_set.at(index.row()));
        }
        return QVariant();
    }
    return QVariant();
}
bool ask_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole){
        if (index.isValid()){
            this->ask_set.replace(index.row(), value.value<tuple_qss5>());
            return true;
        } else {
            this->ask_set.append(value.value<tuple_qss5>());
            return true;
        }
    } else if (role == Qt::UserRole){
        if (index.isValid()){
            std::get<4>(this->ask_set[index.row()]) = value.value<QString>();
            return true;
        }
    }
    return false;
}
QVariant ask_model::headerData(int section, Qt::Orientation orientation, int role) const
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
                     return QVariant("Описание переменной:");
            case 1:
                    return QVariant("Введите значение:");
        }
    }
    return QVariant();
}
Qt::ItemFlags ask_model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if( index.isValid() ) {
        if (index.column() == 1){
            flags |= Qt::ItemIsEditable;
        } else {
           flags |= Qt::NoItemFlags;
        }
    }
    return flags;
}
bool ask_model::removeRows(int row, int count, const QModelIndex & parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = row; i < row + count; i++){
        this->ask_set.removeAt(row);
     }
     endRemoveRows();
     this->layoutChanged();
     return true;
}
