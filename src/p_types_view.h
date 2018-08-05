#ifndef P_TYPES_VIEW_H
#define P_TYPES_VIEW_H

#include <QObject>
#include <QObject>
#include <QWidget>
#include <QAbstractItemView>
#include <QTableView>
#include <QMouseEvent>
#include <QMenu>
#include <QString>
#include <QVariant>
#include <tuple>
#include "type_in_direct.h"

// Вид для отображения таблицы выбранных типов констант для протокола
class p_types_view : public QTableView
{
    Q_OBJECT
public:
    p_types_view(QWidget *par = nullptr);
    void mousePressEvent(QMouseEvent * arg);
//    void mouseDoubleClickEvent(QMouseEvent* arg);
//    void set_edit(bool arg = true);
//    bool is_edit();
public slots:
//    void slot_edit();
    void slot_delete();
    void slot_add();
private:
    QPoint curs;
};

#endif // P_TYPES_VIEW_H
