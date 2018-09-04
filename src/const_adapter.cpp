#include "const_adapter.h"

const_adapter::const_adapter(const QString &type)
{
    const_loader& cnl = const_loader::getInstance();
    QList<QString> tmp = cnl.get_var_list();
    if (std::find(tmp.begin(), tmp.end(), type) == tmp.end()){
        valid = false;
    } else {
        valid = true;
    };
    data = cnl.get_obj(type);
}
const_adapter::const_adapter(const_adapter& arg)
{
    data = arg.data;
    valid =arg.valid;
}
const_adapter::const_adapter(const_adapter&& arg)
{
    data = std::move(arg.data);
    valid =std::move(arg.valid);
}
const_adapter& const_adapter::operator=(const const_adapter& arg)
{
    data = arg.data;
    valid =arg.valid;
    return *this;
}
const_adapter& const_adapter::operator=(const_adapter&& arg)
{
    data = std::move(arg.data);
    valid = std::move(arg.valid);
    return *this;
}
bool const_adapter::is_valid()
{
    return  valid;
}
QString const_adapter::get_var(const QString &varname)
{
    if (!valid) return "";
    return data.get_vdata(varname);
}
bool const_adapter::change_type(const QString& type)
{
    const_loader& cnl = const_loader::getInstance();
    QList<QString> tmp = cnl.get_var_list();
    if (std::find(tmp.begin(), tmp.end(), type) == tmp.end()){
        return false;
    }
    data = cnl.get_obj(type);
    return true;
}
