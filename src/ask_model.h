#ifndef ASK_MODEL_H
#define ASK_MODEL_H

#include "pair_type.h"
#include <QAbstractTableModel>
#include <QList>
#include <memory>
// Класс модкели данных для диалога ввода значений недоступных автоматически
class ask_model : public QAbstractTableModel
{
public:
    ask_model(const QList<tuple_qss5>& arg);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
    std::unique_ptr<QList<tuple_qss5>> return_list();

private:
                     //Имя типа  Описание Имя переменной Класс Значение переменной
     //QList<std::tuple<QString, QString, QString, QString, QString>>
    QList<tuple_qss5> ask_set;
};

#endif // ASK_MODEL_H
