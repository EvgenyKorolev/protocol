#include "protocol.h"

protocol::protocol(obj *par, const QString &arg)
{
    parent = par;
    dr = arg;
}
protocol::protocol(protocol& prt)
{
    parent = prt.parent;
    prt_number = prt.prt_number;
    prt_date = prt.prt_date;
    prt_type = prt.prt_type;
    prt_text = prt.prt_text;
    end_text = prt.end_text;
}
protocol::protocol(protocol&& prt)
{
    parent = std::move(prt.parent);
    prt_number = std::move(prt.prt_number);
    prt_date = std::move(prt.prt_date);
    prt_type = std::move(prt.prt_type);
    prt_text = std::move(prt.prt_text);
    end_text = std::move(prt.end_text);
}
protocol& protocol::operator=(protocol& prt)
{
    parent = prt.parent;
    prt_number = prt.prt_number;
    prt_date = prt.prt_date;
    prt_type = prt.prt_type;
    prt_text = prt.prt_text;
    end_text = prt.end_text;
    return *this;
}
protocol&& protocol::operator=(protocol&& prt)
{
    parent = std::move(prt.parent);
    prt_number = std::move(prt.prt_number);
    prt_date = std::move(prt.prt_date);
    prt_type = std::move(prt.prt_type);
    prt_text = std::move(prt.prt_text);
    end_text = std::move(prt.end_text);
    return std::move(*this);
}
void protocol::set_parent(obj* par)
{
    parent = par;
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
    prt_text = arg;
}
void protocol::set_endtxt(const QString& arg)
{
    end_text = arg;
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
QString protocol::get_prttxt() const
{
    return prt_text;
}
QString protocol::get_endtxt() const
{
    return end_text;
}
QString protocol::ret_srctxt() const
{

}
QString protocol::ret_endtxt() const
{

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

     QDomElement xml_type = ret_xml.createElement("prt_type");
       QDomText xml_type_text = ret_xml.createTextNode(prt_type);
          root.appendChild(xml_type);
           xml_type.appendChild(xml_type_text);

     QDomElement xml_prt_text = ret_xml.createElement("prt_text");
       QDomText xml_prt_text_text = ret_xml.createTextNode(prt_text);
          root.appendChild(xml_prt_text);
          xml_prt_text.appendChild(xml_prt_text_text);

     QDomElement xml_end_text = ret_xml.createElement("end_text");
       QDomText xml_end_text_text = ret_xml.createTextNode(end_text);
          root.appendChild(xml_end_text);
          xml_end_text.appendChild(xml_end_text_text);

     QDomElement xml_dr = ret_xml.createElement("dr");
       QDomText xml_dr_text = ret_xml.createTextNode(dr);
          root.appendChild(xml_dr);
          xml_dr.appendChild(xml_dr_text);

     root.appendChild(my_fnc::date_to_xml(prt_date));

    return root;
}
int protocol::load_xml(QDomDocument *arg)
{
    QDomNode root = *arg;
    prt_number = root.firstChildElement("prt_number").text();
    my_fnc::xml_to_date(root.firstChildElement("date"), prt_date);
    prt_type = root.firstChildElement("prt_type").text();
    prt_text = root.firstChildElement("prt_text").text();
    end_text = root.firstChildElement("end_text").text();
    dr = root.firstChildElement("dr").text();
    return 0;
}
