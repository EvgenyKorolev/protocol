#include "mainwindow.h"
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
#include "settings.h"
#include <QLabel>
#include <QDockWidget>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
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
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
// Приветсвенная запись в логах
    logger &wlog = logger::getInstance();
    wlog.add_log("---===###___+ И вот тебя я запустил и создал главное окно +___###===---");
// Настройка окошка
    this->resize(1000, 800);
    this->setWindowTitle("Создание протоколов измерений " + QString::number(__cplusplus));
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));

// Для представления
    QDockWidget *my_tree_area = new QDockWidget("Клиеты и заявки", this);
    my_tree = new MyTreeView(this);
    TreeModel *my_tree_model = new TreeModel();
    my_tree_area->setWidget(my_tree);
    my_tree_area->setAllowedAreas(Qt::LeftDockWidgetArea);
    my_tree_area->setFeatures(QDockWidget::NoDockWidgetFeatures);
        my_tree_model->headerData(2, Qt::Horizontal);
    my_tree->setModel(my_tree_model);
    addDockWidget(Qt::LeftDockWidgetArea, my_tree_area);

    my_tree_area->setMinimumWidth(450);
    my_tree->setColumnWidth(0, 250);
    my_tree->setColumnWidth(1, 100);
    QWidget *main_l = new QWidget;
    QMainWindow::setCentralWidget(main_l);
// Загрузим клиентов из директории по умолчанию.
    settings& tmpss = settings::GetInstance();
    QDir tmp_dir(tmpss.get_data_patch() + tmpss.get_customers_dir());
    QStringList name_filtr;
    name_filtr << "*.pk" << "*.ppk";
    QStringList tmpl = tmp_dir.entryList(name_filtr, QDir::Files);
    std::transform(tmpl.begin(), tmpl.end(), tmpl.begin(), [&tmp_dir](QString& arg){return tmp_dir.absoluteFilePath(arg);});
    std::vector<QString> files;
    std::copy(tmpl.begin(), tmpl.end(), std::back_inserter(files));
    my_tree->load_klient(files);

// Главное меню
    QMenu * menu_file = new QMenu("&Файл");
    QMenu * menu_about = new QMenu("&Прочее");
    QMenu * menu_options = new QMenu("&Настройки");
    this->menuBar()->addMenu(menu_file);
    this->menuBar()->addMenu(menu_options);
    this->menuBar()->addMenu(menu_about);

//    //============================================
    QAction * act_add_klient = new QAction("Создать клиента", nullptr);
    QAction * act_load_klient = new QAction("Открыть файл клиента", nullptr);
    QAction * act_save_all = new QAction("Сохранить всё", nullptr);
    QAction * act_edit_lab = new QAction("Редактировать данные лаборатории", nullptr);
    QAction * act_about = new QAction("Разработчики", nullptr);
    QAction * act_help = new QAction("Справка", nullptr);
    QAction * act_app_direct = new QAction("Справочник приборов", nullptr);
    QAction * act_edit_const = new QAction("Редактировать текст протоколов", nullptr);
    QAction * act_edit_typs = new QAction("Редактировать константы", nullptr);
    QAction * act_exit = new QAction("Выход", nullptr);

    act_add_klient->setText("Добавить клиента");
    act_add_klient->setToolTip("Добавить клиента");
    act_add_klient->setShortcut(QKeySequence("CTRL+A"));
    act_add_klient->setStatusTip("Добавить клиента");
    act_add_klient->setWhatsThis("Добавить клиента");
    QObject::connect(act_add_klient, SIGNAL(triggered()), SLOT(slot_add_klient()));

    act_load_klient->setText("Открыть файл клиента");
    act_load_klient->setToolTip("Открыть файл клиента");
    act_load_klient->setShortcut(QKeySequence("CTRL+W"));
    act_load_klient->setStatusTip("Открыть файл клиента");
    act_load_klient->setWhatsThis("Открыть файл клиента");
    QObject::connect(act_load_klient, SIGNAL(triggered()), SLOT(slot_open_klient()));

    act_save_all->setText("Сохранить всё");
    act_save_all->setToolTip("Сохранить всё");
    act_save_all->setShortcut(QKeySequence("CTRL+S"));
    act_save_all->setStatusTip("Сохранить всё");
    act_save_all->setWhatsThis("Сохранить всё");
    QObject::connect(act_save_all, SIGNAL(triggered()), SLOT(slot_save_all()));

    act_edit_lab->setText("Редактировать данные лаборатории");
    act_edit_lab->setToolTip("Редактировать данные лаборатории");
    act_edit_lab->setShortcut(QKeySequence("CTRL+L"));
    act_edit_lab->setStatusTip("Редактировать данные лаборатории");
    act_edit_lab->setWhatsThis("Редактировать данные лаборатории");
    QObject::connect(act_edit_lab, SIGNAL(triggered()), SLOT(slot_edit_lab()));

    act_help->setText("Справка");
    act_help->setToolTip("Справка");
    act_help->setShortcut(QKeySequence("CTRL+S"));
    act_help->setStatusTip("Справка");
    act_help->setWhatsThis("Справка");
    connect(act_help, SIGNAL(triggered()), SLOT(slot_help()));

    act_about->setText("Разработчик");
    act_about->setToolTip("Разработчик");
    act_about->setShortcut(QKeySequence("CTRL+A"));
    act_about->setStatusTip("Разработчик");
    act_about->setWhatsThis("Разработчик");
    connect(act_about, SIGNAL(triggered()), SLOT(slot_about()));

    act_app_direct->setText("Справочник приборов");
    act_app_direct->setToolTip("Справочник приборов");
    act_app_direct->setShortcut(QKeySequence("CTRL+K"));
    act_app_direct->setStatusTip("Справочник приборов");
    act_app_direct->setWhatsThis("Справочник приборов");
    connect(act_app_direct, SIGNAL(triggered()), SLOT(slot_app_direct()));

    act_edit_const->setText("Редактировать текст протоколов");
    act_edit_const->setToolTip("Редактировать текст протоколов");
    act_edit_const->setShortcut(QKeySequence("CTRL+O"));
    act_edit_const->setStatusTip("Редактировать текст протоколов");
    act_edit_const->setWhatsThis("Редактировать текст протоколов");
    connect(act_edit_const, SIGNAL(triggered()), SLOT(slot_edit_const()));

    act_edit_typs->setText("Редактировать константы");
    act_edit_typs->setToolTip("Редактировать константы");
    act_edit_typs->setShortcut(QKeySequence("CTRL+C"));
    act_edit_typs->setStatusTip("Редактировать константы");
    act_edit_typs->setWhatsThis("Редактировать константы");
    connect(act_edit_typs, SIGNAL(triggered()), SLOT(slot_edit_typs()));

    act_exit->setText("Выход");
    act_exit->setToolTip("Выход");
    act_exit->setShortcut(QKeySequence("CTRL+T"));
    act_exit->setStatusTip("Выход");
    act_exit->setWhatsThis("Выход");
    connect(act_exit, SIGNAL(triggered()), SLOT(close()));

