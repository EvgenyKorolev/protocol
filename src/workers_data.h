#ifndef WORKERS_DATA_H
#define WORKERS_DATA_H

#include <QAbstractTableModel>
#include <QList>
#include <QVariant>
#include <QModelIndex>
#include <QString>
#include "worker.h"

class workers_data : public QAbstractTableModel
{
public:
    workers_data(QList<worker> *arg);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
private:
    QList<worker> *work_list;
};

#endif // WORKERS_DATA_H
