#include "order.h"
#include "ktp.h"
#include "cp.h"

cp::cp()
{
    this->name = "";
    this->p_list = QList<protocol*>();
    this->adr = address();
    this->sh = "";
    this->status = "cp";
    this->max_time = QList<QPair<QTime, QTime>>();
    this->min_time = QList<QPair<QTime, QTime>>();
    this->up = nullptr;
    this->voltage = 0;
    this->ktp_list = QList<obj*>();
    _tr = transformator();
}
cp::cp(order *arg)
{
    cp();
    this->status = "cp";
    this->up = arg;
}
cp::cp(obj *arg)
{
    this->name = arg->get_name();
    QList<protocol*>tmp_prt = arg->get_pro_list();
    QList<protocol*>::iterator it1 = tmp_prt.begin();
    while (!(it1 == tmp_prt.end())){
        this->p_list.append(*it1);
        ++it1;
    }
    adr = arg->get_adr();
    sh = arg->get_sh();
    status = arg->get_status();
    max_time = arg->get_maxt_list();
    min_time = arg->get_mint_list();
    voltage = arg->get_voltage();
    fab_obj fabob;
    QList<obj*> tmp_ktp = arg->get_ktp_list();
    QList<obj*>::iterator it2 = tmp_ktp.begin();
    while (it2 != tmp_ktp.end()){
        obj *tmpo = fabob.create_ktp();
        tmpo->init(*it2);
        this->add_ktp(tmpo);
        ++it2;
    }
    QList<apparaturs*> tmp_app = arg->get_app_list();
    QList<apparaturs*>::iterator it3 = tmp_app.begin();
    while (it3 != tmp_app.end()){
        this->appr.append(*it3);
        ++it3;
    }
    _tr = arg->get_tr();
}
cp::cp(const cp &arg) : obj(arg)
{
    fab_obj fabob;
    QList<obj*> tmp_ktp = arg.get_ktp_list();
    QList<obj*>::iterator it2 = tmp_ktp.begin();
    while (it2 != tmp_ktp.end()){
        obj *tmpo = fabob.create_ktp();
        tmpo->init(*it2);
        this->add_ktp(tmpo);
        ++it2;
    }
    _tr = arg.get_tr();
}
cp::~cp()
{
    if (this->up != nullptr) {
        QList<obj*> tmp = up->get_obj_list();
        int z = tmp.indexOf(this);
        if (z != -1){
            up->del_n_obj(z);
        }
    }
    up = nullptr;
    QList<obj*>::iterator start = ktp_list.begin();
    while (start != ktp_list.end()){
        delete (*start);
        ++start;
    }
    this->ktp_list.clear();
}
cp cp::null_cp()
{
    cp();
    return (*this);
}
void cp::init(const cp *arg)
{
    this->name = arg->get_name();
    QList<protocol*>tmp_prt = arg->get_pro_list();
    QList<protocol*>::iterator it1 = tmp_prt.begin();
    while (!(it1 == tmp_prt.end())){
        this->p_list.append(*it1);
        ++it1;
    }
    this->adr = arg->get_adr();
    this->sh = arg->get_sh();
    this->status = arg->get_status();
    this->max_time = arg->get_maxt_list();
    this->min_time = arg->get_mint_list();
    this->voltage = arg->get_voltage();
    fab_obj fabob;
    QList<obj*> tmp_ktp = arg->get_ktp_list();
    QList<obj*>::iterator it2 = tmp_ktp.begin();
    while (it2 != tmp_ktp.end()){
        obj *tmpo = fabob.create_ktp();
        tmpo->init(*it2);
        this->add_ktp(tmpo);
        ++it2;
    }
    QList<apparaturs*> tmp_app = arg->get_app_list();
    QList<apparaturs*>::iterator it3 = tmp_app.begin();
    while (it3 != tmp_app.end()){
        this->appr.append(*it3);
        ++it3;
    }
   _tr = arg->get_tr();
}
void cp::init(const obj &arg)
{
    this->init(&arg);
}
void cp::init(const obj *arg)
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
    fab_obj fabob;
    QList<obj*> tmp_ktp = arg->get_ktp_list();
    QList<obj*>::iterator it2 = tmp_ktp.begin();
    while (it2 != tmp_ktp.end()){
        obj *tmpo = fabob.create_ktp();
        tmpo->init(*it2);
        this->add_ktp(tmpo);
        ++it2;
    }
    QList<apparaturs*> tmp_app = arg->get_app_list();
    QList<apparaturs*>::iterator it3 = tmp_app.begin();
    while (it3 != tmp_app.end()){
        this->appr.append(*it3);
        ++it3;
    }
    _tr = arg->get_tr();
}
int cp::add_ktp(obj *arg)
{
    arg->set_up(this);
    this->ktp_list.append(arg);
    arg->add_max_list(this->get_maxt_list());
    arg->add_min_list(this->get_mint_list());
    return 0;
}
QList<obj *> cp::get_ktp_list() const
{
    return this->ktp_list;
}
int cp::clear_ktp_list()
{
    this->ktp_list.clear();
    return 0;
}
int cp::del_top_ktp()
{
    this->ktp_list.removeLast();
    return 0;
}
int cp::remove_n_ktp(int arg)
{
    if (arg < this->ktp_list.size()){
        this->ktp_list.removeAt(arg);
        return 0;
    }
    return 1;
}
int cp::set_tr(transformator arg)
{
    _tr = arg;
    return 0;
}

transformator cp::get_tr() const
{
    return _tr;
}
QDomElement cp::make_xml()
{
    QDomDocument ret_xml;
     QDomElement root = ret_xml.createElement("cp");
         ret_xml.appendChild(root);
         root.appendChild(this->make_xml_1());
         root.appendChild(_tr.make_xml());
         QList<obj*>::iterator it = this->ktp_list.begin();
         QDomElement xml_ktp = ret_xml.createElement("ktp_list");
         int i = 0;
         while (it != this->ktp_list.end()){
             QDomElement wr =  ret_xml.createElement("ktp" + QString::number(i));
             xml_ktp.appendChild(wr);
             wr.appendChild(it[0]->make_xml());
             ++it;
             ++i;
         }
         root.appendChild(xml_ktp);
    return root;
}
int cp::load_xml(QDomNode *arg)
{
    QDomNode root = *arg;

    QDomNode rxml = root.firstChildElement("obj");
    this->load_xml_1(&rxml);
    QDomNode lxml = root.firstChildElement("trans");
    _tr.load_xml(&lxml);
    QDomNode tmpd;
    fab_obj fabob;
    int i = 0;
    while (!root.firstChildElement("ktp_list").firstChildElement("ktp" + QString::number(i)).isNull()) {
        tmpd = root.firstChildElement("ktp_list").firstChildElement("ktp" + QString::number(i)).firstChildElement("ktp");
        obj *tmpo = fabob.create_ktp();
        tmpo->load_xml(&tmpd);
        this->add_ktp(tmpo);
        ++i;
    }
    return 0;
}
QString cp::type() const
{
    return this->status;
}
void cp::time_ktp()
{
    QList<obj*>::iterator it = this->ktp_list.begin();
    while (it != this->ktp_list.end()){
        (*it)->add_max_list(this->get_maxt_list());
        (*it)->add_min_list(this->get_mint_list());
        ++it;
    }
}
