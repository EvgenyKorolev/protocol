#include "mytreeview.h"
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
#include "protocol_list_load.h"
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
#include "protocol_editor.h"
#include "protocol.h"
#include "settings.h"
#include "protocol_list_load.h"
#include "textedit.h"
#include "jstextedit.h"
#include <QUrl>
#include <QWidget>
#include <QErrorMessage>
#include <QMenu>
#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QEventLoop>
#include <vector>
#include <random>
MyTreeView::MyTreeView(QWidget *par)
{
    this->parent = par;
}
void MyTreeView::mousePressEvent(QMouseEvent *arg)
{
    if (arg->buttons() == Qt::RightButton) {
        QMenu *mnu = new QMenu(this);
        mnu->setEnabled(true);
        QAction *make_klient = new QAction(trUtf8("&Создать клиента"), this);
        QAction *load_klient = new QAction(trUtf8("&Открыть файл клиента"), this);
        mnu->addAction(make_klient);
        mnu->addAction(load_klient);
        QObject::connect(make_klient, SIGNAL(triggered()), this, SLOT(slot_create_klient()));
        QObject::connect(load_klient, SIGNAL(triggered()), this, SLOT(slot_load_klient()));
    if (this->indexAt(arg->pos()).isValid()){
            QVariant temp_v = this->indexAt(arg->pos()).data(Qt::UserRole);
            curs = arg->pos();
            QAction *delete_item = new QAction(trUtf8("Удалить"), this);
            QObject::connect(delete_item, SIGNAL(triggered()), this, SLOT(slot_delete()));
         if (temp_v == "kli"){
             QAction *edit_kli = new QAction(trUtf8("Редактировать клиента"), this);
             mnu->addAction(edit_kli);
             QObject::connect(edit_kli, SIGNAL(triggered()), this, SLOT(slot_edit_klient()));
             QAction *add_order = new QAction(trUtf8("Добавить заявку"), this);
             QObject::connect(add_order, SIGNAL(triggered()), this, SLOT(slot_create_order()));
             mnu->addAction(add_order);
             QAction *save_as = new QAction(trUtf8("Экспортировать клиента"), this);
             QObject::connect(save_as, SIGNAL(triggered()), this, SLOT(slot_save_klient()));
             mnu->addAction(save_as);
             QAction *del_kli = new QAction(trUtf8("Удалить клиента"), this);
             QObject::connect(del_kli, SIGNAL(triggered()), this, SLOT(slot_del_klient()));
             mnu->addAction(del_kli);
             delete_item->setText("Убрать из списка");
             QAction *move_kli = new QAction(trUtf8("Выгрузить клиента"), this);
             QObject::connect(move_kli, SIGNAL(triggered()), this, SLOT(slot_exp_klient()));
             mnu->addAction(move_kli);
            }
         if (temp_v == "ord"){
             QAction *edit_ord = new QAction(trUtf8("Редактировать заявку"), this);
             QObject::connect(edit_ord, SIGNAL(triggered()), this, SLOT(slot_edit_order()));
             mnu->addAction(edit_ord);
             QAction *add_cp = new QAction(trUtf8("Добавить Центр питания"), this);
             QObject::connect(add_cp, SIGNAL(triggered()), this, SLOT(slot_create_cp()));
             mnu->addAction(add_cp);
             QAction *add_ktp = new QAction(trUtf8("Добавить КТП"), this);
             QObject::connect(add_ktp, SIGNAL(triggered()), this, SLOT(slot_create_ktp_ord()));
             mnu->addAction(add_ktp);
             QAction *double_ord = new QAction(trUtf8("Дублировать заявку"), this);
             QObject::connect(double_ord, SIGNAL(triggered()), this, SLOT(slot_clone_order()));
             mnu->addAction(double_ord);
            }
         if (temp_v == "cp"){
             QAction *edit_cp = new QAction(trUtf8("Редактировать ЦП"), this);
             QObject::connect(edit_cp, SIGNAL(triggered()), this, SLOT(slot_edit_cp()));
             mnu->addAction(edit_cp);
             QAction *add_ktp = new QAction(trUtf8("Добавить КТП"), this);
             QObject::connect(add_ktp, SIGNAL(triggered()), this, SLOT(slot_create_ktp()));
             mnu->addAction(add_ktp);
             QAction *add_prot = new QAction(trUtf8("Добавить протокол"), this);
             QObject::connect(add_prot, SIGNAL(triggered()), this, SLOT(slot_create_prot()));
             mnu->addAction(add_prot);
             QAction *double_cp = new QAction(trUtf8("Дублировать ЦП"), this);
             QObject::connect(double_cp, SIGNAL(triggered()), this, SLOT(slot_clone_cp()));
             mnu->addAction(double_cp);
            }
         if(temp_v == "ktp"){
             QAction *edit_ktp = new QAction(trUtf8("Редактировать КТП"), this);
             QObject::connect(edit_ktp, SIGNAL(triggered()), this, SLOT(slot_edit_ktp()));
             mnu->addAction(edit_ktp);
             QAction *add_prot = new QAction(trUtf8("Добавить протокол"), this);
             QObject::connect(add_prot, SIGNAL(triggered()), this, SLOT(slot_create_prot()));
             mnu->addAction(add_prot);
             QAction *double_ktp = new QAction(trUtf8("Дублировать КТП"), this);
             QObject::connect(double_ktp, SIGNAL(triggered()), this, SLOT(slot_clone_ktp()));
             mnu->addAction(double_ktp);
         }
         if(temp_v == "prot"){
             QAction *edit_prot = new QAction(trUtf8("Редактировать протокол"), this);
             QObject::connect(edit_prot, SIGNAL(triggered()), this, SLOT(slot_edit_prot()));
             mnu->addAction(edit_prot);
             QAction *double_prot = new QAction(trUtf8("Дублировать протокол"), this);
             QObject::connect(double_prot, SIGNAL(triggered()), this, SLOT(slot_clone_prot()));
             mnu->addAction(double_prot);
             QAction *txt_prot = new QAction(trUtf8("Текст Протокола"), this);
             QObject::connect(txt_prot, SIGNAL(triggered()), this, SLOT(slot_open_txt()));
             mnu->addAction(txt_prot);
             QAction *js_prot = new QAction(trUtf8("JS редактор протокола"), this);
             QObject::connect(js_prot, SIGNAL(triggered()), this, SLOT(slot_open_jseditor()));
             mnu->addAction(js_prot);
         }
            mnu->addAction(delete_item);
    }
    mnu->popup(arg->globalPos());
    mnu->show();
   }
    else QTreeView::mousePressEvent(arg);
}
void MyTreeView::slot_clone_order()
{
    fab_order fabord;
    order *cre_order = fabord.create();
    if (this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_o() != nullptr){
        cre_order->init_new(*(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_o()));
    }
    this->indexAt(curs).parent().data(Qt::EditRole).value<tree_item*>()->create_cild(cre_order);
    model()->layoutChanged();
}
void MyTreeView::slot_clone_cp()
{
    fab_obj fabcp;
    obj *cre_cp = fabcp.create_cp();
    cre_cp->init_new(*(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_c()));
    this->indexAt(curs).parent().data(Qt::EditRole).value<tree_item*>()->create_cild(cre_cp);
    model()->layoutChanged();
}
void MyTreeView::slot_clone_ktp()
{
    fab_obj fabcp;
    obj *cre_ktp = fabcp.create_ktp();
    cre_ktp->init_new(*(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_ktp()));
    this->indexAt(curs).parent().data(Qt::EditRole).value<tree_item*>()->create_cild(cre_ktp);
    model()->layoutChanged();
}
void MyTreeView::slot_delete()
{
    QVariant temp_v = this->indexAt(curs).data(Qt::UserRole);
    QString txxt;
    if (temp_v == "kli"){
        txxt = "<b>Вы точно хотите убрать клиента из списка: " + this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_name();
      }
    if (temp_v == "ord"){
        txxt = "<b>Вы точно хотите удалить заявку: " + this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_o()->get_uniq();
    }
    if (temp_v == "cp"){
        txxt = "<b>Вы точно хотите удалить центр: питания " + this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_c()->get_name();
    }
    if(temp_v == "ktp"){
        txxt = "<b>Вы точно хотите удалить КТП: " + this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_ktp()->get_name();
    }
    if(temp_v == "prot"){
        txxt = "<b>Вы точно хотите удалить протокол:";
    }
    yes_no* pmbx = new yes_no(txxt + "?</b>");
    if (pmbx->exec() == QDialog::Accepted)
    {
        if(temp_v == "prot"){
            this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_prot()->erase();
        }
        model()->removeRow(this->indexAt(curs).row(),this->indexAt(curs).parent());
        model()->layoutChanged();
    }
    delete pmbx;
}
void MyTreeView::edit_klient(klient *arg)
{
    klient tmp_klient = *arg;
    editor_klient *editor = new editor_klient(&tmp_klient, this->parent);
    if (editor->exec() == QDialog::Accepted){
    *arg = tmp_klient;
    }
    delete editor;
}
void MyTreeView::edit_order(order *arg)
{
    order tmp_order = *arg;
    editor_order *editor = new editor_order(&tmp_order, this->parent);
    if (editor->exec() == QDialog::Accepted){
        *arg = tmp_order;
    }
    delete editor;
}
void MyTreeView::edit_cp(cp *arg)
{
    cp tmp_cp = *arg;
    editor_cp *editor = new editor_cp(&tmp_cp, this->parent);
    if (editor->exec() == QDialog::Accepted){
        *arg = tmp_cp;
    }
    delete editor;
}
void MyTreeView::edit_ktp(ktp *arg)
{
    ktp tmp_ktp = *arg;
    editor_ktp *editor = new editor_ktp(&tmp_ktp, this->parent);
    if (editor->exec() == QDialog::Accepted){
        *arg = tmp_ktp;
    }
    delete editor;
}
void MyTreeView::slot_create_klient()
{
    fab_klient fabkl;
    klient *cre_klient = fabkl.create_new();
    if (cre_klient == nullptr) return;
    editor_klient *editor = new editor_klient(cre_klient);
    editor->edited();
    if (editor->exec() == QDialog::Accepted && editor->is_edit()){
        QString tmpname = cre_klient->get_fname();
        if (tmpname.right(4) == ".ppk"){
            tmpname = tmpname.left(tmpname.size() - 3) + "db3";
        } else if (tmpname.right(3) == ".pk"){
            tmpname = tmpname.left(tmpname.size() - 2) + "db3";
        } else tmpname += ".db3";
       cre_klient->set_pdirname(tmpname);
       save_klient::save_xml(cre_klient, cre_klient->get_patch() + "/" + cre_klient->get_fname());
       prt_fun::create_base(cre_klient->get_patch(), tmpname);
       int i = model()->rowCount();
       model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(cre_klient), Qt::EditRole);
       model()->layoutChanged();
    }
    delete editor;
}
void MyTreeView::slot_create_order()
{
    order *cre_order = new order(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k());
    editor_order *editor = new editor_order(cre_order);
    if (editor->exec() == QDialog::Accepted){
        model()->setData(this->indexAt(curs), QVariant::fromValue(cre_order), Qt::EditRole);
        model()->layoutChanged();
    }
}
void MyTreeView::slot_create_cp()
{
    cp *cre_cp = new cp(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_o());
    editor_cp *editor = new editor_cp(cre_cp);
    if (editor->exec() == QDialog::Accepted && editor->is_edit()){
        model()->setData(this->indexAt(curs), QVariant::fromValue(cre_cp), Qt::EditRole);
        model()->layoutChanged();
    }
}
void MyTreeView::slot_create_ktp()
{
    ktp *cre_ktp = new ktp();
    cre_ktp->set_up(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_c());
    editor_ktp *editor = new editor_ktp(cre_ktp);
    if (editor->exec() == QDialog::Accepted && editor->is_edit()){
        model()->setData(this->indexAt(curs), QVariant::fromValue(cre_ktp), Qt::EditRole);
        model()->layoutChanged();
    }
}
void MyTreeView::slot_create_ktp_ord()
{
    ktp *cre_ktp = new ktp();
    cre_ktp->set_up(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_o());
    editor_ktp *editor = new editor_ktp(cre_ktp);
    if (editor->exec() == QDialog::Accepted && editor->is_edit()){
        model()->setData(this->indexAt(curs), QVariant::fromValue(cre_ktp), Qt::EditRole);
        model()->layoutChanged();
    }
}
void MyTreeView::slot_edit_klient()
{
   klient *edkli = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k();
   if (edkli == nullptr) return;
   editor_klient *editor = new editor_klient(edkli);
   if (editor->exec() == QDialog::Accepted && editor->is_edit()){
       model()->layoutChanged();
   }
   delete editor;
}
void MyTreeView::slot_edit_order()
{
    order *edord = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_o();
    if (edord == nullptr) return;
    editor_order *editor = new editor_order(edord);
    if (editor->exec() == QDialog::Accepted){
        model()->layoutChanged();
    }
    delete editor;
}
void MyTreeView::slot_save_klient()
{
    save_klient sv;
    QString my_file = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_patch() + "/" + this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_fname();
    do{
    my_file = QFileDialog::getSaveFileName(this->parent, tr("Сохранить как"), my_file);
    } while ((!sv.save_xml(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k(), my_file) && (my_file == "")));
    if (my_file != ""){
        QString my_patch = my_file.left(my_file.lastIndexOf("/"));
        QString my_name = my_file.right(my_file.size() - my_file.lastIndexOf("/") - 1);
        this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->set_fname(my_name);
        if (my_name.right(4) == ".ppk"){
            my_name = my_name.left(my_name.size() - 3) + "db3";
        } else if (my_name.right(3) == ".pk"){
            my_name = my_name.left(my_name.size() - 2) + "db3";
        } else my_name += ".db3";
        sv.save_db(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k(), my_patch + "/" + my_name);
        this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->set_pdirname(my_name);
        this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->set_patch(my_patch);
        prt_fun::erase_lost_protocols(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k());
    }
}
void MyTreeView::slot_load_klient()
{
    QString my_file = "";
    my_file = QFileDialog::getOpenFileName(this->parent, tr("Открыть файл клиента"));
    fab_klient fabr_kli;
    if (my_file != ""){
        open_klient opn;
        klient *ret = fabr_kli.create();
        ret->init(opn.load(my_file));
        ret->set_patch(my_file.left(my_file.lastIndexOf("/")));
        int i{0};
        i = model()->rowCount();
       model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(ret), Qt::EditRole);
       model()->layoutChanged();
    }
}
void MyTreeView::load_klient(std::vector<QString>& arg)
{
    open_klient opn;
    int i{model()->rowCount()};
    for (auto it : arg) {
        klient *ret = opn.load(it);
        ret->set_patch(it.left(it.lastIndexOf("/")));
        model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(ret), Qt::EditRole);
        ++i;
    }
}
void MyTreeView::save_all_klient()
{
    settings& tmpss = settings::GetInstance();
    QDir tmp_dir(tmpss.get_data_patch() + tmpss.get_customers_dir());
    save_klient sv;
    QString abs_path = tmpss.get_data_patch() + tmpss.get_customers_dir();
    QString my_file{""};
    std::random_device gensc;
    std::mt19937 gen;
    gen.seed(gensc());
    int n{model()->rowCount()};
    for (int i{0}; i < n; ++i){
       my_file = model()->data(model()->index(i, 0, QModelIndex()), Qt::EditRole).value<tree_item*>()->ret_k()->get_patch() + "/" + model()->data(model()->index(i, 0, QModelIndex()), Qt::EditRole).value<tree_item*>()->ret_k()->get_fname();
       if (my_file == ""){
           my_file = abs_path + "/autoname_" + QString::number(gen()) + "_" +
                   model()->data(model()->index(i, 0, QModelIndex()), Qt::EditRole).value<tree_item*>()->ret_k()->get_name() + ".ppk";
       }
       sv.save_xml(model()->data(model()->index(i, 0, QModelIndex()), Qt::EditRole).value<tree_item*>()->ret_k(), my_file);
       prt_fun::erase_lost_protocols(model()->data(model()->index(i, 0, QModelIndex()), Qt::EditRole).value<tree_item*>()->ret_k());
    }
}
void MyTreeView::slot_exp_klient()
{
    save_klient sv;
    QString my_file = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_patch() + "/" + this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_fname();
    do{
    my_file = QFileDialog::getSaveFileName(this->parent, tr("Выгрузить(переместить) в:"), my_file);
    } while ((!sv.save_xml(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k(), my_file) && (my_file == "")));
    if (my_file != ""){
        QString my_patch = my_file.left(my_file.lastIndexOf("/"));
        QString my_name = my_file.right(my_file.size() - my_file.lastIndexOf("/") - 1);
        QString tmp_name = my_name;
        if (my_name.right(4) == ".ppk"){
            my_name = my_name.left(my_name.size() - 3) + "db3";
        } else if (my_name.right(3) == ".pk"){
            my_name = my_name.left(my_name.size() - 2) + "db3";
        } else my_name += ".db3";
        sv.save_db(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k(), my_patch + "/" + my_name);
        QString del_patch = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_patch() + "/" + this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_fname();
        QString del_dpatch = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_patch() + "/" + this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_pdirname();
        QFile(del_patch).remove();
        QFile(del_dpatch).remove();
        this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->set_fname(tmp_name);
        this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->set_pdirname(my_name);
        this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->set_patch(my_patch);
    }
}
void MyTreeView::slot_edit_cp()
{
    obj *edcp = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_c();
    editor_cp *editor = new editor_cp(edcp);
    if (editor->exec() == QDialog::Accepted && editor->is_edit()){
        model()->layoutChanged();
    }
    delete editor;
}
void MyTreeView::slot_edit_ktp()
{
    obj *edktp = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_ktp();
    editor_ktp *editor = new editor_ktp(edktp);
    if (editor->exec() == QDialog::Accepted && editor->is_edit()){
        model()->layoutChanged();
    }
    delete editor;
}
void MyTreeView::slot_create_prot(){
    obj* tmpo;
    QVariant temp_v = this->indexAt(curs).data(Qt::UserRole);
    if (temp_v == "cp"){
        tmpo = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_c();
    } else if (temp_v == "ktp"){
        tmpo = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_ktp();
    } else if(temp_v == "prot"){
       tmpo = nullptr;
    } else tmpo = nullptr;
    if (tmpo != nullptr){
        protocol* prt = new protocol(tmpo);
        protocol_constructor *prtconst = new protocol_constructor(prt);
        if (prtconst->exec() == QDialog::Accepted){
            model()->setData(this->indexAt(curs), QVariant::fromValue(prt), Qt::EditRole);
            model()->layoutChanged();
        }
        delete prtconst;
    } else {
        QMessageBox::information(nullptr, "Отладка", "Не получается найти родительский объект при создании протокола.<br><br> Сообщите об этом разработчикам");
    }
    tmpo = nullptr;
    }
