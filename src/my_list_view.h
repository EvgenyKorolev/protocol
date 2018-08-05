#ifndef MY_LIST_VIEW_H
#define MY_LIST_VIEW_H

#include <QObject>
#include <QWidget>
#include <QListView>
#include <QMouseEvent>
#include <QMenu>
#include <QDialog>
#include <QAbstractItemView>
#include "string_edit.h"
// Представление для отображения списка строк
class my_list_view : public QListView
{
    Q_OBJECT
public:
    my_list_view(bool *arg, QWidget *par);
    void mousePressEvent(QMouseEvent * arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
public slots:
    void slot_edit();
    void slot_delete();
    void slot_add();

private:
    QPoint curs;
    bool *flag_edit;
};

#endif // MY_LIST_VIEW_H
