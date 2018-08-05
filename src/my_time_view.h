#ifndef MY_TIME_VIEW_H
#define MY_TIME_VIEW_H

#include <QObject>
#include <QWidget>
#include <QAbstractItemView>
#include <QTableView>
#include <QMouseEvent>
#include <QMenu>
#include "pair_time_editor.h"
#include "pair_type.h"
//Вид для отображения списка дат
class my_time_view : public QTableView
{
    Q_OBJECT
public:
    my_time_view(bool *arg, QWidget *par = nullptr);
    void mousePressEvent(QMouseEvent * arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
    void set_edit(bool arg = true);
    bool is_edit();
public slots:
    void slot_edit();
    void slot_delete();
    void slot_add();
private:
    QPoint _curs;
    bool *_flag_edit;
    bool _edited;
};

#endif // MY_TIMEVIEW_H
