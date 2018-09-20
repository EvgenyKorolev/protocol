#include "obj.h"
#include "order.h"

obj::obj()
{
    this->up = nullptr;
    this->ups = nullptr;
}
obj::obj(order *arg)
{
    obj();
    this->up = arg;
}
obj::obj(const obj &arg)
{
    this->name = arg.get_name();
    QList<protocol*> tmp_prt = arg.get_pro_list();
    QList<protocol*>::iterator it1 = tmp_prt.begin();
    while (!(it1 == tmp_prt.end())){
        this->p_list.append(*it1);
        ++it1;
    }
    QList<apparaturs*> tmp_app = arg.get_app_list();
    QList<apparaturs*>::iterator it3 = tmp_app.begin();
    while (it3 != tmp_app.end()){
        this->appr.append(*it3);
        ++it3;
    }
    this->adr = arg.get_adr();
    this->sh = arg.get_sh();
    this->status = arg.get_status();
    this->max_time = arg.get_maxt_list();
    this->min_time = arg.get_mint_list();
    this->voltage = arg.get_voltage();
    this->up = nullptr;
    this->ups = nullptr;
}
obj::~obj()
{
    this->up = nullptr;
    this->ups = nullptr;
    QList<protocol*>::iterator start = this->p_list.begin();
    while (start != this->p_list.end()){
        delete (*start)++;
    }
    while (this->p_list.size() > 0){
        this->p_list.removeLast();
    }
}
void obj::init(const obj& arg)
{
    this->name = arg.get_name();
    QList<protocol*>tmp_prt = arg.get_pro_list();
    QList<protocol*>::iterator it1 = tmp_prt.begin();
    while (!(it1 == tmp_prt.end())){
        this->p_list.append(*it1);
        it1++;
    }
    this->adr = arg.get_adr();
    this->sh = arg.get_sh();
    this->status = arg.get_status();
    this->max_time = arg.get_maxt_list();
    this->min_time = arg.get_mint_list();
    this->voltage = arg.get_voltage();
    QList<apparaturs*> tmp_app = arg.get_app_list();
    QList<apparaturs*>::iterator it3 = tmp_app.begin();
    while (it3 != tmp_app.end()){
        this->appr.append(*it3);
        it3++;
    }
    this->up = nullptr;
    this->ups = nullptr;
}
void obj::init_new(const obj& arg)
{
    this->name = arg.get_name();
    QList<protocol*>tmp_prt = arg.get_pro_list();
    QList<protocol*>::iterator it1 = tmp_prt.begin();
    while (!(it1 == tmp_prt.end())){
        protocol* tmp = new protocol(this);
        tmp->set_data(*it1);
        this->p_list.append(tmp);
        it1++;
    }
    this->adr = arg.get_adr();
    this->sh = arg.get_sh();
    this->status = arg.get_status();
    this->max_time = arg.get_maxt_list();
    this->min_time = arg.get_mint_list();
    this->voltage = arg.get_voltage();
    QList<apparaturs*> tmp_app = arg.get_app_list();
    QList<apparaturs*>::iterator it3 = tmp_app.begin();
    while (it3 != tmp_app.end()){
        this->appr.append(*it3);
        it3++;
    }
    this->up = nullptr;
    this->ups = nullptr;
}
bool obj::operator ==(const obj &arg)
{
  if (
    this->name == arg.get_name() &&
    this->adr == arg.get_adr() &&
    this->sh == arg.get_sh() &&
    this->status == arg.get_status() &&
    this->voltage == arg.get_voltage()
          ) {return true;}
  return false;
}
bool obj::operator != (const obj &arg)
{
    return !(*this == arg);
}
obj& obj::operator =(const obj &arg)
{
    this->name = arg.get_name();
    QList<protocol*>tmp_prt = arg.get_pro_list();
    QList<protocol*>::iterator it1 = tmp_prt.begin();
    while (!(it1 == tmp_prt.end())){
        this->p_list.append(*it1);
        it1++;
    }
    this->adr = arg.get_adr();
    this->sh = arg.get_sh();
    this->status = arg.get_status();
    this->max_time = arg.get_maxt_list();
    this->min_time = arg.get_mint_list();
    this->voltage = arg.get_voltage();
    this->up = arg.up;
    this->ups = arg.ups;
    return *this;
}
void obj::set_up(order *arg)
{
    this->up = arg;
    this->ups = nullptr;
}
QString obj::get_bd_name() const
{
    if (up == nullptr){
       if (ups == nullptr) return "";
       return ups->get_bd_name();
    } else return up->get_bd_name();
}
void obj::set_up(obj *arg)
{
    this->up = nullptr;
    this->ups = arg;
}
order* obj::get_up() const
{
    return this->up;
}
obj* obj::get_ups() const
{
    return nullptr;
}
int obj::set_name(const QString &arg)
{
    if (arg.size() < 1000)
    {
        name = arg;
        return 0;
    }
    return 1;
}
QString obj::get_name() const
{
    return this->name;
}

