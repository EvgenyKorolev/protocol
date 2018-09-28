#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QObject>
#include <QTreeView>
#include <QMouseEvent>
class klient;
class order;
class cp;
class ktp;
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

    void slot_exp_klient();
    void slot_open_txt();
    void slot_open_jseditor();
private:
    QWidget * parent;
    QPoint curs;
};

#endif // MYTREEVIEW_H
