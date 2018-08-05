#ifndef VER_DATA_MODEL_H
#define VER_DATA_MODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QList>
#include <QPair>
#include <QDate>
#include <QString>
#include "ppair_type.h"
// Модель для отображения списка дат поверок прибора
class ver_data_model : public QAbstractTableModel
{
public:
    ver_data_model(QList<QPair<QPair<QString, QDate>, QDate>> *arg);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
private:
    QList<QPair<QPair<QString, QDate>, QDate>> *ver_list;
};

#endif // VER_DATA_MODEL_H
