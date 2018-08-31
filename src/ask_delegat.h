#ifndef ASK_DELEGAT_H
#define ASK_DELEGAT_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QString>
// Делегат для редактирования значений в списке переменных
class ask_delegat : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ask_delegat(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // ASK_DELEGAT_H
