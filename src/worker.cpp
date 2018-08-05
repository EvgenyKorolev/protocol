#include "worker.h"

worker::worker()
{
    this->name = "";
    this->surname = "";
    this->fname = "";
    this->position = "";
    // laboratory job;
    this->tel = "";
    this->post = "";
    this->login = "";
    this->pass = "";
    this->adr = address();
}
worker worker::null_worker()
{
    worker();
    return *this;
}
int worker::set_name(QString *arg)
{
    if (arg->size() < 1000) {
        this->name = *arg;
        return 0;
    }
    return 1;
}
int worker::set_name(QString arg)
{
    if (arg.size() < 1000) {
        this->name = arg;
        return 0;
    }
    return 1;
}
QString worker::get_name() const
{
    return this->name;
}
int worker::set_surname(QString *arg)
{
    if (arg->size() < 1000) {
        this->surname = *arg;
        return 0;
    }
    return 1;
}
int worker::set_surname(QString arg)
{
    if (arg.size() < 1000) {
        this->surname = arg;
        return 0;
    }
    return 1;
}
QString worker::get_surname() const
{
    return this->surname;
}
int worker::set_fname(QString *arg)
{
    if (arg->size() < 1000) {
        this->fname = *arg;
        return 0;
    }
    return 1;
}
int worker::set_fname(QString arg)
{
    if (arg.size() < 1000) {
        this->fname = arg;
        return 0;
    }
    return 1;
}
QString worker::get_fname() const
{
    return this->fname;
}
int worker::set_position(QString *arg)
{
    if (arg->size() < 1000) {
        this->position = *arg;
        return 0;
    }
    return 1;
}
int worker::set_position(QString arg)
{
    if (arg.size() < 1000) {
        this->position = arg;
        return 0;
    }
    return 1;
}
QString worker::get_position() const
{
    return this->position;
}
int worker::set_tel(QString *arg)
{
    if (arg->size() < 1000) {
        this->tel = *arg;
        return 0;
    }
    return 1;
}
int worker::set_tel(QString arg)
{
    if (arg.size() < 1000) {
        this->tel = arg;
        return 0;
    }
    return 1;
}
QString worker::get_tel() const
{
    return this->tel;
}
int worker::set_post(QString *arg)
{
    if (arg->size() < 1000) {
        this->post = *arg;
        return 0;
    }
    return 1;
}
int worker::set_post(QString arg)
{
    if (arg.size() < 1000) {
        this->post = arg;
        return 0;
    }
    return 1;
}
QString worker::get_post() const
{
    return this->post;
}
int worker::set_login(QString *arg, QString *arg2)
{
    if ((arg->size() < 1000) && (this->test_pass(arg2))) {
        this->login = *arg;
        return 0;
    }
    return 1;
}
int worker::set_login(QString arg, QString arg2)
{
    if ((arg.size() < 1000) && (this->test_pass(arg2))) {
        this->login = arg;
        return 0;
    }
    return 1;
}
QString worker::get_login() const
{
    return this->login;
}
int worker::set_pass(QString *arg, QString *arg2)
{
    if ((arg->size() < 1000) && (this->test_pass(arg2))) {
        this->pass = *arg;
        return 0;
    }
    return 1;
}
int worker::set_pass(QString arg, QString arg2)
{
    if ((arg.size() < 1000) && (this->test_pass(arg2))) {
        this->pass = arg;
        return 0;
    }
    return 1;
}
bool worker::test_pass(QString *arg)
{
    if (*arg == this->pass) {return true;}
    return false;
}
bool worker::test_pass(QString arg)
{
    if (arg == this->pass) {return true;}
    return false;
}
int worker::set_adr(address *arg)
{
    this->adr = *arg;
    return 0;
}
int worker::set_adr(address arg)
{
    this->adr = arg;
    return 0;
}
address worker::get_adr()
{
    return this->adr;
}

int worker::load_xml(QDomNode *arg)
{
    QDomNode lst = *arg;

    this->name = lst.firstChildElement("name").text();
    this->surname = lst.firstChildElement("surname").text();
    this->fname = lst.firstChildElement("fname").text();
    this->position = lst.firstChildElement("position").text();
    this->tel = lst.firstChildElement("tel").text();
    this->post = lst.firstChildElement("post").text();
    this->login = lst.firstChildElement("login").text();
    this->pass = lst.firstChildElement("pass").text();

    QDomDocument* tmpd = new QDomDocument;
     tmpd->appendChild(lst.firstChildElement("address"));
         this->adr.load_xml(tmpd);
     delete tmpd;
    return 0;
}
QDomElement worker::make_xml()
{
    QDomDocument ret_xml;

    QDomElement root = ret_xml.createElement("worker");
        ret_xml.appendChild(root);

    QDomElement xml_name = ret_xml.createElement("name");
         QDomText xml_name_text = ret_xml.createTextNode(this->name);
            root.appendChild(xml_name);
            xml_name.appendChild(xml_name_text);
    QDomElement xml_surname = ret_xml.createElement("surname");
        QDomText xml_surname_text = ret_xml.createTextNode(this->surname);
            root.appendChild(xml_surname);
            xml_surname.appendChild(xml_surname_text);
    QDomElement xml_fname = ret_xml.createElement("fname");
        QDomText xml_fname_text = ret_xml.createTextNode(this->fname);
            root.appendChild(xml_fname);
            xml_fname.appendChild(xml_fname_text);
    QDomElement xml_position = ret_xml.createElement("position");
        QDomText xml_position_text = ret_xml.createTextNode(this->position);
            root.appendChild(xml_position);
            xml_position.appendChild(xml_position_text);
    QDomElement xml_tel = ret_xml.createElement("tel");
        QDomText xml_tel_text = ret_xml.createTextNode(this->tel);
            root.appendChild(xml_tel);
            xml_tel.appendChild(xml_tel_text);
    QDomElement xml_post = ret_xml.createElement("post");
        QDomText xml_post_text = ret_xml.createTextNode(this->post);
            root.appendChild(xml_post);
            xml_post.appendChild(xml_post_text);
    QDomElement xml_login = ret_xml.createElement("login");
        QDomText xml_login_text = ret_xml.createTextNode(this->login);
            root.appendChild(xml_login);
            xml_login.appendChild(xml_login_text);
    QDomElement xml_pass = ret_xml.createElement("pass");
        QDomText xml_pass_text = ret_xml.createTextNode(this->pass);
            root.appendChild(xml_pass);
            xml_pass.appendChild(xml_pass_text);

            root.appendChild(this->adr.make_xml());

    return root;

}




int worker::load_db()
{
 return 0;
}
int worker::save_db()
{
    return 0;
}
