#ifndef P_TYPES_MODEL_H
#define P_TYPES_MODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QString>
#include <QList>
#include <tuple>
#include "pair_type.h"

class p_types_model : public QAbstractTableModel
{
public:
    p_types_model();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
private:
    // Имя типа (чеоловекочитаемое) Описание Имя переменной
    QList<std::tuple<QString, QString, QString>> mdata;
};

#endif // P_TYPES_MODEL_H
