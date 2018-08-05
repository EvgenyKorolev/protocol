#include "apparaturs.h"

apparaturs::apparaturs()
{
    QList<QPair<QPair<QString, QDate>, QDate>> tmpl;
    _name = "";
    _mdata.setDate(1, 1, 1);
    _verification = tmpl;
    _type = "";
    _mnom = "";
    _cls = "";
    _uniq = "0";
}
apparaturs::apparaturs(apparaturs *arg)
{
    _name = arg->get_name();
    _mdata = arg->get_mdata();
    _verification = arg->get_verification_list();
    _type = arg->get_type();
    _mnom = arg->get_mnom();
    _cls = arg->get_clas();
    _uniq = arg->get_uniq();
}
void apparaturs::init(apparaturs *arg)
{
    _name = arg->get_name();
    _mdata = arg->get_mdata();
    _verification = arg->get_verification_list();
    _type = arg->get_type();
    _mnom = arg->get_mnom();
    _cls = arg->get_clas();
    _uniq = arg->get_uniq();
}
apparaturs::apparaturs(const apparaturs& arg)
{
    _name = arg.get_name();
    _mdata = arg.get_mdata();
    _verification = arg.get_verification_list();
    _type = arg.get_type();
    _mnom = arg.get_mnom();
    _cls = arg.get_clas();
    _uniq = arg.get_uniq();
}
int apparaturs::set_name(QString *arg)
{
    if (arg->size() < 1000) {
        _name = *arg;
        return 0;
    }
    return 1;
}
void apparaturs::set_uniq(QString arg)
{
    _uniq = arg;
}
QString apparaturs::get_uniq() const
{
    return _uniq;
}
int apparaturs::set_name(QString arg)
{
    if (arg.size() < 1000) {
        _name = arg;
        return 0;
    }
    return 1;
}
QString apparaturs::get_name() const
{
    return _name;
}
int apparaturs::set_mdata(QDate *arg)
{
    _mdata = *arg;
    return 0;
}
int apparaturs::set_mdata(QDate arg)
{
    _mdata = arg;
    return 0;
}
QDate apparaturs::get_mdata() const
{
    return _mdata;
}

int apparaturs::add_verification(QPair<QPair<QString, QDate>, QDate> *arg)
{
    _verification.append(*arg);
    return 0;
}
int apparaturs::set_verification_list(QList<QPair<QPair<QString, QDate>, QDate>>* arg)
{
    this->clear_verification();
    _verification.append(*arg);
    return 0;
}
QList<QPair<QPair<QString, QDate>, QDate>> apparaturs::get_verification_list() const
{
    return _verification;
}
int apparaturs::clear_verification()
{
    _verification.clear();
    return 0;
}
int apparaturs::set_type(QString *arg)
{
    if (arg->size() < 1000) {
        _type = *arg;
        return 0;
    }
    return 1;
}
int apparaturs::set_type(QString arg)
{
    if (arg.size() < 1000) {
        _type = arg;
        return 0;
    }
    return 1;
}
QString apparaturs::get_type() const
{
    return _type;
}
int apparaturs::set_mnom(QString *arg)
{
    if (arg->size() < 1000) {
        _mnom = *arg;
        return 0;
    }
    return 1;
}
int apparaturs::set_mnom(QString arg)
{
    if (arg.size() < 1000) {
        _mnom = arg;
        return 0;
    }
    return 1;
}
QString apparaturs::get_mnom() const
{
    return _mnom;
}

