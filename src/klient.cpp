#include "klient.h"
#include "order.h"
#include "ktp.h"
klient::klient()
{
    det = details();
    fadr = address();
    orders = QList<order*>();
}
klient::klient(const klient &arg)
{
    name = arg.name;
    det = arg.det;
    fadr = arg.fadr;
    fab_order fabo;
    QList<order*>::const_iterator it = arg.orders.begin();
    while (it != arg.orders.end()){
        order *tmpord = fabo.create();
        tmpord->init(*it);
        this->add_orders(tmpord);
        ++it;
    }
    this->pth = arg.pth;
}
bool klient::operator == (const klient &arg)
{
    if (
            name == arg.name &&
            det == arg.det &&
            fadr == arg.fadr
            ) {return true;}
    return false;
}
bool klient::operator != (const klient &arg)
{
    return !(*this == arg);
}
klient& klient::operator = (const klient &arg)
{
    name = arg.name;
    det = arg.det;
    fadr = arg.fadr;
    fab_order fabo;
    QList<order*>::const_iterator it = arg.orders.begin();
    while (it != arg.orders.end()){
        order *tmpord = fabo.create();
        tmpord->init(*it);
        this->add_orders(tmpord);
        ++it;
    }
    return (*this);
}
klient klient::null_klient()
{
    klient();
    return *this;
}
klient::~klient()
{
    QList<order*>::iterator start = orders.begin();
    while (start != orders.end()){
        (*start)->~order();
        ++start;
    }
    this->orders.clear();
}
void klient::init(klient *arg)
{
    this->name = arg->get_name();
    this->det = arg->get_det();
    this->fadr = arg->get_fadr();
    fab_order fabord;
    QList<order*> tmpo = arg->get_order_list();
    QList<order*>::iterator it = tmpo.begin();
    while (it != tmpo.end()){
        order* tmpo_2 = fabord.create();
        tmpo_2->init(*it);
        this->add_orders(tmpo_2);
        ++it;
    }
}
void klient::set_email(const QString &arg)
{
    det.set_email(arg);
}
QString klient::get_email() const
{
    return det.get_email();
}
void klient::set_full_name(const QString& arg)
{
    det.set_name(arg);
}
QString klient::get_full_name() const
{
    return det.get_name();
}
void klient::set_name(QString arg)
{
    if (arg.size() < 1000)
    {
        this->name = arg;
    }
}
QString klient::get_name() const
{
    return this->name;
}
void klient::set_det(details *arg)
{
    this->det = *arg;
}
details klient::get_det() const
{
    return this->det;
}

void klient::set_uadr(address *arg)
{
    this->det.set_ur_post(arg);
}
address klient::get_uadr() const
{
    return this->det.get_ur_post();
}
void klient::set_fadr(address *arg)
{
    this->fadr = *arg;
}
address klient::get_fadr() const
{
    return this->fadr;
}
void klient::set_padr(address *arg)
{
    this->det.set_re_post(arg);
}
address klient::get_padr() const
{
    return this->det.get_re_post();
}

void klient::add_orders(order *arg)
{
    this->orders.append(arg);
    arg->set_up(this);
}
void klient::set_orders_list(QList<order*> *arg)
{
    this->orders.clear();
    this->orders.append(*arg);
    QList<order*>::iterator it = this->orders.begin();
    while (it != this->orders.end()){
        it[0]->set_up(this);
        ++it;
    }
}
QList<order*> klient::get_order_list() const
{
    return this->orders;
}
void klient::clear_orders()
{
    this->orders.clear();
}
void klient::del_top_order()
{
    this->orders.removeLast();
}
void klient::del_n_order(int arg)
{
    if (arg < this->orders.size()) {
        this->orders.removeAt(arg);
    }
}
int klient::size_orders()
{
    return this->orders.size();
}
void klient::set_inn(unsigned long long int arg)
{
    this->det.set_inn(arg);
}
void klient::set_dir(QPair<QString, QString> arg)
{
    this->det.set_dir(arg);
}
void klient::set_tel_list(QList<QString> arg)
{
    this->det.set_tel_list(arg);
}
void klient::set_fax_list(QList<QString> arg)
{
    this->det.set_fax_list(arg);
}
QDomDocument klient::make_xml()
{
    QDomDocument ret_xml;
    QDomElement root = ret_xml.createElement("klient");

    QDomElement xml_name = ret_xml.createElement("name");
        QDomText xml_name_text = ret_xml.createTextNode(name);
        root.appendChild(xml_name);
        xml_name.appendChild(xml_name_text);

    QDomElement xml_pdirname = ret_xml.createElement("pdirname");
        QDomText xml_pdirname_text = ret_xml.createTextNode(pdirname);
        root.appendChild(xml_pdirname);
        xml_pdirname.appendChild(xml_pdirname_text);

       root.appendChild(this->det.make_xml());

    QDomElement xml_fadr = ret_xml.createElement("fadr");
        root.appendChild(xml_fadr);
        xml_fadr.appendChild(this->fadr.make_xml());

    QDomElement xml_orders = ret_xml.createElement("orders");
       root.appendChild(xml_orders);
       QList<order*>::iterator it = this->orders.begin();
       int i = 0;
       while (it != this->orders.end()) {
              QDomElement ord =  ret_xml.createElement("ord" + QString::number(i));
              xml_orders.appendChild(ord);
              ord.appendChild(it[0]->make_xml());
              ++it;
              ++i;
        }
       ret_xml.appendChild(root);
    return  ret_xml;
}
void klient::load_xml(QDomDocument *arg)
{
    QDomElement root = arg->firstChildElement("klient");
    name = root.firstChildElement("name").text();
    pdirname = root.firstChildElement("pdirname").text();

    auto treg0 = root.firstChildElement("details");
    this->det.load_xml(&treg0);
    auto treg1 = root.firstChildElement("fadr").firstChildElement("address");
    this->fadr.load_xml(&treg1);

      auto treg2 = root.firstChildElement("orders");
      fab_order create_ord;
      int i = 0;
      while (!treg2.firstChildElement("ord" + QString::number(i)).isNull()){
          auto treg3 = treg2.firstChildElement("ord" + QString::number(i)).firstChildElement("order");
          this->orders.append(create_ord.create());
          this->orders.last()->load_xml(&treg3, this);
        i++;
      }
}
void klient::set_patch(const QString &arg)
{
    this->pth = arg;
}
QString klient::get_patch() const
{
    return this->pth;
}
void klient::set_fname(const QString &arg)
{
    this->fname = arg;
}
QString klient::get_fname() const
{
    return this->fname;
}
void klient::set_pdirname(const QString& arg)
{
    pdirname =arg;
}
QString klient::get_pdirname() const
{
    return pdirname;
}
int klient::load_db(){return 0;}
int klient::save_db(){return 0;}


