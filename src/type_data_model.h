#ifndef TYPE_DATA_MODEL_H
#define TYPE_DATA_MODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <tuple>
#include "type_obj.h"
#include "pair_type.h"

class type_data_model : public QAbstractTableModel
{
public:
    type_data_model(type_obj &arg);
    void set_source_data(type_obj &arg);
    type_obj return_data() const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

private:
    type_obj data_list;
};

#endif // TYPE_DATA_MODEL_H
