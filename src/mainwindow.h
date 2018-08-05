#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include "direct_app_listing.h"
#include "const_data_listing.h"
#include "type_data_listing.h"
#include "close_class.h"
#include <QLabel>
#include <QDockWidget>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>
#include <QBoxLayout>
#include <QTreeView>
#include <QDir>
#include <algorithm>
#include "treemodel.h"
#include "treeitem.h"
#include "logger.h"
#include "mytreeview.h"
#include <QKeySequence>
#include <QMessageBox>
#include <QHeaderView>
#include <QWebEngineView>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void slot_edit_lab();
    void slot_add_klient();
    void slot_open_klient();
    void slot_about();
    void slot_app_direct();
    void slot_edit_const();
    void slot_edit_typs();
    void slot_help();
    void closeEvent(QCloseEvent *event);
private:
    QWidget *main_l;
    MyTreeView *my_tree;
};

#endif // MAINWINDOW_H
