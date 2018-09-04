#include "type_obj.h"

type_obj::type_obj(){}
type_obj::type_obj(const type_obj& arg)
{
    var_name = arg.var_name;
    name = arg.name;
    data = arg.data;
    description = arg.description;
    cls = arg.cls;
}
type_obj::type_obj(type_obj&& arg)
{
    var_name = std::move(arg.var_name);
    name = std::move(arg.name);
    data = std::move(arg.data);
    description = std::move(arg.description);
    cls = std::move(arg.cls);
}
type_obj& type_obj::operator=(const type_obj& arg)
{
    var_name = arg.var_name;
    name = arg.name;
    data = arg.data;
    description = arg.description;
    cls = arg.cls;
    return *this;
}
type_obj& type_obj::operator=(type_obj&& arg)
{
    var_name = std::move(arg.var_name);
    name = std::move(arg.name);
    data = std::move(arg.data);
    description = std::move(arg.description);
    cls = std::move(arg.cls);
    return *this;
}
QString type_obj::get_name() const
{
    return name;
}
void type_obj::set_name(const QString& arg)
{
    name = arg;
}
QString type_obj::get_vname() const
{
    return var_name;
}
void type_obj::set_vname(const QString& arg)
{
    var_name = arg;
}
QString type_obj::get_description() const
{
    return description;
}
void type_obj::set_description(const QString& arg)
{
    description = arg;
}
QString type_obj::get_cls() const
{
    return cls;
}
void type_obj::set_cls(const QString& arg)
{
    cls = arg;
}
void type_obj::append(std::tuple<QString, QString, QString, QString> arg)
{
    if (std::find_if(data.begin(), data.end(), [&arg](std::tuple<QString, QString, QString, QString>& pred)->bool{
                     return (std::get<0>(arg) == std::get<0>(pred));}) != data.end()){

    QMessageBox::information(nullptr, "Отладка", "Нельзя создавать две переменных с одним именем");
    return;
    }
    data.append(arg);
}
std::tuple<QString, QString, QString, QString> type_obj::at(int arg) const
{
    return data.at(arg);
}
QString type_obj::get_vdata(const QString &key) const
{
    // имя переменной, описание, значение, тип переменной
    auto it = std::find_if(data.begin(), data.end(), [key](const std::tuple<QString, QString, QString, QString>& pred)->bool{
            return std::get<0>(pred) == key; });
    if (it == data.end()) return "NULL";
    return  std::get<3>(*it);
}
void type_obj::removeAt(int arg)
{
    data.removeAt(arg);
}
void type_obj::replace(int row, std::tuple<QString, QString, QString, QString> arg)
{
    if (std::find_if(data.begin(), data.end(), [arg](const std::tuple<QString, QString, QString, QString>& pred)->bool{
                     return (std::get<0>(arg) == std::get<0>(pred));}) != data.end()){
        if (std::get<0>(data.at(row)) != std::get<0>(arg)) {
            QMessageBox::information(nullptr, "Отладка", "Нельзя создавать две переменных с одним именем");
            return;
        }
    }
    data.replace(row, arg);
}
lst_type type_obj::get_data() const
{
    return data;
}
int type_obj::count() const
{
    return data.count();
}
QDomElement type_obj::make_xml()
{
    QDomDocument xml_ret;
    QDomElement root = xml_ret.createElement("const_type");
    xml_ret.appendChild(root);

    QDomElement xml_name = xml_ret.createElement("name");
        QDomText xml_name_text = xml_ret.createTextNode(name);
            root.appendChild(xml_name);
            xml_name.appendChild(xml_name_text);
   QDomElement xml_vname = xml_ret.createElement("var_name");
       QDomText xml_vname_text = xml_ret.createTextNode(name);
           root.appendChild(xml_vname);
           xml_vname.appendChild(xml_vname_text);

   QDomElement xml_description = xml_ret.createElement("description");
       QDomText xml_description_text = xml_ret.createTextNode(description);
           root.appendChild(xml_description);
           xml_description.appendChild(xml_description_text);
   QDomElement xml_cls = xml_ret.createElement("cls");
       QDomText xml_cls_text = xml_ret.createTextNode(cls);
           root.appendChild(xml_cls);
           xml_cls.appendChild(xml_cls_text);

    QDomElement xml_ver = xml_ret.createElement("consts");
        root.appendChild(xml_ver);
    int i = 0;
    for (std::tuple<QString, QString, QString, QString> key : data){
        QDomElement xml_number = xml_ret.createElement("con" + QString::number(i));
        QDomElement xml_liter = xml_ret.createElement("liter");
        QDomElement xml_txt = xml_ret.createElement("txt");
        QDomElement xml_value = xml_ret.createElement("val");
        QDomElement xml_var_type = xml_ret.createElement("var");
// имя переменной, описание, значение, тип переменной
        QDomText xml_liter_text = xml_ret.createTextNode(std::get<0>(key));
        QDomText xml_txt_text = xml_ret.createTextNode(std::get<1>(key));
        QDomText xml_value_text = xml_ret.createTextNode(std::get<2>(key));
        QDomText xml_var_type_text = xml_ret.createTextNode(std::get<3>(key));
        xml_liter.appendChild(xml_liter_text);
        xml_txt.appendChild(xml_txt_text);
        xml_value.appendChild(xml_value_text);
        xml_var_type.appendChild(xml_var_type_text);
        xml_number.appendChild(xml_liter);
        xml_number.appendChild(xml_txt);
        xml_number.appendChild(xml_value);
        xml_number.appendChild(xml_var_type);
        xml_ver.appendChild(xml_number);
        ++i;
    }
    return root;
}
void type_obj::load_xml(QDomElement arg)
{
    name = arg.firstChildElement("name").text();
    var_name = arg.firstChildElement("var_name").text();
    description = arg.firstChildElement("description").text();
    cls = arg.firstChildElement("cls").text();
    QDomElement lst_temp = arg.firstChildElement("consts");
    int i{0};
    std::tuple<QString, QString, QString, QString> key;
    while(!lst_temp.firstChildElement("con" + QString::number(i)).isNull()){
        std::get<0>(key) = lst_temp.firstChildElement("con" + QString::number(i)).firstChildElement("liter").text();
        std::get<1>(key) = lst_temp.firstChildElement("con" + QString::number(i)).firstChildElement("txt").text();
        std::get<2>(key) = lst_temp.firstChildElement("con" + QString::number(i)).firstChildElement("val").text();
        std::get<3>(key) = lst_temp.firstChildElement("con" + QString::number(i)).firstChildElement("var").text();
        data.append(key);
        ++i;
    }
}
