#include "lab_adapter.h"

lab_adapter::lab_adapter(){}
QString lab_adapter::get_var(const QString &arg) const
{
    laboratory &tmpl = laboratory::getInstance();
    if (arg == "_lab_name"){return  tmpl.get_name();}
    if (arg == "_lab_att"){return tmpl.get_attestat();}
 // Дата
    if (arg == "_lab_att_date"){return tmpl.get_att_date().toString();}
    if (arg == "_lab_att_date1"){return tmpl.get_att_date().toString("dd.MM.yyyy");}
    if (arg == "_lab_att_date2"){return tmpl.get_att_date().toString("dd.MM.yy");}
    if (arg == "_lab_att_date3"){return tmpl.get_att_date().toString("dd.MMM.yyyy");}
    if (arg == "_lab_att_date4"){return tmpl.get_att_date().toString("dd.MMMM.yyyy");}
    if (arg == "_lab_inn"){
        if (tmpl.get_det().get_inn() == 0) return  "";
        return QString::number(tmpl.get_det().get_inn());
    }
    if (arg == "_lab_dir_dol"){return  tmpl.get_det().get_dir().first;}
    if (arg == "_lab_dir_name"){return  tmpl.get_det().get_dir().second;}
 // Телефоны
    if (arg == "_lab_tel"){
        QList<QString> tmp = tmpl.get_det().get_tel_list();
        if (tmp.size() > 0){return tmp.at(0);}
        return "";
    }
    if (arg == "_lab_tel1"){
        QList<QString> tmp = tmpl.get_det().get_tel_list();
        if (tmp.size() > 1){return tmp.at(1);}
        return "";
    }
    if (arg == "_lab_tel2"){
        QList<QString> tmp = tmpl.get_det().get_tel_list();
        if (tmp.size() > 2){return tmp.at(2);}
        return "";
    }
    if (arg == "_lab_tel3"){
        QList<QString> tmp = tmpl.get_det().get_tel_list();
        if (tmp.size() > 3){return tmp.at(3);}
        return "";
    }
    if (arg == "_lab_tel4"){
        QList<QString> tmp = tmpl.get_det().get_tel_list();
        if (tmp.size() > 4){return tmp.at(4);}
        return "";
    }
 // Факсы
    if (arg == "_lab_fax"){
        QList<QString> tmp = tmpl.get_det().get_fax_list();
        if (tmp.size() > 0){return tmp.at(0);}
        return "";
    }
    if (arg == "_lab_fax1"){
        QList<QString> tmp = tmpl.get_det().get_fax_list();
        if (tmp.size() > 1){return tmp.at(1);}
        return "";
    }
    if (arg == "_lab_fax2"){
        QList<QString> tmp = tmpl.get_det().get_fax_list();
        if (tmp.size() > 2){return tmp.at(2);}
        return "";
    }
    if (arg == "_lab_fax3"){
        QList<QString> tmp = tmpl.get_det().get_fax_list();
        if (tmp.size() > 3){return tmp.at(3);}
        return "";
    }
    if (arg == "_lab_fax4"){
        QList<QString> tmp = tmpl.get_det().get_fax_list();
        if (tmp.size() > 4){return tmp.at(4);}
        return "";
    }
 // Адрес почтовый
    if (arg == "_lab_padr_cont") {return tmpl.get_padr().get_country();}
    if (arg == "_lab_padr_statclass"){return tmpl.get_padr().get_state_class();}
    if (arg == "_lab_padr_state"){return tmpl.get_padr().get_state();}
    if (arg == "_lab_padr_stdistr"){return tmpl.get_padr().get_state_distr();}
    if (arg == "_lab_padr_citycl"){return tmpl.get_padr().get_city_class();}
    if (arg == "_lab_padr_city"){return tmpl.get_padr().get_city();}
    if (arg == "_lab_padr_distr"){return tmpl.get_padr().get_district();}
    if (arg == "_lab_padr_strcl"){return tmpl.get_padr().get_street_class();}
    if (arg == "_lab_padr_str"){return tmpl.get_padr().get_street();}
    if (arg == "_lab_padr_bnum"){
        if (tmpl.get_padr().get_building_num() == 0) return  "";
        return QString::number(tmpl.get_padr().get_building_num());
    }
    if (arg == "_lab_padr_blit"){return tmpl.get_padr().get_building_lit();}
    if (arg == "_lab_padr_ofnum"){
        if (tmpl.get_padr().get_office_num() == 0) return  "";
        return QString::number(tmpl.get_padr().get_office_num());
    }
    if (arg == "_lab_padr_oflit"){return  tmpl.get_padr().get_office_lit();}
    if (arg == "_lab_padr_postind"){
        if (tmpl.get_padr().get_post_index() == 0) return  "";
        return QString::number(tmpl.get_padr().get_post_index());
    }
 // Адрес юридический
    if (arg == "_lab_uadr_cont") {return tmpl.get_uadr().get_country();}
    if (arg == "_lab_uadr_statclass"){return tmpl.get_uadr().get_state_class();}
    if (arg == "_lab_uadr_state"){return tmpl.get_uadr().get_state();}
    if (arg == "_lab_uadr_stdistr"){return tmpl.get_uadr().get_state_distr();}
    if (arg == "_lab_uadr_citycl"){return tmpl.get_uadr().get_city_class();}
    if (arg == "_lab_uadr_city"){return tmpl.get_uadr().get_city();}
    if (arg == "_lab_uadr_distr"){return tmpl.get_uadr().get_district();}
    if (arg == "_lab_uadr_strcl"){return tmpl.get_uadr().get_street_class();}
    if (arg == "_lab_uadr_str"){return tmpl.get_uadr().get_street();}
    if (arg == "_lab_uadr_bnum"){
        if (tmpl.get_uadr().get_building_num() == 0) return  "";
        return QString::number(tmpl.get_uadr().get_building_num());
    }
    if (arg == "_lab_uadr_blit"){return tmpl.get_uadr().get_building_lit();}
    if (arg == "_lab_uadr_ofnum"){
        if (tmpl.get_uadr().get_office_num() == 0) return  "";
        return QString::number(tmpl.get_uadr().get_office_num());
    }
    if (arg == "_lab_uadr_oflit"){return  tmpl.get_uadr().get_office_lit();}
    if (arg == "_lab_uadr_postind"){
        if (tmpl.get_uadr().get_post_index() == 0) return  "";
        return QString::number(tmpl.get_uadr().get_post_index());
    }
 // Адрес фактический
    if (arg == "_lab_fadr_cont") {return tmpl.get_adr().get_country();}
    if (arg == "_lab_fadr_statclass"){return tmpl.get_adr().get_state_class();}
    if (arg == "_lab_fadr_state"){return tmpl.get_adr().get_state();}
    if (arg == "_lab_fadr_stdistr"){return tmpl.get_adr().get_state_distr();}
    if (arg == "_lab_fuadr_citycl"){return tmpl.get_adr().get_city_class();}
    if (arg == "_lab_fadr_city"){return tmpl.get_adr().get_city();}
    if (arg == "_lab_fadr_distr"){return tmpl.get_adr().get_district();}
    if (arg == "_lab_fadr_strcl"){return tmpl.get_adr().get_street_class();}
    if (arg == "_lab_fadr_str"){return tmpl.get_adr().get_street();}
    if (arg == "_lab_fadr_bnum"){
        if (tmpl.get_adr().get_building_num() == 0) return  "";
        return QString::number(tmpl.get_adr().get_building_num());
    }
    if (arg == "_lab_fadr_blit"){return tmpl.get_adr().get_building_lit();}
    if (arg == "_lab_fadr_ofnum"){
        if (tmpl.get_adr().get_office_num() == 0) return  "";
        return QString::number(tmpl.get_adr().get_office_num());
    }
    if (arg == "_lab_fadr_oflit"){return  tmpl.get_adr().get_office_lit();}
    if (arg == "_lab_fadr_postind"){
        if (tmpl.get_adr().get_post_index() == 0) return  "";
        return QString::number(tmpl.get_adr().get_post_index());
    }
    return "NULL";
}
