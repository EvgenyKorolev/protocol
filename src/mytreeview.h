#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H
#include <QWidget>
#include <QErrorMessage>
#include <QTreeView>
#include <QMouseEvent>
#include <QMenu>
#include <QObject>
#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <vector>
#include <random>
#include "treeitem.h"
#include "treemodel.h"
#include "address.h"
#include "worker.h"
#include "laboratory.h"
#include "details.h"
#include "klient.h"
#include "order.h"
#include "cp.h"
#include "ktp.h"
#include "editor_address.h"
#include "editor_cp.h"
#include "editor_klient.h"
#include "editor_ktp.h"
#include "editor_laboratory.h"
#include "editor_order.h"
#include "editor_worker.h"
#include "save_klient.h"
#include "open_klient.h"
#include "fab_klient.h"
#include "fab_order.h"
#include "yes_no.h"
#include "protocol_constructor.h"
#include "protocol.h"
// Представление для отображения главного дерева
class MyTreeView : public QTreeView
{
    Q_OBJECT
public:
    MyTreeView(QWidget * par);
    void mousePressEvent(QMouseEvent * arg);

    void edit_klient(klient *arg);
    void edit_order(order *arg);
    void edit_cp(cp *arg);
    void edit_ktp(ktp *arg);
    void load_klient(std::vector<QString>& arg);
    void save_all_klient();
public slots:
    void slot_delete();
    void slot_del_klient();

    void slot_edit_klient();
    void slot_edit_order();
    void slot_edit_cp();
    void slot_edit_ktp();
    void slot_edit_prot();

    void slot_create_klient();
    void slot_create_order();
    void slot_create_cp();
    void slot_create_ktp();
    void slot_create_ktp_ord();
    void slot_create_prot();

    void slot_save_klient();
    void slot_load_klient();

    void slot_clone_order();
    void slot_clone_cp();
    void slot_clone_ktp();
    void slot_clone_prot();
private:
    QWidget * parent;
    QPoint curs;
};

#endif // MYTREEVIEW_H
