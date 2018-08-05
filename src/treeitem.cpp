#include "treeitem.h"
// -=-=-=-=-=-=-=-=-=-=-=- Вопрос с добавлением родителей в разные заявки и ЦП КТП при их добавлении как дочерних элиментов открыт.
tree_item::tree_item(klient *data, tree_item *parent)
{
    child_items = QList<tree_item*>();
    this->set_kli(data);
    this->parent_item = parent;
    if (!this->parent_item->is_child(this)) {this->parent_item->add_chaild(this);}
}
tree_item::tree_item(order *data, tree_item *parent)
{
    child_items = QList<tree_item*>();
    this->set_ord(data);
    this->parent_item = parent;
    if (!this->parent_item->is_child(this)) {this->parent_item->add_chaild(this);}
}
tree_item::tree_item(obj *data, tree_item *parent)
{
    if (data->get_status() == "cp"){
        child_items = QList<tree_item*>();
        this->set_cp(data);
        this->parent_item = parent;
        if (!this->parent_item->is_child(this)) {this->parent_item->add_chaild(this);}
    }
    if (data->get_status() == "ktp"){
        child_items = QList<tree_item*>();
        this->set_ktp(data);
        this->parent_item = parent;
        if (!this->parent_item->is_child(this)) {this->parent_item->add_chaild(this);}
    }
}
tree_item::tree_item(cp *data, tree_item *parent)
{
    child_items = QList<tree_item*>();
    this->set_cp(data);
    this->parent_item = parent;
    if (!this->parent_item->is_child(this)) {this->parent_item->add_chaild(this);}
}
tree_item::tree_item(ktp *data, tree_item *parent)
{
    child_items = QList<tree_item*>();
    this->set_ktp(data);
    this->parent_item = parent;
    if (!this->parent_item->is_child(this)) {this->parent_item->add_chaild(this);}
}
tree_item::tree_item()
 {
      if (this->type == "NULL" || this->type == "root" || this->type == "") {
          this->type = "root";
          this->parent_item = nullptr;
          this->child_items = QList<tree_item*>();
          this->item_data_k = nullptr;
          this->item_data_o = nullptr;
          this->item_data_c = nullptr;
          this->item_data_ktp = nullptr;
          this->item_data_prot = nullptr;
      }
 }
