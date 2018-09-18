#ifndef APP_DATA_MODEL_H
#define APP_DATA_MODEL_H

#include "apparaturs.h"
#include <QAbstractTableModel>
// Модель для отображения списка приборов
class app_data_model : public QAbstractTableModel
{
public:
    app_data_model(QList<apparaturs *> *arg);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

private:
    QList<apparaturs*> *app_list;
};

#endif // APP_DATA_MODEL_H
