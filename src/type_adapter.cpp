#include "type_adapter.h"

type_adapter::type_adapter(){}
QString type_adapter::get_var(const QString &type, const QString &varname)
{
    type_const_loader& tmpl = type_const_loader::getInstance();
    QList<QString> tmpvs = tmpl.get_var_list();
    QList<QString>::iterator it = std::find(tmpvs.begin(), tmpvs.end(), type);
    if (it == tmpvs.end()) return  "";
    type_obj tmp_obj = tmpl.get_obj(*it);
    return tmp_obj.get_vdata(varname);
}
