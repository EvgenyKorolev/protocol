#include "laboratory.h"

laboratory::laboratory()
{
    QDomDocument openlab;
    QFile labf("./data/lab.dat");
    if (!labf.exists()){
        labf.open(QIODevice::WriteOnly);
        labf.close();
    }
    if (labf.open(QIODevice::ReadOnly)){
        openlab.setContent(&labf);
        labf.close();
    } else {
        QMessageBox::information(nullptr, "Отладка", "Не открывается файл с информацией о лаборатории");
    }
    this->laod_xml(&openlab);
}
int laboratory::set_name(QString *arg)
{
    if (arg->size() < 1000)
    {
        this->name = *arg;
        return 0;
    }
    return 1;
}
int laboratory::set_name(QString arg)
{
    if (arg.size() < 1000)
    {
        this->name = arg;
        return 0;
    }
    return 1;
}
QString laboratory::get_name()
{
    return this->name;
}
int laboratory::set_attestat(QString *arg)
{
    if (arg->size() < 1000)
    {
        this->attestat = *arg;
        return 0;
    }
    return 1;
}
int laboratory::set_attestat(QString arg)
{
    if (arg.size() < 1000)
    {
        this->attestat = arg;
        return 0;
    }
    return 1;
}
QString laboratory::get_attestat()
{
    return this->attestat;
}
int laboratory::set_adr(address *arg)
{
    this->adr = *arg;
    return 0;
}
address laboratory::get_adr()
{
    return this->adr;
}
void laboratory::set_det(details *arg)
{
    this->det = *arg;
}
details laboratory::get_det()
{
    return this->det;
}
int laboratory::add_workers(worker* arg)
{
    if (arg->test_meneger()){
        if (this->test_manager()){return -1;}
    }
    this->workers.append(*arg);
    return 0;
}
int laboratory::add_workers(worker arg)
{
    if (arg.test_meneger()){
        if (this->test_manager()){
            QMessageBox::information(nullptr, "Внимание!", "У вас более одного руководителя лаборатори.<br> В протокол попадёт только один из них.");
        }
    }
    this->workers.append(arg);
    return 0;
}
int laboratory::set_workers_list(QList<worker> *arg)
{
    if(std::count_if(arg->begin(), arg->end(), [](const worker& pred)->bool{return pred.test_meneger();}) > 1){
        QMessageBox::information(nullptr, "Внимание!", "У вас более одного руководителя лаборатори.<br> В протокол попадёт только один из них.");
    }
    this->clear_workers();
    this->workers.append(*arg);
    return 0;
}
int laboratory::set_workers_list(QList<worker> arg)
{
    if(std::count_if(arg.begin(), arg.end(), [](const worker& pred)->bool{return pred.test_meneger();}) > 1){
        QMessageBox::information(nullptr, "Внимание!", "У вас более одного руководителя лаборатори.<br> В протокол попадёт только один из них.");
    }
    this->clear_workers();
    this->workers.append(arg);
    return 0;
}
QList<worker> laboratory::get_workers_list()
{
    return this->workers;
}
int laboratory::clear_workers()
{
    this->workers.clear();
    return 0;
}
int laboratory::set_uadr(address *arg)
{
    this->det.set_ur_post(arg);
    return 0;
}
address laboratory::get_uadr()
{
 return this->det.get_ur_post();
}
int laboratory::set_padr(address *arg)
{
    this->det.set_re_post(arg);
    return 0;
}
address laboratory::get_padr()
{
    return this->det.get_re_post();
}
int laboratory::set_inn(unsigned long long int arg)
{
    return this->det.set_inn(arg);
}
int laboratory::set_dir(QPair<QString, QString> arg)
{
    this->det.set_dir(arg);
    return 0;
}
void laboratory::set_tel_list(QList<QString> arg)
{
    this->det.set_tel_list(arg);
}
void laboratory::set_fax_list(QList<QString> arg)
{
    this->det.set_fax_list(arg);
}
void laboratory::set_email(const QString &arg)
{
    det.set_email(arg);
}
QString laboratory::get_email() const
{
    return det.get_email();
}
void laboratory::set_full_name(const QString& arg)
{
    det.set_name(arg);
}
QString laboratory::get_full_name() const
{
    return det.get_name();
}
worker laboratory::get_manager()
{
    if (workers.empty()){
        auto ret = std::find_if(workers.begin(), workers.end(), [](const worker& pred)->bool{return pred.test_meneger();});
        if (ret == workers.end()){
            return worker();
        } else return *ret;
    }
    return worker();
}
bool laboratory::test_manager()
{
    if (workers.empty()){
        auto ret = std::find_if(workers.begin(), workers.end(), [](const worker& pred)->bool{return pred.test_meneger();});
        if (ret == workers.end()){
            return false;
        } else return true;
    }
    return false;
}
worker laboratory::get_labdir()
{
    auto ret = std::find_if(workers.begin(), workers.end(), [](const worker& pred)->bool{return pred.test_meneger();});
    if (ret != workers.end()){
        return *ret;
    }
    return worker();
}
QDomDocument laboratory::make_xml()
{
    QDomDocument ret_xml;
    QDomElement root = ret_xml.createElement("laboratory");

    QDomElement xml_name = ret_xml.createElement("name");
        QDomText xml_name_text = ret_xml.createTextNode(this->name);
        root.appendChild(xml_name);
        xml_name.appendChild(xml_name_text);

    QDomElement xml_att = ret_xml.createElement("attestat");
        QDomText xml_att_text = ret_xml.createTextNode(this->attestat);
        root.appendChild(xml_att);
        xml_att.appendChild(xml_att_text);

    root.appendChild(this->det.make_xml());

    QDomElement xml_adr = ret_xml.createElement("adr");
        root.appendChild(xml_adr);
        xml_adr.appendChild(this->adr.make_xml());

    root.appendChild(my_fnc::date_to_xml(att_date));

    QDomElement xml_wor = ret_xml.createElement("workers");
       root.appendChild(xml_wor);
       QList<worker>::iterator it = this->workers.begin();
       int i = 0;
       while (it != this->workers.end()) {
              QDomElement wr =  ret_xml.createElement("wrk" + QString::number(i));
              xml_wor.appendChild(wr);
              wr.appendChild(it->make_xml());
              ++i;
              ++it;
        }
    ret_xml.appendChild(root);
    return ret_xml;
}
void laboratory::laod_xml(QDomDocument *arg)
{
    QDomElement root = arg->firstChildElement("laboratory");
        this->name = root.firstChildElement("name").text();
        this->attestat = root.firstChildElement("attestat").text();

     auto tmpd0 = root.firstChildElement("details");
         this->det.load_xml(&tmpd0);
     auto tmpd1 = root.firstChildElement("adr").firstChildElement("address");
         this->adr.load_xml(&tmpd1);
     my_fnc::xml_to_date(root.firstChildElement("date"), att_date);

     QDomElement tmpd = root.firstChildElement("workers");
     worker tmpw;
     int i = 0;
     while (!tmpd.firstChildElement("wrk" + QString::number(i)).isNull()) {
         QDomNode tmpd2 = tmpd.firstChildElement("wrk" + QString::number(i)).firstChildElement("worker");
         tmpw.load_xml(&tmpd2);
         this->workers.append(tmpw);
         ++i;
     }
}
void laboratory::set_att_date(QDate *arg)
{
    att_date = *arg;
}
void laboratory::set_att_date(QDate arg)
{
    att_date = arg;
}
QDate laboratory::get_att_date()
{
    return att_date;
}
int laboratory::load_db(){return 0;}
int laboratory::save_db(){return 0;}