tree_item::tree_item(QString arg)
{
    Q_UNUSED(arg)
    child_items = QList<tree_item*>();
        this->type = "NULL";
        this->parent_item = nullptr;
        QList<tree_item*> tmp;
        this->child_items = tmp;
        this->item_data_k = nullptr;
        this->item_data_o = nullptr;
        this->item_data_c = nullptr;
        this->item_data_ktp = nullptr;
        this->item_data_prot = nullptr;
}
tree_item::~tree_item()
{
        QList<tree_item*>::iterator start = this->child_items.begin();
    while (start != this->child_items.end()) {
        (*start)->~tree_item();
        start++;
    }
    while (this->child_items.size() > 0){
        this->child_items.removeLast();
    }
    child_items.clear();
    if (this->type == "kli") {
        delete this->item_data_k;
        this->type = "NULL";
    }
    if (this->type == "ord") {
        delete this->item_data_o;
        this->type = "NULL";
    }
    if (this->type == "cp") {
        delete this->item_data_c;
        this->type = "NULL";
    }
    if (this->type == "ktp") {
        delete this->item_data_ktp;
        this->type = "NULL";
    }
    if (this->type == "prot") {
       // item_data_prot->~protocol();
        this->type = "NULL";
    }
}
int tree_item::appendChild(tree_item *item)
{
    if (!(this->child_items.contains(item)) || (item->get_status() != "ktp") || (item->parent() == this)){
    this->child_items.append(item);
    item->set_parent(this);
    return 0;
    }
    else return 1;
}
tree_item *tree_item::child(int row)
{
    if (row <= this->child_items.count() || row >= 0) {
    return this->child_items.value(row);
    }
    return nullptr;
}
int tree_item::childCount() const
{
    return child_items.count();
}
int tree_item::row() const
{
     if (this->parent_item != nullptr || this->type != "root"){
        return parent_item->child_items.indexOf(const_cast<tree_item*>(this));
        }
    return 0;
}
int tree_item::columnCount() const
{
   // Количество колонок
    return 2;
}
QVariant tree_item::data(int section, int role)
{
  if (role == Qt::DisplayRole){
    if (this->type == "kli") {
        switch (section){
            case 0:
                return QVariant(this->item_data_k->get_name());
            case 1:
                return QVariant("");
            case 2:
                return QVariant("");
        }
    }
    if (this->type == "ord") {
        switch (section){
        case 0:
            return QVariant(this->item_data_o->get_uniq());
        case 1:
            return QVariant(this->item_data_o->get_date().toString("dd.MM.yyyy"));
        case 2:
            return QVariant(QString::number(this->item_data_o->get_num()));
        }
    }
    if (this->type == "cp") {
        switch (section){
        case 0:
            return QVariant(this->item_data_c->get_name());
        case 1:
            return QVariant("ЦП");
        case 2:
            return QVariant("");
        }
    }
    if (this->type == "ktp") {
        switch (section) {
        case 0:
            return QVariant(this->item_data_ktp->get_name());
        case 1:
            return QVariant("КТП");
        case 2:
            return QVariant("");

        }
    }
    if (this->type == "root"){
      switch (section){
        case 0:
            return QVariant("Наименование");
        case 1:
            return QVariant("Дата");
        case 2:
            return QVariant("Статус");
      }
    }
    if (this->type == "prot") {
        switch (section) {
        case 0:
            return QVariant("Тип");
        case 1:
            return QVariant("Дата");
        case 2:
            return QVariant("Номер");

        }
    }
    return QVariant("errX");
   }
   if (role == Qt::EditRole){
       return QVariant::fromValue<tree_item*>(this);
   }
   if (role == Qt::UserRole){
     if (this->type == "kli") {
                 return QVariant("kli");
     }
     if (this->type == "ord") {
             return QVariant("ord");
     }
     if (this->type == "cp") {
             return QVariant("cp");
     }
     if (this->type == "ktp") {
             return QVariant("ktp");
     }
     if (this->type == "root"){
         return QVariant("root");
     }
     if (this->type == "prot"){
         return QVariant("prot");
     }
     return QVariant("errX");
    }
   return QVariant("errX");
}
tree_item *tree_item::parent()
{
    if (this->type != "root") {return this->parent_item;}
    return nullptr;
}
int tree_item::set_parent(tree_item *item)
{
    this->parent_item = item;
    return 0;
}
int tree_item::add_chaild(tree_item *item)
{
    if (!(this->child_items.contains(item)) || (item->parent() == this)){

            if (item->get_status() == "kli" && this->get_status() == "root"){
               this->child_items.append(item);
            }
            if (item->get_status() == "ord" && this->get_status() == "kli"){
                this->ret_k()->add_orders(item->ret_o());
                this->child_items.append(item);
            }
            if (item->get_status() == "cp" && this->get_status() == "ord"){
                this->ret_o()->add_obj(item->ret_c());
                this->child_items.append(item);
            }
            if (item->get_status() == "ktp" && (get_status() == "ord")){
                this->ret_o()->add_obj(item->ret_ktp());
                this->child_items.append(item);
            }
            if (item->get_status() == "ktp" && (get_status() == "cp")){
                this->ret_c()->add_ktp(item->ret_ktp());
                this->child_items.append(item);
            }
            if (item->get_status() == "prot" && ((get_status() == "ktp") || (item->get_status() == "cp"))){
                this->child_items.append(item);
            }
        return 0;
    }
    return 1;
}
QString tree_item::get_status()
{
    return this->type;
}
int tree_item::create_cild(klient* arg)
{
    tree_item * itm = new tree_item(arg, this);
    Q_UNUSED(itm)
    return 0;
}
int tree_item::create_cild(order* arg)
{
    tree_item * itm = new tree_item(arg, this);
    Q_UNUSED(itm)
    return 0;
}
int tree_item::create_cild(cp* arg)
{
    tree_item * itm = new tree_item(arg, this);
    Q_UNUSED(itm)
    return 0;
}
int tree_item::create_cild(ktp* arg)
{
    tree_item * itm = new tree_item(arg, this);
    Q_UNUSED(itm)
    return 0;
}
int tree_item::create_cild(obj* arg)
{
    tree_item * itm = new tree_item(arg, this);
    Q_UNUSED(itm)
    return 0;
}
bool tree_item::is_child(tree_item *item)
{
    return this->child_items.contains(item);
}
bool tree_item::setData(QVariant &value)
{
    const char *c_kli = "klient*";
    const char *c_ord = "order*";
    const char *c_cp = "cp*";
    const char *c_ktp = "ktp*";
    const char *c_prot = "protocol*";
    const char *c_tmp = value.typeName();

        if (strcmp(c_tmp, c_kli) == 0){
               this->set_kli(value.value<klient*>());
               return true;
        }
        if (strcmp(c_tmp, c_ord) == 0){
            this->set_ord(value.value<order*>());
            return true;
        }
        if (strcmp(c_tmp, c_cp) == 0){
            this->set_cp(value.value<cp*>());
            return true;
        }
        if (strcmp(c_tmp, c_ktp) == 0){
            this->set_ktp(value.value<ktp*>());
            return true;
        }
        if (strcmp(c_tmp, c_prot) == 0){
        }
        return false;
}
void tree_item::set_kli(klient *data)
{
    this->item_data_k = data;
    if (this->type == "NULL" || this->type == "kli" || this->type == "") {this->type = "kli";}
    else {this->type = "err1";}
    QList<order*> tmpo = data->get_order_list();
    if (tmpo.size() > 0) {
        fab_item fabit;
        QList<order*>::iterator it = tmpo.begin();
        while (it != tmpo.end()) {
            tree_item* tmp = fabit.create();
            tmp->set_ord(&(*it[0]));
            tmp->set_parent(this);
            this->child_items.append(tmp);
            ++it;
        }
    }
}
void tree_item::set_ord(order *data)
{
    this->item_data_o = data;
    if (this->type == "NULL" || this->type == "ord" || this->type == "") {this->type = "ord";}
    else {this->type = "err2";}
    QList<obj*> tmpo = data->get_obj_list();
    if (tmpo.size() > 0) {
            fab_item fabit;
        QList<obj*>::iterator it = tmpo.begin();
        while (it != tmpo.end()) {
            tree_item* tmp = fabit.create();
            tmp->set_obj(&(*it[0]));
            tmp->set_parent(this);
            this->child_items.append(tmp);
            ++it;
        }
    }
}
void tree_item::set_cp(cp *data)
{
    this->item_data_c = data;
    if (this->type == "NULL" || this->type == "cp" || this->type == "") {this->type = "cp";}
    else {this->type = "err3";}
    QList<obj*> tmpo = data->get_ktp_list();
    if (tmpo.size() > 0) {
        fab_item fabit;
        QList<obj*>::iterator it = tmpo.begin();
        while (it != tmpo.end()) {
            tree_item* tmp = fabit.create();
            tmp->set_ktp(&(*it[0]));
            tmp->set_parent(this);
            this->child_items.append(tmp);
            ++it;
        }
    }
}
void tree_item::set_ktp(ktp *data)
{
    this->item_data_ktp = data;
    if (data->get_up() != nullptr) {this->item_data_ktp->set_up(data->get_up());}
    if (data->get_ups() != nullptr) {this->item_data_ktp->set_up(data->get_ups());}
    if (this->type == "NULL" || this->type == "ktp" || this->type == "") {this->type = "ktp";}
    else {this->type = "err4";}
}
bool tree_item::remove_child(int row)
{
  if (!child_items.isEmpty()) {
    if (0 <= row && row < child_items.size()) {
      child_items.at(row)->~tree_item();
      child_items.removeAt(row);
      return true;
    }
  }
  return false;
}
void tree_item::set_cp(obj *data)
{
    this->item_data_c = data;
    if (this->type == "NULL" || this->type == "cp" || this->type == "") {this->type = "cp";}
    else {this->type = "err3";}
    QList<obj*> tmpo = data->get_ktp_list();
    if (tmpo.size() > 0) {
        fab_item fabit;
        QList<obj*>::iterator it = tmpo.begin();
        while (it != tmpo.end()) {
            tree_item* tmp = fabit.create();
            tmp->set_ktp(&(*it[0]));
            tmp->set_parent(this);
            this->child_items.append(tmp);
            ++it;
        }
    }
}
void tree_item::set_ktp(obj *data)
{
    this->item_data_ktp = data;
    if (this->type == "NULL" || this->type == "ktp" || this->type == "") {this->type = "ktp";}
    else {this->type = "err4";}
}
void tree_item::set_obj(obj* data)
{
    if (data->type() == "cp"){
        this->set_cp(data);
    }
    if (data->type() == "ktp"){
        this->set_ktp(data);
    }

}
bool tree_item::is_child_at(int row)
{
    if (row <= this->child_items.size()) {return true;}
    return false;
}
int tree_item::chaild_nom(tree_item *item)
{
    return this->child_items.indexOf(item);
}
void tree_item::set_prot(protocol *data)
{
    Q_UNUSED(data)
}
klient* tree_item::ret_k()
{
    if (this->type == "kli"){
        return this->item_data_k;
    }
    return nullptr;
}
order* tree_item::ret_o()
{
    if (this->type == "ord"){
        return this->item_data_o;
    }
    return nullptr;
}
obj* tree_item::ret_c()
{
    if (this->type == "cp"){
        return this->item_data_c;
    }
    return nullptr;
}
obj* tree_item::ret_ktp()
{
    if (this->type == "ktp"){
        return this->item_data_ktp;
    }
    return nullptr;
}
protocol* tree_item::ret_prot()
{
    if (this->type == "prot"){
        return this->item_data_prot;
    }
    return nullptr;
}
