#include "protocol.h"

protocol::protocol(obj *par)
{
    parent = par;
}
protocol::~protocol()
{

}
protocol::protocol(protocol& prt)
{
    parent = prt.parent;
    prt_number = prt.prt_number;
    prt_date = prt.prt_date;
    prt_type = prt.prt_type;
    prt_text = prt.prt_text;
}
protocol::protocol(protocol&& prt)
{
    parent = std::move(prt.parent);
    prt_number = std::move(prt.prt_number);
    prt_date = std::move(prt.prt_date);
    prt_type = std::move(prt.prt_type);
    prt_text = std::move(prt.prt_text);
}
protocol& protocol::operator=(protocol& prt)
{
    parent = prt.parent;
    prt_number = prt.prt_number;
    prt_date = prt.prt_date;
    prt_type = prt.prt_type;
    prt_text = prt.prt_text;
    return *this;
}
protocol&& protocol::operator=(protocol&& prt)
{
    parent = std::move(prt.parent);
    prt_number = std::move(prt.prt_number);
    prt_date = std::move(prt.prt_date);
    prt_type = std::move(prt.prt_type);
    prt_text = std::move(prt.prt_text);
    return std::move(*this);
}
void protocol::set_parent(obj* par)
{
    parent = par;
}
obj* protocol::get_parent()
{
    return  parent;
}
QDomElement protocol::make_xml()
{
    QDomDocument ret_xml;
     QDomElement root = ret_xml.createElement("pro");
    return root;
}

int protocol::load_xml(QDomDocument *arg, obj *obt)
{
    Q_UNUSED(arg)
    Q_UNUSED(obt)
    return 0;
}
