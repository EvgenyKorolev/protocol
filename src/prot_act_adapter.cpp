#include "prot_act_adapter.h"

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
