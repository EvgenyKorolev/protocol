#ifndef TYPE_DATA_VIEW_H
#define TYPE_DATA_VIEW_H

#include <QObject>
#include <QTableView>
#include <QMouseEvent>
#include <QMenu>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include "pair_type.h"
#include "type_data_editor.h"

class type_data_view : public QTableView
{
    Q_OBJECT
public:
    type_data_view(QSortFilterProxyModel* arg, QWidget *par = nullptr);
    void mousePressEvent(QMouseEvent * arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
public slots:
    void slot_edit();  // Редактировать
    void slot_delete();// Удалить
    void slot_add();   // Добавить
private:
    QPoint _curs;   // Позиция курора
    QSortFilterProxyModel* pat_mod;
};

#endif // TYPE_DATA_VIEW_H