int apparaturs::load_xml_1(QDomNode *my_dom)
{
    QDomNode lst = *my_dom;

    _name = lst.firstChildElement("name").text();
    _type = lst.firstChildElement("type").text();
    _mnom = lst.firstChildElement("mnom").text();
    _cls = lst.firstChildElement("clas").text();
    _uniq = lst.firstChildElement("uniq").text();
    my_fnc::xml_to_date(lst.firstChildElement("date"), _mdata);

    QDomElement lst_temp = lst.firstChildElement("verification");
    int i = 0;
    QPair<QPair<QString, QDate>, QDate> pr;
    while (!lst_temp.firstChildElement("ver" + QString::number(i)).isNull()) {
        pr.first.first = lst_temp.firstChildElement("ver" + QString::number(i)).firstChildElement("numver").text();
        my_fnc::xml_to_date(lst_temp.firstChildElement("ver" + QString::number(i)).firstChildElement("ver_date").firstChildElement("date"), pr.first.second);
        my_fnc::xml_to_date(lst_temp.firstChildElement("ver" + QString::number(i)).firstChildElement("ver_next_date").firstChildElement("date"), pr.second);
        _verification.append(pr);
        ++i;
    }
    return 0;
}
QString apparaturs::get_clas() const
{
    return _cls;
}
void apparaturs::set_clas(QString arg)
{
    _cls = arg;
}
QDate apparaturs::get_real_ver()
{
    QDate ret;
    if (_verification.size() > 0){
        QList<QPair<QPair<QString, QDate>, QDate>>::iterator it = _verification.begin();
        ret = (*it).first.second;
        while (it != _verification.end()){
            if (ret < (*it).first.second) { ret = (*it).first.second;}
            ++it;
        }
    } else {
        ret.setDate(1, 1, 1970);}
    return ret;
}
QDomElement apparaturs::make_xml_1()
{
    QDomDocument xml_ret;
    QDomElement root = xml_ret.createElement("apparaturs1");
    xml_ret.appendChild(root);

    QDomElement xml_name = xml_ret.createElement("name");
        QDomText xml_name_text = xml_ret.createTextNode(_name);
            root.appendChild(xml_name);
            xml_name.appendChild(xml_name_text);

     QDomElement xml_type = xml_ret.createElement("type");
         QDomText xml_type_text = xml_ret.createTextNode(_type);
             root.appendChild(xml_type);
             xml_type.appendChild(xml_type_text);

     QDomElement xml_clas = xml_ret.createElement("clas");
         QDomText xml_clas_text = xml_ret.createTextNode(_cls);
             root.appendChild(xml_clas);
             xml_clas.appendChild(xml_clas_text);

     QDomElement xml_uniq = xml_ret.createElement("uniq");
          QDomText xml_uniq_text = xml_ret.createTextNode(_uniq);
              root.appendChild(xml_uniq);
              xml_uniq.appendChild(xml_uniq_text);

     QDomElement xml_mnom = xml_ret.createElement("mnom");
         QDomText xml_mnom_text = xml_ret.createTextNode(_mnom);
             root.appendChild(xml_mnom);
             xml_mnom.appendChild(xml_mnom_text);

        root.appendChild(my_fnc::date_to_xml(_mdata));

     QList<QPair<QPair<QString, QDate>, QDate>>::iterator it = _verification.begin();

     QDomElement xml_ver = xml_ret.createElement("verification");
        root.appendChild(xml_ver);
        int i = 0;
        while (it != _verification.end())
        {
            QDomElement xml_number = xml_ret.createElement("ver" + QString::number(i));
            QDomElement xml_numver = xml_ret.createElement("numver");
            QDomElement xml_ver_date = xml_ret.createElement("ver_date");
            QDomElement xml_ver_next_date = xml_ret.createElement("ver_next_date");
            QDomText xml_numver_text = xml_ret.createTextNode(it->first.first);

                xml_ver.appendChild(xml_number);
                xml_number.appendChild(xml_numver);
                    xml_numver.appendChild(xml_numver_text);
                xml_number.appendChild(xml_ver_date);
                    xml_ver_date.appendChild(my_fnc::date_to_xml(it->first.second));
                xml_number.appendChild(xml_ver_next_date);
                    xml_ver_next_date.appendChild(my_fnc::date_to_xml(it->second));
            ++it;
            ++i;
        }
    return root;
}
void apparaturs::load_xml(QDomNode *my_dom)
{
    this->load_xml_1(my_dom);
}
QDomElement apparaturs::make_xml()
{
    return this->make_xml_1();
}
int apparaturs::load_db_1(){return 0;}
int apparaturs::save_db_1(){return 0;}
