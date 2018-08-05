#include "details.h"

details::details()
{
    QList<QString> tmpl;
    this->list_tel = tmpl;
    this->list_fax = tmpl;
    this->post.first = address();;
    this->post.second = address();
    this->inn = 0;
    this->dir.first = "";
    this->dir.second = "";
}
details::details(const details &arg)
{
   this->list_tel = arg.list_tel;
   this->list_fax = arg.list_fax;
   this->post.first = arg.post.first;
   this->post.second = arg.post.second;
   this->inn = arg.inn;
   this->dir.first = arg.dir.first;
   this->dir.second = arg.dir.second;
}
bool details::operator == (const details &arg)
{
    if (
    this->list_tel == arg.list_tel &&
    this->list_fax == arg.list_fax &&
    this->post.first == arg.post.first &&
    this->post.second == arg.post.second &&
    this->inn == arg.inn &&
    this->dir.first == arg.dir.first &&
    this->dir.second == arg.dir.second
            ) {return true;}
    return false;
}
bool details::operator != (const details &arg)
{
    return !(*this == arg);
}
details& details::operator = (const details &arg)
{
    this->list_tel = arg.list_tel;
    this->list_fax = arg.list_fax;
    this->post.first = arg.post.first;
    this->post.second = arg.post.second;
    this->inn = arg.inn;
    this->dir.first = arg.dir.first;
    this->dir.second = arg.dir.second;
    return *this;
}
details details::null_details()
{
    details();
    return *this;
}
int details::add_tel(QString* arg)
{
    this->list_tel.append(*arg);
    return 0;
}
int details::add_fax(QString* arg)
{
    this->list_fax.append(*arg);
    return 0;
}
int details::add_tel(QString arg)
{
    this->list_tel.append(arg);
    return 0;
}
int details::add_fax(QString arg)
{
    this->list_fax.append(arg);
    return 0;
}
int details::set_tel_list(QList<QString>* arg)
{
        this->clear_tel();
        this->list_tel.append(*arg);
        return 0;
}
int details::set_fax_list(QList<QString>* arg)
{
    this->clear_fax();
    this->list_fax.append(*arg);
    return 0;
}
int details::set_tel_list(QList<QString> arg)
{
        this->clear_tel();
        this->list_tel.append(arg);
        return 0;
}
int details::set_fax_list(QList<QString> arg)
{
    this->clear_fax();
    this->list_fax.append(arg);
    return 0;
}
QList<QString> details::get_tel_list() const
{
    return this->list_tel;
}
QList<QString> details::get_fax_list() const
{
    return this->list_fax;
}

