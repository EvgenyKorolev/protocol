#ifndef MY_TIME_MODEL_H
#define MY_TIME_MODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QList>
#include <QPair>
#include <QTime>
#include "pair_type.h"
// Модель для отображения списка дат
class my_time_model : public QAbstractTableModel
{
public:
    my_time_model(QList<QPair<QTime, QTime>> *arg);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
private:
    QList<QPair<QTime, QTime>> *time_list;
};

#endif // MY_TIME_MODEL_H