//    // Добавим действия к меню
    menu_file->addAction(act_add_klient);
    menu_file->addAction(act_load_klient);
    menu_file->addAction(act_save_all);
    menu_file->addAction(act_exit);
    menu_options->addAction(act_edit_lab);
    menu_options->addAction(act_app_direct);
    menu_options->addAction(act_edit_const);
    menu_options->addAction(act_edit_typs);
    menu_about->addAction(act_help);
    menu_about->addAction(act_about);
}
MainWindow::~MainWindow()
{

}
void MainWindow::slot_edit_lab()
{
    editor_laboratory *edlab = new editor_laboratory(this);
    edlab->exec();
    delete edlab;
}
void MainWindow::slot_add_klient()
{
    my_tree->slot_create_klient();
}
void MainWindow::slot_save_all()
{
    my_tree->save_all_klient();
}
void MainWindow::slot_open_klient()
{
    my_tree->slot_load_klient();
}
void MainWindow::slot_about()
{
    QMessageBox *tmoer = new QMessageBox();
    tmoer->setWindowTitle("О Программе");
    tmoer->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    tmoer->setText("<table><tr><th>"
                   "<img src=\":pic/images/KlogoSS.png\"> </th> <th>Протокол 0.1 <br>"
                   "<HTML>Программу разработал Евгений Королев <br>"
                   "Cайт: <a href = 'http://kyrych.ru'>kyrych.ru</a><br> "
                   "E-mail: <a href = 'mailto:root@kyrych.ru'>root@kyrych.ru</a> <br> "
                   "XMPP: kyrych@xmpp.ru"
                   "</th></tr></table>");
    tmoer->exec();
    delete tmoer;
}
void MainWindow::slot_app_direct()
{
    direct_app_listing* app_list = new direct_app_listing();
    if (app_list->exec()){}
    delete app_list;
}
void MainWindow::slot_edit_const()
{
    const_data_listing* const_list = new const_data_listing();
    if (const_list->exec()){}
    delete const_list;
}
void MainWindow::slot_edit_typs()
{
    type_data_listing* ctype_list = new type_data_listing();
    if (ctype_list->exec()){}
    delete ctype_list;
}
void MainWindow::slot_help()
{
    settings& tmpss = settings::GetInstance();
    QWebEngineView* hlp = new QWebEngineView(nullptr);
    hlp->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    hlp->setWindowTitle("Справка программы протокол");
    hlp->setUrl(QUrl("file://" + tmpss.get_data_patch() + tmpss.get_help_dir() + "/main.html"));
    hlp->show();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    close_class* pmbx = new close_class();
    if (pmbx->exec() == QDialog::Accepted)
    {
        if (pmbx->result() == "save"){
            my_tree->save_all_klient();
        }
            event->accept();
            QMainWindow::closeEvent(event);
            return;
    }
    delete pmbx;
    event->ignore();
}
