#ifndef VER_DATA_VIEW_H
#define VER_DATA_VIEW_H

#include <QObject>
#include <QWidget>
#include <QModelIndex>
#include <QTableView>
#include <QMouseEvent>
#include <QMenu>
#include "ppair_type.h"
#include "ver_editor.h"
// Отображает список номеров и дат поверки прибора
class ver_data_view : public QTableView
{
    Q_OBJECT
public:
    ver_data_view(bool *arg, QWidget *par = nullptr);
    void mousePressEvent(QMouseEvent *arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
public slots:
    void slot_edit();
    void slot_delete();
    void slot_add();
private:
    QPoint curs;
    bool *flag_edit;
};

#endif // VER_DATA_VIEW_H
