#ifndef WORKERS_VIEW_H
#define WORKERS_VIEW_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QMouseEvent>
#include <QMenu>
#include <QVariant>
#include "worker.h"
#include "editor_worker.h"

class workers_view : public QTableView
{
    Q_OBJECT
public:
    workers_view(bool *arg, QWidget *par = nullptr);
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

#endif // WORKERS_VIEW_H
