#ifndef DIRECT_APP_MODEL_H
#define DIRECT_APP_MODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "apparaturs.h"
#include "directory_app.h"
// Модель для отображения справочника приборов
class direct_app_model : public QAbstractTableModel
{
public:
    direct_app_model();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
};

#endif // DIRECT_APP_MODEL_H
