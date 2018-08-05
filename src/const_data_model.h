#ifndef CONST_DATA_MODEL_H
#define CONST_DATA_MODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <QPair>
#include "pair_type.h"
#include "const_obj.h"

// Модель даных для представления списка констант протокола (константы это тексты разных абзацев)
class const_data_model : public QAbstractTableModel
{
public:
    const_data_model(const_obj &arg);
    void set_source_data(const_obj &arg);
    const_obj return_data() const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

private:
    // Описание абзаца, Содержание абзаца, Имя переменной
    const_obj _data_list;
};

#endif // CONST_DATA_MODEL_H
