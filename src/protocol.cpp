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
    parent = prt.get_parent();
}
protocol::protocol(protocol&& prt)
{
    parent = std::move(prt.parent);
}
protocol& protocol::operator=(protocol& prt)
{
    parent = prt.get_parent();
    return *this;
}
protocol&& protocol::operator=(protocol&& prt)
{
    parent = std::move(prt.parent);
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
