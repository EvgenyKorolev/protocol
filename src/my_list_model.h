#ifndef MY_LIST_MODEL_H
#define MY_LIST_MODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>
#include <QString>
// Модель для отображения списка строк (Для телефонов использыется и факсов, но для любых строк подходит)
class my_list_model : public QAbstractListModel
{
    Q_OBJECT
public:
    my_list_model(QList<QString> *arg);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void appendLine(const QString& data);
    bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

private:
    QList<QString> *the_data;
};
#endif // MY_LIST_MODEL_H