int obj::set_voltage(int arg)
{
        this->voltage = arg;
        return 0;
}
int obj::get_voltage() const
{
    return this->voltage;
}
int obj::add_pro(protocol *arg)
{
    arg->set_parent(this);
    this->p_list.append(arg);
    return 0;
}
QList<protocol *> obj::get_pro_list() const
{
    return this->p_list;
}
int obj::clear_pro_list()
{
    this->p_list.clear();
    return 0;
}
int obj::del_top_pro()
{
    p_list.last()->erase();
    this->p_list.removeLast();
    return 0;
}
int obj::remove_n_pro(int arg)
{
    if ((arg < this->p_list.size()) && arg >= 0)
    {
        this->p_list.removeAt(arg);
    }
    return 1;
}

int obj::set_adr(address *arg)
{
    this->adr = *arg;
    return 0;
}
int obj::set_adr(address arg)
{
    this->adr = arg;
    return 0;
}
address obj::get_adr() const
{
    return this->adr;
}
int obj::set_sh(const QString& arg)
{
    if (arg.size() < 1000){
        sh = arg;
        return 0;
    }
    return 1;
}
QString obj::get_sh() const
{
    return this->sh;
}
void obj::set_schema(const QString& arg)
{
    schema = arg;
}
QString obj::get_schema() const
{
    return  schema;
}
int obj::set_cp()
{
    this->status = "cp";
    return 0;
}
int obj::set_ktp()
{
    this->status = "ktp";
    return 0;
}
QString obj::get_status() const
{
    return this->status;
}