int details::clear_tel()
{
    this->list_tel.clear();
    return 0;
}
int details::clear_fax()
{
    this->list_fax.clear();
    return 0;
}
int details::del_n_tel(int arg)
{
    if (arg < this->list_tel.size()){
        this->list_tel.removeAt(arg);
        return 0;
    }
    return 1;
}
int details::del_top_tel()
{
    this->list_tel.removeLast();
    return 0;
}
int details::del_n_fax(int arg)
{
    if (arg < this->list_fax.size()){
        this->list_fax.removeAt(arg);
        return 0;
    }
    return 1;
}
int details::del_top_fax()
{
    this->list_fax.removeLast();
    return 0;
}
int details::set_re_post(address* arg)
{
    this->post.first = *arg;
    return 0;
}
int details::set_ur_post(address* arg)
{
    this->post.second = *arg;
    return 0;
}
address details::get_re_post() const
{
    return this->post.first;
}
address details::get_ur_post() const
{
    return this->post.second;
}
int details::set_inn(unsigned long long in)
{
    this->inn = in;
    return 0;
}
unsigned long long details::get_inn() const
{
    return this->inn;
}
int details::set_dir(QPair<QString, QString>* di)
{
    this->dir.first = di->first;
    this->dir.second = di->second;
    return 0;
}
int details::set_dir(QPair<QString, QString> di)
{
    this->dir.first = di.first;
    this->dir.second = di.second;
    return 0;
}
QPair<QString, QString> details::get_dir() const
{
    return this->dir;
}
QDomElement details::make_xml()
{
    QDomDocument ret_xml;

    QDomElement root = ret_xml.createElement("details");
        ret_xml.appendChild(root);

    QDomElement xml_tel = ret_xml.createElement("tel_list");
        root.appendChild(xml_tel);
        QList<QString>::iterator it = this->list_tel.begin();
        int i = 0;
        while (it != this->list_tel.end()) {
               QDomElement tel =  ret_xml.createElement("tel" + QString::number(i));
               QDomText tel_text = ret_xml.createTextNode(*it);
               i++;
               it++;
               xml_tel.appendChild(tel);
               tel.appendChild(tel_text);
        }

    QDomElement xml_fax = ret_xml.createElement("fax_list");
     root.appendChild(xml_fax);
          it = this->list_fax.begin();
          i = 0;
       while (it != this->list_fax.end()) {
           QDomElement fax =  ret_xml.createElement("fax" + QString::number(i));
           QDomText fax_text = ret_xml.createTextNode(*it);
           i++;
           it++;
           xml_fax.appendChild(fax);
           fax.appendChild(fax_text);
       }

    QDomElement xml_post = ret_xml.createElement("post");
        QDomElement re_post = ret_xml.createElement("re_post");
        QDomElement ur_post = ret_xml.createElement("ur_post");
        root.appendChild(xml_post);
            xml_post.appendChild(re_post);
            xml_post.appendChild(ur_post);
                re_post.appendChild(this->post.first.make_xml());
                ur_post.appendChild(this->post.second.make_xml());


    QDomElement xml_inn = ret_xml.createElement("inn");
        QDomText inn_text = ret_xml.createTextNode(QString::number(this->inn));
            root.appendChild(xml_inn);
                xml_inn.appendChild(inn_text);

    QDomElement main_dir = ret_xml.createElement("dir");
      QDomElement dol_dir = ret_xml.createElement("dol_dir");
      QDomElement name_dir = ret_xml.createElement("name_dir");
        QDomText dir_dol_text = ret_xml.createTextNode(this->dir.first);
        QDomText dir_name_text = ret_xml.createTextNode(this->dir.second);
            root.appendChild(main_dir);
            main_dir.appendChild(dol_dir);
            main_dir.appendChild(name_dir);
                dol_dir.appendChild(dir_dol_text);
                name_dir.appendChild(dir_name_text);
      return root;
}
int details::load_xml(QDomNode* arg)
{
    QDomNode lst = *arg;
    //QList<QString> list_tel;
    QDomElement lst_temp = lst.firstChildElement("tel_list");
    int i = 0;
    while (!lst_temp.firstChildElement("tel" + QString::number(i)).isNull()) {
        this->list_tel.append(lst_temp.firstChildElement("tel" + QString::number(i)).text());
        i++;
    }
   // QList<QString> list_fax;
    lst_temp = lst.firstChildElement("fax_list");
    i = 0;
    while (!lst_temp.firstChildElement("fax" + QString::number(i)).isNull()) {
        this->list_fax.append(lst_temp.firstChildElement("fax" + QString::number(i)).text());
        i++;
    }

    auto ret1 = lst.firstChildElement("post").firstChildElement("re_post").firstChildElement("address");
        this->post.first.load_xml(&ret1);
    auto ret2 = lst.firstChildElement("post").firstChildElement("ur_post").firstChildElement("address");
        this->post.second.load_xml(&ret2);

   this->inn = lst.firstChildElement("inn").text().toULongLong();
   QDomElement t_dir = lst.firstChildElement("dir");
        this->dir.first = t_dir.firstChildElement("dol_dir").text();
        this->dir.second = t_dir.firstChildElement("name_dir").text();

    return 0;
}

int details::load_db(){ return 0; }
int details::save_db(){ return 0; }
