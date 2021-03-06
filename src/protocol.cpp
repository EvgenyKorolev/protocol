#include "protocol.h"
#include "obj.h"

protocol::protocol(obj *par)
{
    if (uin == "") uin = prt_fun::create_uin();
    parent = par;
    dr = par->get_bd_name();
}
protocol::protocol(const QString& uin)
{
    parent = nullptr;
    this->uin = uin;
}
protocol::protocol(protocol* prt)
{
    parent = prt->parent;
    prt_number = prt->prt_number;
    prt_date = prt->prt_date;
    prt_type = prt->prt_type;
    file = prt->file;
    uin = prt->uin;
}
protocol::protocol(protocol& prt)
{
    parent = prt.parent;
    prt_number = prt.prt_number;
    prt_date = prt.prt_date;
    prt_type = prt.prt_type;
    file = prt.file;
    uin = prt.uin;
}
protocol::protocol(protocol&& prt)
{
    parent = std::move(prt.parent);
    prt_number = std::move(prt.prt_number);
    prt_date = std::move(prt.prt_date);
    prt_type = std::move(prt.prt_type);
    file = std::move(prt.file);
    uin = std::move(prt.uin);
}
protocol& protocol::operator=(protocol& prt)
{
    parent = prt.parent;
    prt_number = prt.prt_number;
    prt_date = prt.prt_date;
    prt_type = prt.prt_type;
    file = prt.file;
    uin = prt.uin;
    return *this;
}
protocol&& protocol::operator=(protocol&& prt)
{
    parent = std::move(prt.parent);
    prt_number = std::move(prt.prt_number);
    prt_date = std::move(prt.prt_date);
    prt_type = std::move(prt.prt_type);
    file = std::move(prt.file);
    uin = std::move(prt.uin);
    return std::move(*this);
}
bool protocol::set_data(const protocol& arg)
{
    if (parent == nullptr && uin == "") return false;
    prt_number = arg.prt_number;
    prt_date = arg.prt_date;
    prt_type = arg.prt_type;
    file = arg.file;
    dr = arg.file;
    QString tmp1 = arg.get_prttxt();
    QString tmp2 = arg.get_endtxt();
    prt_fun::add_prt(arg.get_dr(), this, tmp1, tmp2);
    return true;
}
protocol::protocol(QDomNode *arg)
{
    this->load_xml(arg);
}
protocol::~protocol()
{
    QList<protocol*> tmp = parent->get_pro_list();
    int z = tmp.indexOf(this);
    if (z != -1){
        parent->remove_n_pro(z);
    }
}
bool protocol::erase()
{
    if (parent != nullptr) return prt_fun::delete_prt(parent->get_bd_name(), uin);
    return prt_fun::delete_prt(dr, uin);
}
void protocol::set_parent(obj* par)
{
    parent = par;
    dr = par->get_bd_name();
}
obj* protocol::get_parent() const
{
    return  parent;
}
void protocol::set_number(const QString& arg)
{
    prt_number = arg;
}
void protocol::set_date(const QDate& arg)
{
    prt_date = arg;
}
void protocol::set_type(const QString& arg)
{
    prt_type = arg;
}
void protocol::set_prttxt(const QString& arg)
{
     prt_fun::set_prt_text(parent->get_bd_name(), uin, arg);
}
void protocol::set_endtxt(const QString& arg)
{
    prt_fun::set_end_text(parent->get_bd_name(), uin, arg);
}
void protocol::set_file(const QString& arg)
{
    file = arg;
}
void protocol::set_uin(const QString& arg)
{
    uin = arg;
}
QString protocol::get_number() const
{
    return prt_number;
}
QDate protocol::get_date() const
{
    return prt_date;
}
QString protocol::get_type() const
{
    return prt_type;
}
QString protocol::get_dr() const
{
    if (!(parent == nullptr)) return parent->get_bd_name();
    return dr;
}
QString protocol::get_prttxt() const
{
    return prt_fun::get_prt_text(parent->get_bd_name(), uin);
}
QString protocol::get_endtxt() const
{
    return prt_fun::get_end_text(parent->get_bd_name(), uin);
}
QString protocol::get_file() const
{
    return file;
}
QString protocol::get_uin() const
{
    return uin;
}
QDomElement protocol::make_xml() const
{
    QDomDocument ret_xml;
    QDomElement root = ret_xml.createElement("protocol");
         ret_xml.appendChild(root);

    QDomElement xml_number = ret_xml.createElement("prt_number");
     QDomText xml_number_text = ret_xml.createTextNode(prt_number);
        root.appendChild(xml_number);
        xml_number.appendChild(xml_number_text);

    QDomElement xml_file = ret_xml.createElement("file");
     QDomText xml_file_text = ret_xml.createTextNode(file);
        root.appendChild(xml_file);
        xml_file.appendChild(xml_file_text);

    QDomElement xml_uin = ret_xml.createElement("uin");
     QDomText xml_uin_text = ret_xml.createTextNode(uin);
        root.appendChild(xml_uin);
        xml_uin.appendChild(xml_uin_text);

     QDomElement xml_type = ret_xml.createElement("prt_type");
       QDomText xml_type_text = ret_xml.createTextNode(prt_type);
          root.appendChild(xml_type);
           xml_type.appendChild(xml_type_text);

     root.appendChild(my_fnc::date_to_xml(prt_date));

    return root;
}
int protocol::load_xml(QDomNode *arg)
{
    QDomNode root = *arg;
    prt_number = root.firstChildElement("prt_number").text();
    my_fnc::xml_to_date(root.firstChildElement("date"), prt_date);
    prt_type = root.firstChildElement("prt_type").text();
    file = root.firstChildElement("file").text();
    uin = root.firstChildElement("uin").text();
    return 0;
}
