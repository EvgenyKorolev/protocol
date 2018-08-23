#include "type_adapter.h"

type_adapter::type_adapter(const QList<type_obj>& arg)
{
    data_list = arg;
}
void type_adapter::add_type(const QString& arg)
{
    type_const_loader& tmpl = type_const_loader::getInstance();
    data_list.append(tmpl.get_obj(arg));
}
QString type_adapter::get_var(const QString &cls, const QString &varname)
{

    QList<QString> tmpvs = tmpl.get_var_list();
    QList<QString>::iterator it = std::find(tmpvs.begin(), tmpvs.end(), cls);
    if (it == tmpvs.end()) return  "NULL";
    type_obj tmp_obj = tmpl.get_obj(*it);
    return tmp_obj.get_vdata(varname);
}
