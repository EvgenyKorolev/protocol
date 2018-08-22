#include "prot_act_adapter.h"

QString prot_act_adapter::get_var(const QString& arg, const QString& style)
{
    if (arg == "_cur_data") return current_data.toString(style);
    if (arg == "_cur_data") return current_data.toString("dd.MM.yyyy");
    if (arg == "_cur_data") return current_data.toString("dd.MM.yy");
    if (arg == "_cur_data") return current_data.toString("dd.MMM.yyyy");
    if (arg == "_cur_data") return current_data.toString("dd.MMMM.yyyy");
    if (arg == "_cur_engineer"){ return worker::get_fio(engineer, fio::nf_surname);}
    if (arg == "_cur_engineer1"){ return worker::get_fio(engineer, fio::surname_nf);}
    if (arg == "_cur_engineer2"){ return worker::get_fio(engineer, fio::name_surname);}
    if (arg == "_cur_engineer3"){ return worker::get_fio(engineer, fio::surname_name);}
    if (arg == "_cur_engineer4"){ return worker::get_fio(engineer, fio::full);}
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
QString prot_act_adapter::get_engineer() const
{
    return engineer.get_name().left(1) + ". " + engineer.get_fname().left(1) + ". " + engineer.get_surname();
}
worker prot_act_adapter::get_engineer_all() const
{
    return engineer;
}
void prot_act_adapter::set_worker(const worker& arg)
{
    engineer = arg;
}
