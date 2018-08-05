#include "const_obj.h"

const_obj::const_obj()
{
    name = "";
    var_name = "";
    data = QList<QPair<QPair<QString, QString>, QString>>();
}
const_obj::const_obj(const_obj& arg)
{
    var_name = arg.get_vname();
    name = arg.get_name();
    data = arg.get_data();
}
const_obj::const_obj(const const_obj& arg)
{
    var_name = arg.get_vname();
    name = arg.get_name();
    data = arg.get_data();
}
const_obj::const_obj(const_obj&& arg)
{
    var_name = std::move(arg.var_name);
    name = std::move(arg.name);
    data = std::move(arg.data);
}
const_obj& const_obj::operator=(const_obj& arg)
{
    var_name = arg.get_vname();
    name = arg.get_name();
    data = arg.get_data();
    return *this;
}
const_obj& const_obj::operator=(const_obj&& arg)
{
    var_name = std::move(arg.var_name);
    name = std::move(arg.name);
    data = std::move(arg.data);
    return *this;
}
listing_type const_obj::get_data() const
{
    return data;
}
int const_obj::count() const
{
    return data.count();
}
QString const_obj::get_name() const
{
    return name;
}
void const_obj::set_name(const QString& arg)
{
    name = arg;
}
QString const_obj::get_vname() const
{
    return var_name;
}
void const_obj::set_vname(const QString& arg)
{
    var_name = arg;
}
void const_obj::append(QPair<QPair<QString, QString>, QString> arg)
{
    if (std::find_if(data.begin(), data.end(), [&arg](QPair<QPair<QString, QString>, QString>& pred)->bool{
                     return arg.second == pred.second;}) != data.end()){
         QMessageBox::information(nullptr, "Отладка", "Нельзя создавать две переменных с одним именем");
         return;
    }
    data.append(arg);
}
void const_obj::replace(int row, QPair<QPair<QString, QString>, QString> arg)
{
    if (std::find_if(data.begin(), data.end(), [&arg](QPair<QPair<QString, QString>, QString>& pred)->bool{
                     return arg.second == pred.second;}) != data.end()){
        if (data.at(row).second != arg.second) {
            QMessageBox::information(nullptr, "Отладка", "Нельзя создавать две переменных с одним именем");
            return;
        }
    }
    data.replace(row, arg);
}
QPair<QPair<QString, QString>, QString> const_obj::at(int arg) const
{
    return data.at(arg);
}
void const_obj::removeAt(int arg)
{
    data.removeAt(arg);
}
QString const_obj::get_vdata(const QString& vname)
{
//    QList<QPair<QPair<QString, QString>, QString>>
//    1. ОПИСАНИЕ 2. ТЕКСТ 3. ИМЯ ПЕРЕМЕННОЙ */
    auto tmp_it = std::find_if(data.begin(), data.end(), [&vname](QPair<QPair<QString, QString>, QString>& pred)->bool{return pred.second == vname;});
    if ( tmp_it == data.end()){
        return  "";
    };
    return tmp_it->first.second;
}
QDomElement const_obj::make_xml()
{
    QDomDocument xml_ret;
    QDomElement root = xml_ret.createElement("prot_type");
    xml_ret.appendChild(root);

    QDomElement xml_name = xml_ret.createElement("name");
        QDomText xml_name_text = xml_ret.createTextNode(name);
            root.appendChild(xml_name);
            xml_name.appendChild(xml_name_text);

    QDomElement xml_vname = xml_ret.createElement("var_name");
        QDomText xml_vname_text = xml_ret.createTextNode(var_name);
            root.appendChild(xml_vname);
            xml_vname.appendChild(xml_vname_text);

    QDomElement xml_ver = xml_ret.createElement("consts");
        root.appendChild(xml_ver);
    int i = 0;
    for (QPair<QPair<QString, QString>, QString> key : data){
        QDomElement xml_number = xml_ret.createElement("con" + QString::number(i));
        QDomElement xml_liter = xml_ret.createElement("liter");
        QDomElement xml_txt = xml_ret.createElement("txt");
        QDomElement xml_var = xml_ret.createElement("var");
// 1. НАЗВАНИЕ 2. СОДЕРЖАНИЕ 3. ИМЯ ПЕРЕМЕННОЙ
        QDomText xml_liter_text = xml_ret.createTextNode(key.first.first);
        QDomText xml_txt_text = xml_ret.createTextNode(key.first.second);
        QDomText xml_var_text = xml_ret.createTextNode(key.second);
        xml_liter.appendChild(xml_liter_text);
        xml_txt.appendChild(xml_txt_text);
        xml_var.appendChild(xml_var_text);
        xml_number.appendChild(xml_liter);
        xml_number.appendChild(xml_txt);
        xml_number.appendChild(xml_var);
        xml_ver.appendChild(xml_number);
        ++i;
    }
    return root;
}
void const_obj::load_xml(QDomElement arg)
{
    name = arg.firstChildElement("name").text();
    var_name = arg.firstChildElement("var_name").text();
    QDomElement lst_temp = arg.firstChildElement("consts");
    int i{0};
    QPair<QPair<QString, QString>, QString> pr;
    while(!lst_temp.firstChildElement("con" + QString::number(i)).isNull()){
        pr.first.first = lst_temp.firstChildElement("con" + QString::number(i)).firstChildElement("liter").text();
        pr.first.second = lst_temp.firstChildElement("con" + QString::number(i)).firstChildElement("txt").text();
        pr.second = lst_temp.firstChildElement("con" + QString::number(i)).firstChildElement("var").text();
        data.append(pr);
        ++i;
    }
}
