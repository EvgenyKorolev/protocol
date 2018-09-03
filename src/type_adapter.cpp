#include "type_adapter.h"
type_adapter::type_adapter(){}
type_adapter::type_adapter(const QList<type_obj>& arg)
{
    data_list = arg;
    test_d();
}
void type_adapter::set_lst(const QList<type_obj>& arg)
{
    data_list = arg;
    test_d();
}
void type_adapter::add_type(const QString& arg)
{
    type_const_loader& tmpl = type_const_loader::getInstance();
    type_obj tmpt = tmpl.get_obj(arg);
    if (tmpt.get_vname() == "") return;
    if (data_list.end() != std::find_if(data_list.begin(), data_list.end(), [tmpt](const type_obj& pred)->bool{
                                        return pred.get_cls() == tmpt.get_cls();})){
        duplication = true;
    }
    data_list.append(tmpt);
}
bool type_adapter::test_duplicate() const
{
    return duplication;
}
void type_adapter::test_d()
{
// Да-да, сложность квадратичная, но спсок ожидается в 2-10 элиментов, до 20 скорее всего никогда не дорастёт
    for (int i = 0; i < data_list.size(); ++i){
        for (int j = i + 1; j < data_list.size(); ++j){
            if (data_list.at(i).get_cls() == data_list.at(j).get_cls()){
                duplication = true;
                return;
            }
        }
    }
    duplication = false;
    return;
}
QString type_adapter::get_var(const QString &cls, const QString &varname) const
{
    auto ret = std::find_if(data_list.begin(), data_list.end(), [cls](const type_obj& pred)->bool{return pred.get_cls() == cls;});
    if (ret == data_list.end()) return "NULL";
    return ret->get_vdata(varname);
}
void type_adapter::del_type(const QString& arg)
{
    std::remove_if(data_list.begin(), data_list.end(), [arg](const type_obj& pred)->bool{return pred.get_vname() == arg;});
    test_d();
}
void type_adapter::clear()
{
    data_list = QList<type_obj>();
}
