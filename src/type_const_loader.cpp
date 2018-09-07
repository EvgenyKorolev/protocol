#include "type_const_loader.h"

type_const_loader::type_const_loader()
{
    settings& tmps = settings::GetInstance();
    QDomDocument open_const_lst;
    QFile con_f(tmps.get_data_patch() + tmps.get_data_dir() + "/type.dat");
    if (!con_f.exists()){
        con_f.open(QIODevice::WriteOnly);
        con_f.close();
    }
    if (con_f.open(QIODevice::ReadOnly)){
        open_const_lst.setContent(&con_f);
        con_f.close();
    } else {
        QMessageBox::information(nullptr, "Отладка", "Не открывается файл с константами для чтения");
    }
    QDomElement root = open_const_lst.firstChildElement("typs");
    int i{0};
    while(!root.firstChildElement("type" + QString::number(i)).isNull()){
        type_obj tmpo;
        tmpo.load_xml(root.firstChildElement("type" + QString::number(i)).firstChildElement("const_type"));
        this->add_obj(tmpo);
        ++i;
    }
    con_f.close();
}
void type_const_loader::save()
{
    settings& tmps = settings::GetInstance();
    QFile con_f(tmps.get_data_patch() + tmps.get_data_dir() + "/type.dat");
    con_f.copy(tmps.get_data_patch() + tmps.get_data_dir() + "/type.bak");
    if (con_f.open(QIODevice::WriteOnly)){
        QDomDocument save_list;
        QDomElement root = save_list.createElement("typs");
            save_list.appendChild(root);
            int i{0};
        for (auto it : data_list){
            QDomElement xml_number = save_list.createElement("type" + QString::number(i));
            root.appendChild(xml_number);
            xml_number.appendChild(it->make_xml());
            ++i;
        }
        QTextStream stream(&con_f);
        save_list.save(stream, 1);
        con_f.close();
    } else {
        QMessageBox::information(nullptr, "Отладка", "Не открывается файл с константами для записи");
    }
    con_f.close();
}
QList<QString> type_const_loader::get_id_list() const
{
    QList<QString> ret;
    for (auto it : data_list){
        ret.append(it->get_name());
    }
    return ret;
}
QList<QString> type_const_loader::get_var_list() const
{
    QList<QString> ret;
    for (auto it : data_list){
        ret.append(it->get_vname());
    }
    return ret;
}
type_obj type_const_loader::get_obj(const QString &key) const
{
    if (key == "") {return type_obj();}
    auto ret_it = std::find_if(data_list.begin(), data_list.end(), [key](type_obj* pred)->bool{return (key == pred->get_name());});
    if (ret_it != data_list.end() ){
        return *(ret_it[0]);
    }
    return type_obj();
}
bool type_const_loader::add_obj(type_obj& arg)
{
    if (arg.get_name() == "") {return false;}
    QList<QString> tmp_list = this->get_var_list();
    auto it = std::find(tmp_list.begin(), tmp_list.end(), arg.get_vname());
    if ( it == tmp_list.end()){
        type_obj *tmpo = new type_obj(arg);
        data_list.append(tmpo);
        return true;
    } else {
        QString key = (*it);
        auto ret_it = std::find_if(data_list.begin(), data_list.end(), [key](type_obj* pred)->bool{return (key == pred->get_vname());});
        *(*ret_it) = arg;
    }
    return false;
}
bool type_const_loader::change_obj(type_obj& arg, QString key)
{
    if (arg.get_vname() == "" || key == "") {return false;}
    QList<QString> tmp_list = this->get_var_list();
    auto it = std::find(tmp_list.begin(), tmp_list.end(), key);
    if ( it == tmp_list.end()){
        type_obj *tmpo = new type_obj(arg);
        data_list.append(tmpo);
        return true;
    } else {
        auto ret_it = std::find_if(data_list.begin(), data_list.end(), [key](type_obj* pred)->bool{return (key == pred->get_vname());});
        *(*ret_it) = arg;
        return true;
    }
}
bool type_const_loader::del_type(const QString& key)
{
    if (key == "") {return false;}
    auto ret_it = std::find_if(data_list.begin(), data_list.end(), [key](type_obj* pred)->bool{return (key == pred->get_name());});
    if (ret_it != data_list.end() ){
        data_list.erase(ret_it);
        this->save();
        return true;
    }
    return false;
}
