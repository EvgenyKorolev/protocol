#include "mytreeview.h"

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
        QAction *load_klient = new QAction(trUtf8("&Загрузить клиента"), this);
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
             QAction *save_as = new QAction(trUtf8("Сохранить клиента"), this);
             QObject::connect(save_as, SIGNAL(triggered()), this, SLOT(slot_save_klient()));
             mnu->addAction(save_as);
             QAction *del_kli = new QAction(trUtf8("Удалить клиента"), this);
             QObject::connect(del_kli, SIGNAL(triggered()), this, SLOT(slot_del_klient()));
             mnu->addAction(del_kli);
             delete_item->setText("Убрать из списка");
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
    cre_order->init(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_o());
    this->indexAt(curs).parent().data(Qt::EditRole).value<tree_item*>()->create_cild(cre_order);
    model()->layoutChanged();
}
void MyTreeView::slot_clone_cp()
{
    fab_obj fabcp;
    obj *cre_cp = fabcp.create_cp();
    cre_cp->init(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_c());
    this->indexAt(curs).parent().data(Qt::EditRole).value<tree_item*>()->create_cild(cre_cp);
    model()->layoutChanged();
}
void MyTreeView::slot_clone_ktp()
{
    fab_obj fabcp;
    obj *cre_ktp = fabcp.create_ktp();
    cre_ktp->init(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_ktp());
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
    klient *cre_klient = new klient();
    editor_klient *editor = new editor_klient(cre_klient);
    if (editor->exec() == QDialog::Accepted && editor->is_edit()){
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
   editor_klient *editor = new editor_klient(edkli);
   if (editor->exec() == QDialog::Accepted && editor->is_edit()){
       model()->layoutChanged();
   }
   delete editor;
}
void MyTreeView::slot_edit_order()
{
    order *edord = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_o();
    editor_order *editor = new editor_order(edord);
    if (editor->exec() == QDialog::Accepted){
        model()->layoutChanged();
    }
    delete editor;
}
void MyTreeView::slot_save_klient()
{
    save_klient sv;
    QString my_file = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_patch();
    do{
    my_file = QFileDialog::getSaveFileName(this->parent, tr("Сохранить как"), my_file);
    } while ((!sv.save(this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k(), my_file) && (my_file == "")));
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
        ret->set_patch(my_file);
        int i = 0;
        i = model()->rowCount();
       model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(ret), Qt::EditRole);
       model()->layoutChanged();
    }
}
void MyTreeView::load_klient(std::vector<QString>& arg)
{
    fab_klient fabr_kli;
    open_klient opn;
    int i{model()->rowCount()};
    for (auto it : arg) {
        klient *ret = opn.load(it);
        ret->set_patch(it);
        model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(ret), Qt::EditRole);
        ++i;
    }
}
void MyTreeView::save_all_klient()
{
    QDir tmp_dir("customers");
    save_klient sv;
    QString abs_path = tmp_dir.absolutePath();
    QString my_file{""};
    std::random_device gensc;
    std::mt19937 gen;
    gen.seed(gensc());
    int n{model()->rowCount()};
    for (int i{0}; i < n; ++i){
       my_file = model()->data(model()->index(i, 0, QModelIndex()), Qt::EditRole).value<tree_item*>()->ret_k()->get_patch();
       if (my_file == ""){
           my_file = abs_path + "/autoname_" + QString::number(gen()) + "_" +
                   model()->data(model()->index(i, 0, QModelIndex()), Qt::EditRole).value<tree_item*>()->ret_k()->get_name() + ".ppk";
       }
       sv.save(model()->data(model()->index(i, 0, QModelIndex()), Qt::EditRole).value<tree_item*>()->ret_k(), my_file);

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
       tmpo = nullptr; // tmpo = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_prot();
    } else tmpo = nullptr;
    if (tmpo != nullptr){
        protocol* prt = new protocol(tmpo);
        protocol_constructor *prtconst = new protocol_constructor(prt);
        if (prtconst->exec() == QDialog::Accepted){
         // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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
        QString patch = this->indexAt(curs).data(Qt::EditRole).value<tree_item*>()->ret_k()->get_patch();
        model()->removeRow(this->indexAt(curs).row(),this->indexAt(curs).parent());
        model()->layoutChanged();
        QFile(patch).remove();
    }
};
void MyTreeView::slot_edit_prot(){;}
void MyTreeView::slot_clone_prot(){;}
