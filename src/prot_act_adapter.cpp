#include "prot_act_adapter.h"

QString prot_act_adapter::get_var(const QString& arg, const QString& style)
{
    if (arg == "_cur_data") return current_data.toString(style);
    if (arg == "_cur_data") return current_data.toString("dd.MM.yyyy");
    if (arg == "_cur_data") return current_data.toString("dd.MM.yy");
    if (arg == "_cur_data") return current_data.toString("dd.MMM.yyyy");
    if (arg == "_cur_data") return current_data.toString("dd.MMMM.yyyy");
    return "";
}
void prot_act_adapter::set_current_data(const QDate& arg)
{
    current_data = arg;
}
void prot_act_adapter::set_current_data(QDate&& arg)
{
    current_data = std::move(arg);
}
QDate prot_act_adapter::get_current_data() const
{
    return  current_data;
}
