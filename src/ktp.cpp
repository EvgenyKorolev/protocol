#include "ktp.h"
#include "order.h"
ktp::ktp() : obj()
{
    this->up = nullptr;
    this->ups = nullptr;
}
ktp::ktp(obj *arg)
{
    this->name = arg->get_name();
    QList<protocol*>tmp_prt = arg->get_pro_list();
    QList<protocol*>::iterator it1 = tmp_prt.begin();
    while (it1 != tmp_prt.end()){
        this->p_list.append(*it1);
        ++it1;
    }
    this->adr = arg->get_adr();
    this->sh = arg->get_sh();
    this->status = arg->get_status();
    this->max_time = arg->get_maxt_list();
    this->min_time = arg->get_mint_list();
    this->voltage = arg->get_voltage();
    QList<apparaturs*> tmp_app = arg->get_app_list();
    QList<apparaturs*>::iterator it3 = tmp_app.begin();
    while (it3 != tmp_app.end()){
        this->appr.append(*it3);
        ++it3;
    }
}
ktp::~ktp()
{
    if (up != nullptr){
        QList<obj*> tmp = up->get_obj_list();
        int z = tmp.indexOf(this);
        if (z != -1){
            up->del_n_obj(z);
        }
    }
    if (ups != nullptr){
        QList<obj*> tmp = ups->get_ktp_list();
        int z = tmp.indexOf(this);
        if (z != -1){
            ups->remove_n_ktp(z);
        }
    }
    ups = nullptr;
}
void ktp::init(ktp *arg)
{
    this->name = arg->get_name();
    QList<protocol*>tmp_prt = arg->get_pro_list();
    QList<protocol*>::iterator it1 = tmp_prt.begin();
    while (it1 != tmp_prt.end()){
        this->p_list.append(*it1);
        ++it1;
    }
    this->adr = arg->get_adr();
    this->sh = arg->get_sh();
    this->status = arg->get_status();
    this->max_time = arg->get_maxt_list();
    this->min_time = arg->get_mint_list();
    this->voltage = arg->get_voltage();
    QList<apparaturs*> tmp_app = arg->get_app_list();
    QList<apparaturs*>::iterator it3 = tmp_app.begin();
    while (it3 != tmp_app.end()){
        this->appr.append(*it3);
        ++it3;
    }
}
void ktp::init(obj *arg)
{
    if ("ktp" == arg->type()){
        this->name = arg->get_name();
        QList<protocol*>tmp_prt = arg->get_pro_list();
        QList<protocol*>::iterator it1 = tmp_prt.begin();
        while (it1 != tmp_prt.end()){
            this->p_list.append(*it1);
            ++it1;
        }
        this->adr = arg->get_adr();
        this->sh = arg->get_sh();
        this->status = arg->get_status();
        this->max_time = arg->get_maxt_list();
        this->min_time = arg->get_mint_list();
        this->voltage = arg->get_voltage();
        QList<apparaturs*> tmp_app = arg->get_app_list();
        QList<apparaturs*>::iterator it3 = tmp_app.begin();
        while (it3 != tmp_app.end()){
            this->appr.append(*it3);
            ++it3;
        }
    }
}
void ktp::init(obj arg)
{
    this->init(&arg);
}
QString ktp::type() const
{
    return status;
}
void ktp::set_up(obj *arg)
{
    if (up != nullptr){
        QList<obj*> tmp = up->get_obj_list();
        int z = tmp.indexOf(this);
        if (z != -1){
            up->del_n_obj(z);
        }
    }
    this->up = nullptr;
    this->ups = arg;
    this->max_time = ups->get_maxt_list();
    this->min_time = ups->get_mint_list();
}
void ktp::set_up(order *arg)
{
    if (ups != nullptr){
        QList<obj*> tmp = ups->get_ktp_list();
        int z = tmp.indexOf(this);
        if (z != -1){
            ups->remove_n_ktp(z);
        }
    }
    this->ups = nullptr;
    this->up = arg;
}
obj* ktp::get_ups() const
{
    return this->ups;
}
QDomElement ktp::make_xml()
{
    QDomDocument ret_xml;
     QDomElement root = ret_xml.createElement("ktp");
         ret_xml.appendChild(root);
         root.appendChild(this->make_xml_1());
    return root;
}
int ktp::load_xml(QDomNode *arg)
{
    QDomNode root = *arg;
    QDomNode rxml = root.firstChildElement("obj");
    this->load_xml_1(&rxml);
    return 0; 
}
