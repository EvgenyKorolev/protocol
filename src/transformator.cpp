#include "transformator.h"

transformator::transformator()
{
    _type = QString();       // Тип трансфоматора
    _mnom = QString();       // Заводской №:
    _cls = QString();        // Класс точности
    _nom_power = QString();  // Номинальная полная мощность нагрузки Sн для указанного класса точности, ВА:
    _obm = QString();        // Схема соединения обмоток (усл. обозначение)
    _nom_u_2 = QString();    // Номинальное напряжение основной вторичной обмотки U2 ном, В
    _nom_u_1 = QString();    // Номинальное напряжение первичной обмотки U1 ном, кВ
    _f = 1;            // Сколько фаз (1 или 3)
}
transformator::transformator(transformator *arg)
{
    _type = arg->get_type();
    _mnom = arg->get_mnom();
    _cls = arg->get_cls();
    _nom_power = arg->get_nom_power();
    _obm = arg->get_obm();
    _nom_u_2 = arg->get_nom_u_2();
    _nom_u_1 = arg->get_nom_u_1();
    _f = arg->test_f();
}
transformator& transformator::operator=(const transformator &arg)
{
    _type = arg.get_type();
    _mnom = arg.get_mnom();
    _cls = arg.get_cls();
    _nom_power = arg.get_nom_power();
    _obm = arg.get_obm();
    _nom_u_2 = arg.get_nom_u_2();
    _nom_u_1 = arg.get_nom_u_1();
    _f = arg.test_f();
    return *this;
}
bool transformator::operator==(const transformator &arg)
{
    if (
    (_type == arg.get_type()) &&
    (_mnom == arg.get_mnom()) &&
    (_cls == arg.get_cls()) &&
    (_nom_power == arg.get_nom_power()) &&
    (_obm == arg.get_obm()) &&
    (_nom_u_2 == arg.get_nom_u_2()) &&
    (_nom_u_1 == arg.get_nom_u_1()) &&
    (_f == arg.test_f())
    ) {return true;}
    return false;
}
bool transformator::operator!=(const transformator &arg)
{
    return !(*this == arg);
}
transformator::~transformator()
{
}
transformator::transformator(const transformator &arg)
{
    _type = arg.get_type();
    _mnom = arg.get_mnom();
    _cls = arg.get_cls();
    _nom_power = arg.get_nom_power();
    _obm = arg.get_obm();
    _nom_u_2 = arg.get_nom_u_2();
    _nom_u_1 = arg.get_nom_u_1();
    _f = arg.test_f();
}
void transformator::set_type(QString arg)
{
    _type = arg;
}
QString transformator::get_type() const
{
    return _type;
}
void transformator::set_mnom(QString arg)
{
    _mnom = arg;
}
QString transformator::get_mnom() const
{
    return _mnom;
}
void transformator::set_cls(QString arg)
{
    _cls = arg;
}
QString transformator::get_cls() const
{
    return _cls;
}
void transformator::set_nom_power(QString arg)
{
    _nom_power = arg;
}
QString transformator::get_nom_power() const
{
    return _nom_power;
}
void transformator::set_obm(QString arg)
{
    _obm = arg;
}
QString transformator::get_obm() const
{
    return _obm;
}
void transformator::set_nom_u_2(QString arg)
{
    _nom_u_2 = arg;
}
QString transformator::get_nom_u_2() const
{
    return _nom_u_2;
}
void transformator::set_nom_u_1(QString arg)
{
    _nom_u_1 = arg;
}
QString transformator::get_nom_u_1() const
{
    return _nom_u_1;
}
void transformator::set_f1()
{
    _f = 1;
}
void transformator::set_f3()
{
    _f = 3;
}
void transformator::set_f(uint arg)
{
    _f = arg;
}
uint transformator::test_f() const
{
    return _f;
}
QDomElement transformator::make_xml()
{
    QDomDocument xml_ret;
    QDomElement root = xml_ret.createElement("trans");
        xml_ret.appendChild(root);
    QDomElement xml_type = xml_ret.createElement("type");
        QDomText xml_type_text = xml_ret.createTextNode(_type);
            root.appendChild(xml_type);
            xml_type.appendChild(xml_type_text);
    QDomElement xml_mnom = xml_ret.createElement("mnom");
        QDomText xml_mnom_text = xml_ret.createTextNode(_mnom);
            root.appendChild(xml_mnom);
            xml_mnom.appendChild(xml_mnom_text);
     QDomElement xml_cls = xml_ret.createElement("cls");
         QDomText xml_cls_text = xml_ret.createTextNode(_cls);
             root.appendChild(xml_cls);
             xml_cls.appendChild(xml_cls_text);
      QDomElement xml_nom_power = xml_ret.createElement("nom_power");
          QDomText xml_nom_power_text = xml_ret.createTextNode(_nom_power);
              root.appendChild(xml_nom_power);
              xml_nom_power.appendChild(xml_nom_power_text);
       QDomElement xml_obm = xml_ret.createElement("obm");
           QDomText xml_obm_text = xml_ret.createTextNode(_obm);
               root.appendChild(xml_obm);
               xml_obm.appendChild(xml_obm_text);
       QDomElement xml_nom_u_2 = xml_ret.createElement("nom_u_2");
           QDomText xml_nom_u_2_text = xml_ret.createTextNode(_nom_u_2);
               root.appendChild(xml_nom_u_2);
               xml_nom_u_2.appendChild(xml_nom_u_2_text);
        QDomElement xml_nom_u_1 = xml_ret.createElement("nom_u_1");
            QDomText xml_nom_u_1_text = xml_ret.createTextNode(_nom_u_1);
                root.appendChild(xml_nom_u_1);
                xml_nom_u_1.appendChild(xml_nom_u_1_text);
        QDomElement xml_f = xml_ret.createElement("f");
            QDomText xml_f_text = xml_ret.createTextNode(QString::number(_f));
                root.appendChild(xml_f);
                xml_f.appendChild(xml_f_text);
    return root;
}
int transformator::load_xml(QDomNode *arg)
{
    QDomNode lst = *arg;
       _type = lst.firstChildElement("type").text();
       _mnom = lst.firstChildElement("mnom").text();
       _cls = lst.firstChildElement("cls").text();
       _nom_power = lst.firstChildElement("nom_power").text();
       _obm = lst.firstChildElement("obm").text();
       _nom_u_2 = lst.firstChildElement("nom_u_2").text();
       _nom_u_1 = lst.firstChildElement("nom_u_1").text();
       _f = lst.firstChildElement("f").text().toUInt();
    return 0;
}
int transformator::load_db(){return 0;}
int transformator::save_db(){return 0;}
