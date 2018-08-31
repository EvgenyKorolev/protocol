#ifndef ASK_EDITOR_H
#define ASK_EDITOR_H

#include "ask_delegat.h"
#include "ask_model.h"
#include "ask_view.h"
#include <QObject>
#include <QDialog>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QHeaderView>

// Класс запрашивает для ввода список значений
class ask_editor : public QDialog
{
    Q_OBJECT
public:
    ask_editor(const QList<tuple_qss5> &arg);
    ~ask_editor();
public slots:
    void slot_ok();
private:
    ask_model* data_model;
    ask_view* data_view;
    QSortFilterProxyModel* proxy_mod{new QSortFilterProxyModel()};
};

#endif // ASK_EDITOR_H
