#include "address.h"

address::address(const address &arg)
{
    country = arg.country;
    state = arg.state;
    state_class = arg.state_class;
    state_district = arg.state_district;
    city = arg.city;
    city_class = arg.city_class;
    district = arg.district;
    street = arg.street;
    street_class = arg.street_class;
    building = arg.building;
    office = arg.office;
    post_index = arg.post_index;
}
bool address::operator == (const address &arg)
{
    if (
            country == arg.country &&
            state == arg.state  &&
            state_class == arg.state_class &&
            state_district == arg.state_district &&
            city == arg.city &&
            city_class == arg.city_class &&
            district == arg.district &&
            street == arg.street &&
            street_class == arg.street_class &&
            building.first == arg.building.first &&
            building.second == arg.building.second &&
            office.first == arg.office.first &&
            office.second == arg.office.second &&
            post_index == arg.post_index
            ) {return true;}
    return false;
}
bool address::operator != (const address &arg)
{
     return !(*this == arg);
}
address& address::operator= (const address &arg)
{
    this->country = arg.country;
    this->state = arg.state;
    this->state_class = arg.state_class;
    this->state_district = arg.state_district;
    this->city = arg.city;
    this->city_class = arg.city_class;
    this->district = arg.district;
    this->street = arg.street;
    this->street_class = arg.street_class;
    this->building.first = arg.building.first;
    this->building.second = arg.building.second;
    this->office.first = arg.office.first;
    this->office.second = arg.office.second;
    this->post_index = arg.post_index;
    return (*this);
}
int address::clear_address()
{
    this->country = "";
    this->state = "";
    this->state_class = "";
    this->state_district = "";
    this->city = "";
    this->city_class = "";
    this->district = "";
    this->street = "";
    this->street_class = "";
    this->building.first = 0;
    this->building.second = "";
    this->office.first = 0;
    this->office.second = "";
    this->post_index = 0;
    return 0;
}
int address::set_country(QString* str)
{
    if (str->size() < 1000) {
        this->country = *str;
        return 0;
    }
    return 1;
}
QString address::get_country() const
{
    return this->country;
}
int address::set_state(QString* str)
{
    if (str->size() < 1000) {
        this->state = *str;
        return 0;
    }
    return 1;
}
QString address::get_state() const
{
    return this->state;
}
int address::set_city(QString* str)
{
    if (str->size() < 1000) {
        this->city = *str;
        return 0;
    }
    return 1;
}
QString address::get_city() const
{
    return this->city;
}
int address::set_state_class(QString* str)
{
    if (str->size() < 1000) {
        this->state_class = *str;
        return 0;
    }
    return 1;
}
QString address::get_state_class() const
{
    return this->state_class;
}
int address::set_state_distr(QString* str)
{
    if (str->size() < 1000) {
        this->state_district = *str;
        return 0;
    }
    return 1;
}
QString address::get_state_distr() const
{
    return this->state_district;
}
int address::set_city_class(QString* str)
{
    if (str->size() < 1000) {
        this->city_class = *str;
        return 0;
    }
    return 1;
}
QString address::get_city_class() const
{
    return this->city_class;
}
int address::set_district(QString* str)
{
    if (str->size() < 1000) {
        this->district = *str;
        return 0;
    }
    return 1;
}
QString address::get_district() const
{
    return this->district;
}
int address::set_street(QString* str)
{
    if (str->size() < 1000) {
        this->street = *str;
        return 0;
    }
    return 1;
}
QString address::get_street() const
{
    return this->street;
}
int address::set_street_class(QString* str)
{
    if (str->size() < 1000) {
        this->street_class = *str;
        return 0;
    }
    return 1;
}
QString address::get_street_class() const
{
    return this->street_class;
}
int address::set_building(QPair<int, QString> *pr)
{
    if ((pr->second.size() < 1000)) {
        this->building.first = pr->first;
        this->building.second = pr->second;
        return 0;
    }
    return 1;
}
QPair<int, QString> address::get_building() const
{
    return this->building;
}
QPair<int, QString> address::get_office() const
{
    return this->office;
}
int address::set_office(QPair<int, QString> *pr)
{
    if ((pr->second.size() < 1000)) {
        this->office.first = pr->first;
        this->office.second = pr->second;
        return 0;
    }
    return 1;
}
unsigned int address::get_post_index() const
{
    return this->post_index;
}
int address::set_post_index(unsigned int ind)
{
 if (ind < 999999999){
     this->post_index = ind;
     return 0;
 }
 return 1;
}
QString address::get_adr_str() const
{
    QString ret_st;
    if (this->country != "") {ret_st += (this->country + " ");}
    if (this->state_class != "") {ret_st += (this->state_class + " ");}
    if (this->state != ""){ret_st += (this->state + " ");}
    if (this->state_district != ""){ret_st += (this->state_district + " ");}
    if (this->city_class != ""){ret_st += (this->city_class + " ");}
    if (this->city != ""){ret_st += (this->city + " ");}
    if (this->district != ""){ret_st += (this->district + " ");}
    if (this->street != ""){ret_st += (this->street + " ");}
    if (this->street_class != ""){ret_st += (this->street_class + " ");}
    if (this->building.first != 0){ret_st += (QString::number(this->building.first) + " ");}
    if (this->building.second != ""){ret_st += (this->building.second + " ");}
    if (this->office.first != 0){ret_st += (QString::number(this->office.first) + " ");}
    if (this->office.second != ""){ret_st += (this->office.second + " ");}
    if (this->post_index != 0){ret_st += ("Индекс: " + QString::number(this->post_index) + " ");}
    return ret_st;
}
QString address::get_adr_str2() const
{
    QString ret_st;
    if (this->post_index != 0){ret_st += QString::number(this->post_index) + ", ";}
    if (this->country != "") {ret_st += (this->country + ", ");}
    if (this->state_class != "") {ret_st += (this->state_class + " ");}
    if (this->state != ""){ret_st += (this->state + ", ");}
    if (this->state_district != ""){ret_st += (this->state_district + ", ");}
    if (this->city_class != ""){ret_st += (this->city_class + " ");}
    if (this->city != ""){ret_st += (this->city + ", ");}
    if (this->district != ""){ret_st += (this->district + ", ");}
    if (this->street_class != ""){ret_st += (this->street_class + " ");}
    if (this->street != ""){ret_st += (this->street + ", ");}
    if (this->building.first != 0){ret_st += ("строение " + QString::number(this->building.first) + " ");}
    if (this->building.second != ""){ret_st += (this->building.second + ", ");}
    if (this->office.first != 0){ret_st += ("помещение " + QString::number(this->office.first) + ", ");}
    if (this->office.second != ""){ret_st += (this->office.second + ". ");}
    return ret_st;
}
QString address::get_adr_str3() const
{
    QString ret_st;
    if (this->post_index != 0){ret_st += QString::number(this->post_index) + ", ";}
    if (this->state_class != "") {ret_st += (this->state_class + " ");}
    if (this->state != ""){ret_st += (this->state + ", ");}
    if (this->state_district != ""){ret_st += (this->state_district + ", ");}
    if (this->city_class != ""){ret_st += (this->city_class + " ");}
    if (this->city != ""){ret_st += (this->city + ", ");}
    if (this->district != ""){ret_st += (this->district + ", ");}
    if (this->street_class != ""){ret_st += (this->street_class + " ");}
    if (this->street != ""){ret_st += (this->street + ", ");}
    if (this->building.first != 0){ret_st += (QString::number(this->building.first) + " ");}
    if (this->building.second != ""){ret_st += (this->building.second + ", ");}
    if (this->office.first != 0){ret_st += ("офис " + QString::number(this->office.first) + ", ");}
    if (this->office.second != ""){ret_st += (this->office.second + ". ");}
    return ret_st;
}
int address::set_office_num(int arg)
{
    this->office.first = arg;
    return 0;
}
int address::set_building_num(int arg)
{
    this->building.first = arg;
    return 0;
}
int address::set_office_lit(QString* arg)
{
    this->office.second = *arg;
    return 0;
}
int address::set_building_lit(QString* arg)
{
    this->building.second = *arg;
    return 0;
}
int address::get_office_num() const
{
    return this->office.first;
}
int address::get_building_num() const
{
    return this->building.first;
}
QString address::get_office_lit() const
{
    return this->office.second;
}
QString address::get_building_lit() const
{
    return this->building.second;
}
// Определение перегруженных функций ввода
int address::set_country(const QString &str)
{
    if (str.size() < 1000) {
        this->country = str;
        return 0;
    }
    return 1;
}
int address::set_state(const QString &str)
{
    if (str.size() < 1000) {
        this->state = str;
        return 0;
    }
    return 1;
}
int address::set_state_distr(const QString &str)
{
    if (str.size() < 1000) {
        this->state_district = str;
        return 0;
    }
    return 1;
}
int address::set_city(const QString &str)
{
    if (str.size() < 1000) {
        this->city = str;
        return 0;
    }
    return 1;
}
int address::set_district(const QString &str)
{
    if (str.size() < 1000) {
        this->district = str;
        return 0;
    }
    return 1;
}
int address::set_street(const QString &str)
{
    if (str.size() < 1000) {
        this->street = str;
        return 0;
    }
    return 1;
}
int address::set_street_class(const QString &str)
{
    if (str.size() < 1000) {
        this->street_class = str;
        return 0;
    }
    return 1;
}
int address::set_building(QPair<int, QString> pr)
{
    if (pr.second.size() < 100) {
        this->building.second = pr.second;
        this->building.first = pr.first;
        return 0;
    }
    return 1;
}
int address::set_office(QPair<int, QString> pr)
{
    if (pr.second.size() < 100) {
        this->office.second = pr.second;
        this->office.first = pr.first;
        return 0;
    }
    return 1;
}
int address::set_state_class(const QString &str)
{
    if (str.size() < 1000) {
        this->state_class = str;
        return 0;
    }
    return 1;
}
int address::set_city_class(const QString &str)
{
    if (str.size() < 1000) {
        this->city_class = str;
        return 0;
    }
    return 1;
}
int address::set_office_lit(const QString &str)
{
    if (str.size() < 1000) {
        this->office.second = str;
        return 0;
    }
    return 1;
}
int address::set_building_lit(const QString &str)
{
    if (str.size() < 1000) {
        this->building.second = str;
        return 0;
    }
    return 1;
}
// Конец определение перегруженных функций ввода
int address::load_xml(QDomNode *my_dom)
{   
    QDomNode root = *my_dom;
    this->country = root.firstChildElement("country").text();
    this->state = root.firstChildElement("state").text();
    this->state_district = root.firstChildElement("state_distr").text();
    this->city = root.firstChildElement("city").text();   
    this->state_class = root.firstChildElement("state_class").text();
    this->city_class = root.firstChildElement("city_class").text();
    this->district = root.firstChildElement("district").text();
    this->street = root.firstChildElement("street").text();
    this->street_class = root.firstChildElement("street_class").text();
    QDomElement bld = root.firstChildElement("building");
           this->building.first = bld.firstChildElement("nom").text().toInt();
           this->building.second = bld.firstChildElement("lit").text();
    bld = root.firstChildElement("office");
           this->office.first = bld.firstChildElement("nom").text().toInt();
           this->office.second = bld.firstChildElement("lit").text();
    this->post_index = root.firstChildElement("post_index").text().toUInt();
    return 0;
}
QDomElement address::make_xml() const
{
    QDomDocument ret_xml;

    QDomElement root = ret_xml.createElement("address");

    QDomElement xml_country = ret_xml.createElement("country");
        QDomText country_text = ret_xml.createTextNode(this->country);

    QDomElement xml_state = ret_xml.createElement("state");
        QDomText state_text = ret_xml.createTextNode(this->state);

    QDomElement xml_state_class = ret_xml.createElement("state_class");
        QDomText state_text_class = ret_xml.createTextNode(this->state_class);

    QDomElement xml_state_distr = ret_xml.createElement("state_distr");
        QDomText state_text_distr = ret_xml.createTextNode(this->state_district);

    QDomElement xml_city = ret_xml.createElement("city");
        QDomText city_text = ret_xml.createTextNode(this->city);

    QDomElement xml_city_class = ret_xml.createElement("city_class");
        QDomText city_text_class = ret_xml.createTextNode(this->city_class);

    QDomElement xml_district = ret_xml.createElement("district");
        QDomText district_text = ret_xml.createTextNode(this->district);

    QDomElement xml_street = ret_xml.createElement("street");
        QDomText street_text = ret_xml.createTextNode(this->street);

    QDomElement xml_street_class = ret_xml.createElement("street_class");
        QDomText street_text_class = ret_xml.createTextNode(this->street_class);

    QDomElement xml_building = ret_xml.createElement("building");    
        QDomElement xml_building_nom = ret_xml.createElement("nom");
            QDomText building_nom_text = ret_xml.createTextNode(QString::number(this->building.first));
        QDomElement xml_building_lit = ret_xml.createElement("lit");
            QDomText building_lit_text = ret_xml.createTextNode(this->building.second);

    QDomElement xml_office = ret_xml.createElement("office");
        QDomElement xml_office_nom = ret_xml.createElement("nom");
            QDomText office_nom_text = ret_xml.createTextNode(QString::number(this->office.first));
        QDomElement xml_office_lit = ret_xml.createElement("lit");
            QDomText office_lit_text = ret_xml.createTextNode(this->office.second);

    QDomElement xml_post_index = ret_xml.createElement("post_index");
        QDomText post_index_text = ret_xml.createTextNode(QString::number(this->post_index));

    ret_xml.appendChild(root);

    root.appendChild(xml_country);
        xml_country.appendChild(country_text);
    root.appendChild(xml_state);
        xml_state.appendChild(state_text);     
    root.appendChild(xml_state_class);
        xml_state_class.appendChild(state_text_class);
    root.appendChild(xml_state_distr);
        xml_state_distr.appendChild(state_text_distr);
    root.appendChild(xml_city);
        xml_city.appendChild(city_text);        
    root.appendChild(xml_city_class);
        xml_city_class.appendChild(city_text_class);
    root.appendChild(xml_district);
        xml_district.appendChild(district_text);
    root.appendChild(xml_street);
        xml_street.appendChild(street_text);
    root.appendChild(xml_street_class);
        xml_street_class.appendChild(street_text_class);

    root.appendChild(xml_building);
        xml_building.appendChild(xml_building_nom);
            xml_building_nom.appendChild(building_nom_text);
        xml_building.appendChild(xml_building_lit);
            xml_building_lit.appendChild(building_lit_text);

   root.appendChild(xml_office);
        xml_office.appendChild(xml_office_nom);
            xml_office_nom.appendChild(office_nom_text);
        xml_office.appendChild(xml_office_lit);
            xml_office_lit.appendChild(office_lit_text);

   root.appendChild(xml_post_index);
       xml_post_index.appendChild(post_index_text);

   return root;
}
int address::load_db(){ return 0; }
int address::save_db() const{ return 0; }
