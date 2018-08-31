#include "ask_delegat.h"

ask_delegat::ask_delegat(QObject *parent) : QStyledItemDelegate(parent)
{
}
QWidget* ask_delegat::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option); Q_UNUSED(index);
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}
void ask_delegat::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lined = static_cast<QLineEdit*>(editor);
    lined->setText(value);
}
void ask_delegat::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lined = static_cast<QLineEdit*>(editor);
    QString value = lined->text();
    model->setData(index, value, Qt::UserRole);
}
void ask_delegat::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
