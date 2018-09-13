#include "order.h"

order::order()
{
    this->uniq = "";
    this->number = 0;
    this->date.setDate(1984, 01, 9);
    this->obj_list = QList<obj*>();
    this->up = nullptr;
}
order::order(klient *arg)
{
    this->uniq = "";
    this->number = 0;
    this->date.setDate(1984, 01, 9);
    this->obj_list = QList<obj*>();
    this->up = arg;
}
order::order(const order &arg)
{
    this->uniq = arg.uniq;
    this->date = arg.date;
    this->number = arg.number;
    QList<obj*> tmpo = arg.get_obj_list();
    QList<obj*>::iterator it = tmpo.begin();
    while (it != tmpo.end()){
        if ((*it)->get_status() == "cp"){
            obj* tmpo1 = fab_obj::create_cp();
            tmpo1->init(*it);
            this->add_obj(tmpo1);
        }
        if ((*it)->get_status() == "ktp"){
            obj* tmpo2 = fab_obj::create_ktp();
            tmpo2->init(*it);
            this->add_obj(tmpo2);
        }
        ++it;
    }
}
order::~order()
{
    QList<order*> tmp = up->get_order_list();
    int z = tmp.indexOf(this);
    if ( z != -1){
        up->del_n_order(z);
    }
    up = nullptr;
    QList<obj*>::iterator start = obj_list.begin();
    while (start != obj_list.begin()){
        delete (*start)++;
    }
    this->obj_list.clear();
}
bool order::operator == (const order &arg)
{
    if (
            this->uniq == arg.uniq &&
            this->date == arg.date &&
            this->number == arg.number &&
            this->obj_list == arg.obj_list &&
            this->up == arg.up
            ) {return true;}
    return false;
}
bool order::operator != (const order &arg)
{
    return !(*this == arg);
}
order& order::operator = (const order &arg)
{
    this->init(arg);
    return (*this);
}
void order::init(order arg)
{
    this->uniq = arg.get_uniq();
    this->date = arg.get_date();
    this->number = arg.get_num();
    fab_obj fabob;
    QList<obj*> tmpo = arg.get_obj_list();
    QList<obj*>::iterator it = tmpo.begin();
    while (it != tmpo.end()){
        if ((*it)->get_status() == "cp"){
            obj* tmpo1 = fabob.create_cp();
            tmpo1->init(*it);
            this->add_obj(tmpo1);
        }
        if ((*it)->get_status() == "ktp"){
            obj* tmpo2 = fabob.create_ktp();
            tmpo2->init(*it);
            this->add_obj(tmpo2);
        }
        ++it;
    }
}
void order::init(order *arg)
{
    this->init(*arg);
}
order order::null_order()
{
    order(this->up);
    return *this;
}

int order::set_up(klient *arg)
{
    this->up = arg;
    return 0;
}
klient* order::get_up()
{
    return this->up;
}

int order::set_uniq(QString arg)
{
    if (arg.size() < 1000)
    {
        this->uniq = arg;
        return 0;
    }
    return 1;
}
QString order::get_uniq()
{
    return this->uniq;
}
int order::set_date(QDate arg)
{
    this->date = arg;
    return 0;
}
QDate order::get_date()
{
    return this->date;
}

int order::add_obj(obj *arg)
{
    this->obj_list.append(arg);
    arg->set_up(this);
    return 0;
}
int order::set_obj_list(QList<obj *> *arg)
{
    this->obj_list.clear();
    this->obj_list.append(*arg);
    return 0;
}
QList<obj *> order::get_obj_list() const
{
    return this->obj_list;
}
int order::clear_obj_list()
{
    this->obj_list.clear();
    return 0;
}
int order::del_n_obj(int arg)
{
    if (arg < this->obj_list.size()){
        this->obj_list.removeAt(arg);
        return 0;
    }
    return 1;
}
int order::del_top_obj()
{
    this->obj_list.removeLast();
    return 0;
}
int order::set_num(unsigned int arg)
{
    this->number = arg;
    return 0;
}
unsigned int order::get_num()
{
    return this->number;
}
QString order::get_bd_name() const
{
    if (up == nullptr) return "";
    return up->get_patch() + "/" + up->get_pdirname();
}
QDomElement order::make_xml()
{
    QDomDocument ret_xml;
     QDomElement root = ret_xml.createElement("order");
         ret_xml.appendChild(root);

    QDomElement xml_uniq = ret_xml.createElement("uniq");
     QDomText xml_uniq_text = ret_xml.createTextNode(this->uniq);
        root.appendChild(xml_uniq);
        xml_uniq.appendChild(xml_uniq_text);

     QDomElement xml_number = ret_xml.createElement("number");
       QDomText xml_number_text = ret_xml.createTextNode(QString::number(this->number));
          root.appendChild(xml_number);
           xml_number.appendChild(xml_number_text);

        root.appendChild(my_fnc::date_to_xml(date));
    QDomElement xml_obj = ret_xml.createElement("objects");
        root.appendChild(xml_obj);
        QList<obj*>::iterator it = this->obj_list.begin();
        int i = 0;
        while (it != this->obj_list.end()) {
               QDomElement wr =  ret_xml.createElement("obj" + QString::number(i));
               xml_obj.appendChild(wr);
               wr.appendChild(it[0]->make_xml());
               ++it;
               ++i;
        }
    return root;
}
int order::load_xml(QDomNode *arg, klient *ups)
{
    QDomNode root = *arg;

    this->uniq = root.firstChildElement("uniq").text(); 
    this->number = root.firstChildElement("number").text().toUInt();

    QDomDocument *lxml = new QDomDocument;

    my_fnc::xml_to_date(root.firstChildElement("date"), this->date);

    lxml->appendChild(root.firstChildElement("objects"));

    QDomNode tmpd;
    fab_obj obf;
    int i = 0;
    while (!root.firstChildElement("objects").firstChildElement("obj" + QString::number(i)).isNull()) {
        tmpd = root.firstChildElement("objects").firstChildElement("obj" + QString::number(i)).firstChildElement("cp");
        if (!tmpd.isNull()){
            obj *tmpc = obf.create_cp();
            tmpc->load_xml(&tmpd);
            this->add_obj(tmpc);
        }
        tmpd.clear();
        tmpd = root.firstChildElement("objects").firstChildElement("obj" + QString::number(i)).firstChildElement("ktp");
        if (!tmpd.isNull()){
            obj *tmpk = obf.create_ktp();
            tmpk->load_xml(&tmpd);
            this->add_obj(tmpk);
        }
        tmpd.clear();
        ++i;
    }
    delete lxml;
    this->set_up(ups);

    return 0;
}

