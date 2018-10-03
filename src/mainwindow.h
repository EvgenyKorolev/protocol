#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class MyTreeView;
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
    void slot_save_all();
    void slot_about();
    void slot_app_direct();
    void slot_edit_const();
    void slot_edit_typs();
    void slot_help();
    void slot_opt();
    void closeEvent(QCloseEvent *event);
private:
    QWidget *main_l;
    MyTreeView *my_tree;
};

#endif // MAINWINDOW_H
