#ifndef DIRECT_APP_VIEW_H
#define DIRECT_APP_VIEW_H

#include <QObject>
#include <QTableView>
#include <QMouseEvent>
#include <QMenu>
#include <QSortFilterProxyModel>
#include "app_editor.h"
#include "app_data_model.h"
#include "direct_app_listing.h"
class direct_app_listing;
class direct_app_view : public QTableView
{
    Q_OBJECT
public:
    direct_app_view(QWidget *par = nullptr);
    virtual void mousePressEvent(QMouseEvent* arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
public slots:
    void slot_edit();
    void slot_delete();
    void slot_add();
    virtual void set_pather(direct_app_listing* arg);
private:
    QPoint _curs;
    direct_app_listing* _pather;
};

#endif // DIRECT_APP_VIEW_H