void MyTreeView::slot_del_klient()
{
    yes_no* pmbx = new yes_no("<b>Вы точно хотите удалить клиента: " + this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_name() + "?</b>");
    if (pmbx->exec() == QDialog::Accepted)
    {
        QString patch = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_patch() + "/" + this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_fname();
        QString dpatch = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_patch() + "/" + this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_pdirname();
        model()->removeRow(this->indexAt(curs).row(),this->indexAt(curs).parent());
        model()->layoutChanged();
        QFile(patch).remove();
        QFile(dpatch).remove();
    }
};
void MyTreeView::slot_edit_prot()
{
    protocol* edprt = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_prot();
    if (edprt == nullptr) return;
    protocol_editor *editor = new protocol_editor(edprt);
    if (editor->exec() == QDialog::Accepted){
    }
    delete editor;
    model()->layoutChanged();
}
void MyTreeView::slot_clone_prot()
{
    protocol* prt = new protocol(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_prot()->get_parent());
    prt->set_number(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_prot()->get_number());
    prt->set_date(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_prot()->get_date());
    prt->set_type(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_prot()->get_type());
    prt_fun::add_prt(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_prot()->get_dr(), prt,
                     this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_prot()->get_prttxt(),
                     this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_prot()->get_endtxt());
    model()->setData(this->indexAt(curs).parent(), QVariant::fromValue(prt), Qt::EditRole);
    model()->layoutChanged();
}
void MyTreeView::slot_open_txt()
{
    ret_str ret;
    TextEdit *prtedit = new TextEdit(&ret, this);
    prtedit->load_html(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_prot()->get_endtxt());
    prtedit->resize(1024, 768);
    prtedit->show();
    QEventLoop loop;
    connect(prtedit, SIGNAL(svexit()), &loop, SLOT(quit()));
    loop.exec();
    this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_prot()->set_endtxt(ret.result());
    delete prtedit;
}
void MyTreeView::slot_open_jseditor()
{
            QUrl url;
            url = QUrl("/ckeditor/editor.html");
            JStextedit *browser = new JStextedit(url);
            browser->resize(1024, 768);
            browser->show();
}
