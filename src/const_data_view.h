#ifndef CONST_DATA_VIEW_H
#define CONST_DATA_VIEW_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QMouseEvent>
#include <QMenu>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <tuple>
#include "const_data_editor.h"
#include "pair_type.h"

// Представление списка констант протокола (константы это тексты разных абзацев)
class const_data_view : public QTableView
{
    Q_OBJECT
public:
    const_data_view(QSortFilterProxyModel* arg, QWidget *par = nullptr);
    void mousePressEvent(QMouseEvent * arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
public slots:
    void slot_edit();  // Редактировать
    void slot_delete();// Удалить
    void slot_add();   // Добавить
signals:
    void signal_new();
private:
    QPoint _curs;   // Позиция курора
    QSortFilterProxyModel* pat_mod;
};

#endif // CONST_DATA_VIEW_H
