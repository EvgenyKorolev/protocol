#include "const_loader.h"

const_loader::const_loader()
{
    settings& tmps = settings::GetInstance();
    QDomDocument open_const_lst;
    QFile con_f(tmps.get_data_patch() + tmps.get_data_dir() + "/const.dat");
    if (!con_f.exists()){
        con_f.open(QIODevice::WriteOnly);
        con_f.close();
    }
    if (con_f.open(QIODevice::ReadOnly)){
        open_const_lst.setContent(&con_f);
        con_f.close();
    } else {
        QMessageBox::information(nullptr, "Отладка", "Не открывается файл с текстами протоколов для чтения");
    }
    QDomElement root = open_const_lst.firstChildElement("typs");
    int i{0};
    while(!root.firstChildElement("type" + QString::number(i)).isNull()){
        const_obj tmpo;
        tmpo.load_xml(root.firstChildElement("type" + QString::number(i)).firstChildElement("prot_type"));
        this->add_obj(tmpo);
        ++i;
    }
    con_f.close();
}
void const_loader::save()
{
    settings& tmps = settings::GetInstance();
    QFile con_f(tmps.get_data_patch() + tmps.get_data_dir() + "/const.dat");
    con_f.copy(tmps.get_data_patch() + tmps.get_data_dir() + "/const.bak");
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
        QMessageBox::information(nullptr, "Отладка", "Не открывается файл с текстами протоколов для записи");
    }
    con_f.close();
}
QList<QString> const_loader::get_id_list() const
{
    QList<QString> ret;
    for (auto it : data_list){
        ret.append(it->get_name());
    }
    return ret;
}
QList<QString> const_loader::get_var_list() const
{
    QList<QString> ret;
    for (auto it : data_list){
        ret.append(it->get_vname());
    }
    return ret;
}
QList<QPair<QString, QString>> const_loader::get_idv_list() const
{
    QList<QPair<QString, QString>> ret;
    for (auto it : data_list){
        QPair<QString, QString> tmp;
        tmp.first = it->get_name();
        tmp.second = it->get_vname();
        ret.append(tmp);
    }
    return ret;
}
const_obj const_loader::get_obj(const QString& key) const
{
    if (key == "") {return const_obj();}
    auto ret_it = std::find_if(data_list.begin(), data_list.end(), [key](const_obj* pred)->bool{return (key == pred->get_vname());});
    if (ret_it != data_list.end() ){
        return *(ret_it[0]);
    }
    return const_obj();
}
bool const_loader::add_obj(const_obj& arg)
{
    if (arg.get_vname() == "") {return false;}
    QList<QString> tmp_list = this->get_var_list();
    auto it = std::find(tmp_list.begin(), tmp_list.end(), arg.get_vname());
    if ( it == tmp_list.end()){
        const_obj *tmpo = new const_obj(arg);
        data_list.append(tmpo);
        return true;
    } else {
        QString key = (*it);
        auto ret_it = std::find_if(data_list.begin(), data_list.end(), [key](const_obj* pred)->bool{return (key == pred->get_vname());});
        *(*ret_it) = arg;
        return true;
    }
}
bool const_loader::del_obj(const QString& key)
{
    if (key == "") {return false;}
    auto ret_it = std::find_if(data_list.begin(), data_list.end(), [key](const_obj* pred)->bool{return (key == pred->get_vname());});
    if (ret_it != data_list.end() ){
        data_list.erase(ret_it);
        this->save();
        return true;
    }
    return false;
}
bool const_loader::change_obj(const_obj& arg, QString key)
{
    if (arg.get_vname() == "" || key == "") {return false;}
    QList<QString> tmp_list = this->get_var_list();
    auto it = std::find(tmp_list.begin(), tmp_list.end(), key);
    if ( it == tmp_list.end()){
        const_obj *tmpo = new const_obj(arg);
        data_list.append(tmpo);
        return true;
    } else {
        auto ret_it = std::find_if(data_list.begin(), data_list.end(), [key](const_obj* pred)->bool{return (key == pred->get_vname());});
        *(*ret_it) = arg;
        return true;
    }
}