int obj::add_maxt(QPair<QTime, QTime> *arg)
{
    this->max_time.append(*arg);
    return 0;
}
QList<QPair<QTime, QTime>> obj::get_maxt_list() const
{
    return this->max_time;
}
int obj::clear_maxt_list()
{
    this->max_time.clear();
    return 0;
}
int obj::del_top_maxt()
{
    this->max_time.removeLast();
    return 0;
}
int obj::remove_n_maxt(int arg)
{
    if ((this->max_time.size() > arg) && (0 <= arg)){
        this->max_time.removeAt(arg);
    }
    return 0;
}
bool obj::add_max_list(QList<QPair<QTime, QTime> > *arg)
{
    this->max_time = *arg;
    return true;
}
bool obj::add_max_list(QList<QPair<QTime, QTime> > arg)
{
    this->max_time = arg;
    return true;
}
int obj::add_mint(QPair<QTime, QTime> *arg)
{
    this->min_time.append(*arg);
    return 0;
}
QList<QPair<QTime, QTime>> obj::get_mint_list() const
{
    return this->min_time;
}
int obj::clear_mint_list()
{
    this->min_time.clear();
    return 0;
}
int obj::del_top_mint()
{
    this->min_time.removeLast();
    return 0;
}
int obj::remove_n_mint(int arg)
{
    if ((arg < this->min_time.size()) && (arg >= 0)){
        this->min_time.removeAt(arg);
        return 0;
    }
    return 1;
}
bool obj::add_min_list(QList<QPair<QTime, QTime> > *arg)
{
    this->min_time = *arg;
    return true;
}
bool obj::add_min_list(QList<QPair<QTime, QTime> > arg)
{
    this->min_time = arg;
    return true;
}
void obj::add_app(apparaturs *arg)
{
    this->appr.append(arg);
}
QList<apparaturs*> obj::get_app_list() const
{
    return this->appr;
}
void obj::clear_app_list()
{
    this->appr.clear();
}
void obj::del_top_app()
{
    this->appr.removeLast();
}
void obj::remove_n_app(int arg)
{
    this->appr.removeAt(arg);
}
bool obj::set_app_list(QList<apparaturs*> *arg)
{
    this->appr = *arg;
    return true;
}
bool obj::set_app_list(QList<apparaturs*> arg)
{
    this->appr = arg;
    return true;
}
QDomElement obj::make_xml_1()
{
    QDomDocument ret_xml;
     QDomElement root = ret_xml.createElement("obj");
         ret_xml.appendChild(root);

    QDomElement xml_name = ret_xml.createElement("name");
        QDomText xml_name_text = ret_xml.createTextNode(this->name);
        root.appendChild(xml_name);
        xml_name.appendChild(xml_name_text);
   QDomElement xml_schema = ret_xml.createElement("schema");
       QDomText xml_schema_text = ret_xml.createTextNode(schema);
       root.appendChild(xml_schema);
       xml_schema.appendChild(xml_schema_text);
    QDomElement xml_prol = ret_xml.createElement("protocols");
        root.appendChild(xml_prol);
        QList<protocol*>::iterator it1 = this->p_list.begin();
        int i = 0;
        while (it1 != this->p_list.end()){
            QDomElement wr = ret_xml.createElement("prt" + QString::number(i));
            xml_prol.appendChild(wr);
            wr.appendChild(it1[0]->make_xml());
            it1++;
            i++;
        }
        root.appendChild(this->adr.make_xml());

        QDomElement xml_sh = ret_xml.createElement("sh");
            QDomText xml_sh_text = ret_xml.createTextNode(this->sh);
            root.appendChild(xml_sh);
            xml_sh.appendChild(xml_sh_text);

        QDomElement xml_status = ret_xml.createElement("status");
            QDomText xml_status_text = ret_xml.createTextNode(this->status);
            root.appendChild(xml_status);
            xml_status.appendChild(xml_status_text);

         QDomElement xml_volt = ret_xml.createElement("volt");
             QDomText xml_volt_text = ret_xml.createTextNode(QString::number(this->voltage));
             root.appendChild(xml_volt);
             xml_volt.appendChild(xml_volt_text);

        QDomElement xml_max_time = ret_xml.createElement("max_time_list");
            root.appendChild(xml_max_time);
        QList<QPair<QTime, QTime>>::iterator it2 = this->max_time.begin();
        i = 0;
        while (it2 != this->max_time.end()){
              QDomElement wr = ret_xml.createElement("maxtl" + QString::number(i));
              QDomElement start_time = ret_xml.createElement("start_t");
              QDomElement end_time = ret_xml.createElement("end_t");
              xml_max_time.appendChild(wr);
              wr.appendChild(start_time);
              wr.appendChild(end_time);
              start_time.appendChild(my_fnc::time_to_xml(it2->first));
              end_time.appendChild(my_fnc::time_to_xml(it2->second));
              i++;
              it2++;
        }
        QDomElement xml_min_time = ret_xml.createElement("min_time_list");
            root.appendChild(xml_min_time);
        QList<QPair<QTime, QTime>>::iterator it3 = this->min_time.begin();
        i = 0;
        while (it3 != this->min_time.end()){
              QDomElement wr = ret_xml.createElement("mintl" + QString::number(i));
              QDomElement start_time = ret_xml.createElement("start_t");
              QDomElement end_time = ret_xml.createElement("end_t");
              xml_min_time.appendChild(wr);
              wr.appendChild(start_time);
              wr.appendChild(end_time);
              start_time.appendChild(my_fnc::time_to_xml(it3->first));
              end_time.appendChild(my_fnc::time_to_xml(it3->second));
              i++;
              it3++;
        }
        // Аппаратура
        QDomElement xml_app_list = ret_xml.createElement("applist");
            root.appendChild(xml_app_list);
        QList<apparaturs*>::iterator it4 = this->appr.begin();
        i = 0;
        while (it4 != this->appr.end()){
            QDomElement wr = ret_xml.createElement("app" + QString::number(i));
            xml_app_list.appendChild(wr);
            wr.appendChild(it4[0]->make_xml_1());
            it4++;
            i++;
        }

    return root;
}
int obj::load_xml_1(QDomNode *arg)
{
    QDomNode root = *arg;

    name = root.firstChildElement("name").text();
    schema = root.firstChildElement("schema").text();
    sh = root.firstChildElement("sh").text();
    status = root.firstChildElement("status").text();
    voltage = root.firstChildElement("volt").text().toInt();
    auto lx = root.firstChildElement("address");
    adr.load_xml(&lx);
    QDomNode *lxmp = new QDomNode;
    lxmp->appendChild(root.firstChildElement("protocols"));

    int i = 0;
    while (!root.firstChildElement("protocols").firstChildElement("prt" + QString::number(i)).isNull()){
        QDomNode tmpn = root.firstChildElement("protocols").firstChildElement("prt" + QString::number(i)).firstChildElement("protocol");
        this->add_pro(new protocol(&tmpn));
        i++;
    }
    delete lxmp;
    QDomNode *lxml = new QDomNode;
    lxml->appendChild(root.firstChildElement("max_time_list"));
    QPair<QTime, QTime> tmppr;
    i = 0;
    while (!root.firstChildElement("max_time_list").firstChildElement("maxtl" + QString::number(i)).isNull()){
        my_fnc::xml_to_time(root.firstChildElement("max_time_list").firstChildElement("maxtl" + QString::number(i)).firstChildElement("start_t").firstChildElement("time"), tmppr.first);
        my_fnc::xml_to_time(root.firstChildElement("max_time_list").firstChildElement("maxtl" + QString::number(i)).firstChildElement("end_t").firstChildElement("time"), tmppr.second);
        this->max_time.append(tmppr);
        i++;
    }
    i = 0;
    while (!root.firstChildElement("min_time_list").firstChildElement("mintl" + QString::number(i)).isNull()){
        my_fnc::xml_to_time(root.firstChildElement("min_time_list").firstChildElement("mintl" + QString::number(i)).firstChildElement("start_t").firstChildElement("time"), tmppr.first);
        my_fnc::xml_to_time(root.firstChildElement("min_time_list").firstChildElement("mintl" + QString::number(i)).firstChildElement("end_t").firstChildElement("time"), tmppr.second);
        this->min_time.append(tmppr);
        i++;
    }
    delete lxml;

    QDomNode tmpa;
    fab_app appf;
    i = 0;
    while (!root.firstChildElement("applist").firstChildElement("app" + QString::number(i)).isNull()){
        tmpa = root.firstChildElement("applist").firstChildElement("app" + QString::number(i)).firstChildElement("apparaturs1");
        apparaturs* appt = appf.create_app();
        appt->load_xml(&tmpa);
        this->appr.append(appt);
        i++;
    }
    return 0;
}
// Эти методы должны быть проеделены в дочернем классе
QDomElement obj::make_xml()
{
    QDomDocument ret_xml;
     QDomElement root = ret_xml.createElement("obj");
     return root;
}
int obj::load_xml(QDomNode *arg)
{
    Q_UNUSED(arg)
    return 0;
}
// Это функции для совместимости интерфейса
QString obj::type() const
{
    return status;
}
QList<QString> obj::ret_uids() const
{
    QList<QString> ret{QList<QString>()};
    for ( auto it : p_list){
        ret.append(it->get_uin());
    }
    return ret;
}
int obj::add_ktp(obj *arg){Q_UNUSED(arg); return 666;}
QList<obj*> obj::get_ktp_list() const {return QList<obj*>();}
int obj::clear_ktp_list(){return 666;}
int obj::del_top_ktp(){return 666;}
int obj::remove_n_ktp(int arg){Q_UNUSED(arg); return 666;}
int obj::set_tr(transformator arg){Q_UNUSED(arg); return 666;}
transformator obj::get_tr() const
{
    return nullptr;
}
void obj::time_ktp(){}
