#include "var_adapter.h"

var_adapter::var_adapter(obj* pat)
{
    labad = new lab_adapter();
    if (pat->type() == "cp"){
        pather_cp = pat;
        pather_obj = pat;
        pather_order = pat->get_up();
        pather_klient = pather_order->get_up();
    } else if (pat->type() == "ktp"){
        if (pat->get_up() == nullptr && pat->get_ups() != nullptr){
            pather_obj = pat;
            pather_cp = pather_obj->get_ups();
            pather_order = pather_cp->get_up();
            pather_klient = pather_order->get_up();
        } else if(pat->get_ups() == nullptr && pat->get_up() != nullptr) {
            pather_obj = pat;
            pather_cp = nullptr;
            pather_order = pather_obj->get_up();
            pather_klient = pather_order->get_up();
        } else if (pat->get_ups() == nullptr && pat->get_up() == nullptr){
            pather_obj = pat;
            pather_cp = nullptr;
            pather_order = nullptr;
            pather_klient = nullptr;
        }
    }
}
var_adapter::~var_adapter()
{
    delete labad;
}
var_adapter::var_adapter(const var_adapter&& arg)
{
    pather_obj = std::move(arg.pather_obj);
    pather_cp = std::move(arg.pather_cp);
    pather_order = std::move(arg.pather_order);
    pather_klient = std::move(arg.pather_klient);
    labad = std::move(arg.labad);
}
QString var_adapter::get_var(const QString &arg_type, const QString &arg_vname) const
{
    if (arg_type == "lab"){
        return labad->get_var(arg_vname);
    }
    if (arg_type == "obj"){
        if (arg_vname == "_obj_name") return pather_obj->get_name();
        if (arg_vname == "_obj_unom"){
            if (pather_obj->get_voltage() == 0){ return "";}
            return QString::number(pather_obj->get_voltage());
        }
        if (arg_vname == "_obj_sh") return pather_obj->get_sh();
  // Адрес Объекта
        if (arg_vname == "_obj_padr_cont") return pather_obj->get_adr().get_country();
        if (arg_vname == "_obj_padr_statclass") return pather_obj->get_adr().get_state_class();
        if (arg_vname == "_obj_padr_state") return pather_obj->get_adr().get_state();
        if (arg_vname == "_obj_padr_stdistr") return pather_obj->get_adr().get_state_distr();
        if (arg_vname == "_obj_padr_citycl") return pather_obj->get_adr().get_city_class();
        if (arg_vname == "_obj_padr_city") return pather_obj->get_adr().get_city();
        if (arg_vname == "_obj_padr_distr") return pather_obj->get_adr().get_district();
        if (arg_vname == "_obj_padr_strcl") return pather_obj->get_adr().get_street_class();
        if (arg_vname == "_obj_padr_str") return pather_obj->get_adr().get_street();
        if (arg_vname == "_obj_padr_bnum"){
            if (pather_obj->get_adr().get_building_num() == 0) return "";
            return QString::number(pather_obj->get_adr().get_building_num());
            }
        if (arg_vname == "_obj_padr_blit") return pather_obj->get_adr().get_building_lit();
        if (arg_vname == "_obj_padr_ofnum"){
            if (pather_obj->get_adr().get_office_num() == 0) return "";
            return QString::number(pather_obj->get_adr().get_office_num());
            }
        if (arg_vname == "_obj_padr_oflit") return pather_obj->get_adr().get_office_lit();
        if (arg_vname == "_obj_padr_postind"){
            if (pather_obj->get_adr().get_post_index() == 0) return "";
            return QString::number(pather_obj->get_adr().get_post_index());
            }
// ============================================================================================
// Данные о трансформаторе
        if (arg_vname.left(6) == "_trans"){
            if (pather_obj->type() == "cp"){
                if (arg_vname == "_trans_type") return pather_obj->get_tr().get_type();
                if (arg_vname == "_trans_nom") return pather_obj->get_tr().get_mnom();
                if (arg_vname == "_trans_class") return pather_obj->get_tr().get_cls();
                if (arg_vname == "_trans_npmn") return pather_obj->get_tr().get_nom_power();
                if (arg_vname == "_trans_cco") return pather_obj->get_tr().get_obm();
                if (arg_vname == "_trans_nnov1") return pather_obj->get_tr().get_nom_u_1();
                if (arg_vname == "_trans_nnov1") return pather_obj->get_tr().get_nom_u_2();
                if (arg_vname == "_trans_faz"){
                    if (pather_obj->get_tr().test_f() == 0) return "";
                    return QString::number(pather_obj->get_tr().test_f());
                }
            }
            if (pather_obj->type() == "ktp" && pather_cp != nullptr){
                if (arg_vname == "_trans_type") return pather_cp->get_tr().get_type();
                if (arg_vname == "_trans_nom") return pather_cp->get_tr().get_mnom();
                if (arg_vname == "_trans_class") return pather_cp->get_tr().get_cls();
                if (arg_vname == "_trans_npmn") return pather_cp->get_tr().get_nom_power();
                if (arg_vname == "_trans_cco") return pather_cp->get_tr().get_obm();
                if (arg_vname == "_trans_nnov1") return pather_cp->get_tr().get_nom_u_1();
                if (arg_vname == "_trans_nnov1") return pather_cp->get_tr().get_nom_u_2();
                if (arg_vname == "_trans_faz"){
                    if (pather_cp->get_tr().test_f() == 0) return "";
                    return QString::number(pather_cp->get_tr().test_f());
                }

            }
            if (pather_obj->type() == "ktp" && pather_cp == nullptr){
                return "NULL";
            }
        }

// ============================================================================================
// Если нужны танные принципиально о КТП
        if (arg_vname.left(4) == "_ktp"){
            if (pather_obj->type() == "ktp"){
                if (arg_vname == "_ktp_name") return pather_obj->get_name();
                if (arg_vname == "_ktp_unom"){
                    if (pather_obj->get_voltage() == 0){ return "";}
                    return QString::number(pather_obj->get_voltage());
                    }
                if (arg_vname == "_ktp_sh") return pather_obj->get_sh();
          // Адрес КТП
                if (arg_vname == "_ktp_padr_cont") return pather_obj->get_adr().get_country();
                if (arg_vname == "_ktp_padr_statclass") return pather_obj->get_adr().get_state_class();
                if (arg_vname == "_ktp_padr_state") return pather_obj->get_adr().get_state();
                if (arg_vname == "_ktp_padr_stdistr") return pather_obj->get_adr().get_state_distr();
                if (arg_vname == "_ktp_padr_citycl") return pather_obj->get_adr().get_city_class();
                if (arg_vname == "_ktp_padr_city") return pather_obj->get_adr().get_city();
                if (arg_vname == "_ktp_padr_distr") return pather_obj->get_adr().get_district();
                if (arg_vname == "_ktp_padr_strcl") return pather_obj->get_adr().get_street_class();
                if (arg_vname == "_ktp_padr_str") return pather_obj->get_adr().get_street();
                if (arg_vname == "_ktp_padr_bnum"){
                    if (pather_obj->get_adr().get_building_num() == 0) return "";
                    return QString::number(pather_obj->get_adr().get_building_num());
                    }
                if (arg_vname == "_ktp_padr_blit") return pather_obj->get_adr().get_building_lit();
                if (arg_vname == "_ktp_padr_ofnum"){
                    if (pather_obj->get_adr().get_office_num() == 0) return "";
                    return QString::number(pather_obj->get_adr().get_office_num());
                    }
                if (arg_vname == "_ktp_padr_oflit") return pather_obj->get_adr().get_office_lit();
                if (arg_vname == "_ktp_padr_postind"){
                    if (pather_obj->get_adr().get_post_index() == 0) return "";
                    return QString::number(pather_obj->get_adr().get_post_index());
                    }
                return "NULL";
            } else return "NULL";
        }
// ============================================================================================
// Если нужны танные принципиально о ЦП
      if (arg_vname.left(3) == "_cp"){
        if (pather_obj->type() == "cp"){
                if (arg_vname == "_cp_name") return pather_obj->get_name();
                if (arg_vname == "_cp_unom"){
                    if (pather_obj->get_voltage() == 0){ return "";}
                    return QString::number(pather_obj->get_voltage());
                }
                if (arg_vname == "_cp_sh") return pather_obj->get_sh();
        // Адрес ЦП
                if (arg_vname == "_cp_padr_cont") return pather_obj->get_adr().get_country();
                if (arg_vname == "_cp_padr_statclass") return pather_obj->get_adr().get_state_class();
                if (arg_vname == "_cp_padr_state") return pather_obj->get_adr().get_state();
                if (arg_vname == "_cp_padr_stdistr") return pather_obj->get_adr().get_state_distr();
                if (arg_vname == "_cp_padr_citycl") return pather_obj->get_adr().get_city_class();
                if (arg_vname == "_cp_padr_city") return pather_obj->get_adr().get_city();
                if (arg_vname == "_cp_padr_distr") return pather_obj->get_adr().get_district();
                if (arg_vname == "_cp_padr_strcl") return pather_obj->get_adr().get_street_class();
                if (arg_vname == "_cp_padr_str") return pather_obj->get_adr().get_street();
                if (arg_vname == "_cp_padr_bnum"){
                    if (pather_obj->get_adr().get_building_num() == 0) return "";
                    return QString::number(pather_obj->get_adr().get_building_num());
                }
                if (arg_vname == "_cp_padr_blit") return pather_obj->get_adr().get_building_lit();
                if (arg_vname == "_cp_padr_ofnum"){
                    if (pather_obj->get_adr().get_office_num() == 0) return "";
                    return QString::number(pather_obj->get_adr().get_office_num());
                }
                if (arg_vname == "_cp_padr_oflit") return pather_obj->get_adr().get_office_lit();
                if (arg_vname == "_cp_padr_postind"){
                    if (pather_obj->get_adr().get_post_index() == 0) return "";
                    return QString::number(pather_obj->get_adr().get_post_index());
                }
    // Трансформатор
                if (arg_vname == "_cp_tr_type") return pather_obj->get_tr().get_type();
                if (arg_vname == "_cp_tr_nom") return pather_obj->get_tr().get_mnom();
                if (arg_vname == "_cp_tr_class") return pather_obj->get_tr().get_cls();
                if (arg_vname == "_cp_tr_npmn") return pather_obj->get_tr().get_nom_power();
                if (arg_vname == "_cp_tr_cco") return pather_obj->get_tr().get_obm();
                if (arg_vname == "_cp_tr_nnov1") return pather_obj->get_tr().get_nom_u_1();
                if (arg_vname == "_cp_tr_nnov2") return pather_obj->get_tr().get_nom_u_2();
                if (arg_vname == "_cp_tr_faz"){
                    if (pather_obj->get_tr().test_f() == 0) return "";
                    return QString::number(pather_obj->get_tr().test_f());
                }
             return "NULL";
        } else if (pather_obj->type() == "ktp" && pather_cp != nullptr){
            if (arg_vname == "_cp_name") return pather_cp->get_name();
            if (arg_vname == "_cp_unom"){
                if (pather_cp->get_voltage() == 0){ return "";}
                return QString::number(pather_cp->get_voltage());
            }
            if (arg_vname == "_cp_sh") return pather_cp->get_sh();
    // Адрес ЦП
            if (arg_vname == "_cp_padr_cont") return pather_cp->get_adr().get_country();
            if (arg_vname == "_cp_padr_statclass") return pather_cp->get_adr().get_state_class();
            if (arg_vname == "_cp_padr_state") return pather_cp->get_adr().get_state();
            if (arg_vname == "_cp_padr_stdistr") return pather_cp->get_adr().get_state_distr();
            if (arg_vname == "_cp_padr_citycl") return pather_cp->get_adr().get_city_class();
            if (arg_vname == "_cp_padr_city") return pather_cp->get_adr().get_city();
            if (arg_vname == "_cp_padr_distr") return pather_cp->get_adr().get_district();
            if (arg_vname == "_cp_padr_strcl") return pather_cp->get_adr().get_street_class();
            if (arg_vname == "_cp_padr_str") return pather_cp->get_adr().get_street();
            if (arg_vname == "_cp_padr_bnum"){
                if (pather_cp->get_adr().get_building_num() == 0) return "";
                return QString::number(pather_cp->get_adr().get_building_num());
            }
            if (arg_vname == "_cp_padr_blit") return pather_cp->get_adr().get_building_lit();
            if (arg_vname == "_cp_padr_ofnum"){
                if (pather_cp->get_adr().get_office_num() == 0) return "";
                return QString::number(pather_cp->get_adr().get_office_num());
            }
            if (arg_vname == "_cp_padr_oflit") return pather_cp->get_adr().get_office_lit();
            if (arg_vname == "_cp_padr_postind"){
                if (pather_cp->get_adr().get_post_index() == 0) return "";
                return QString::number(pather_cp->get_adr().get_post_index());
            }
// Трансформатор
            if (arg_vname == "_cp_tr_type") return pather_cp->get_tr().get_type();
            if (arg_vname == "_cp_tr_nom") return pather_cp->get_tr().get_mnom();
            if (arg_vname == "_cp_tr_class") return pather_cp->get_tr().get_cls();
            if (arg_vname == "_cp_tr_npmn") return pather_cp->get_tr().get_nom_power();
            if (arg_vname == "_cp_tr_cco") return pather_cp->get_tr().get_obm();
            if (arg_vname == "_cp_tr_nnov1") return pather_cp->get_tr().get_nom_u_1();
            if (arg_vname == "_cp_tr_nnov2") return pather_cp->get_tr().get_nom_u_2();
            if (arg_vname == "_cp_tr_faz"){
                if (pather_cp->get_tr().test_f() == 0) return "";
                return QString::number(pather_cp->get_tr().test_f());
            }
         return "NULL";
        } else return "NULL";
      }

    }
 // ==========================--------------------------================================
// Заявка
    if (arg_type == "order"){
        if (arg_vname == "_ord_num"){
            if (pather_order->get_num() == 0) return "";
            return QString::number(pather_order->get_num());
        }
        if (arg_vname == "_ord_uniq") return pather_order->get_uniq();
        if (arg_vname == "_ord_date") return pather_order->get_date().toString();
        if (arg_vname == "_ord_date_1") return pather_order->get_date().toString("dd.MM.yyyy");
        if (arg_vname == "_ord_date_2") return pather_order->get_date().toString("dd.MM.yy");
        if (arg_vname == "_ord_date_3") return pather_order->get_date().toString("dd.MMM.yyyy");
        if (arg_vname == "_ord_type") return pather_order->type();
        return "NULL";
    }
// Клиент
    if (arg_type == "klient"){
        if (arg_vname == "_kl_name") return pather_klient->get_name();
    // Реквизиты
        if (arg_vname == "_kl_det_inn"){
            if (pather_klient->get_det().get_inn() == 0) return "";
            return QString::number(pather_klient->get_det().get_inn());
        }
        if (arg_vname == "_kl_det_dirpos") return pather_klient->get_det().get_dir().first;
        if (arg_vname == "_kl_det_dirname") return pather_klient->get_det().get_dir().second;
    // Телефоны
        if (arg_vname == "_kl_det_tel"){
            QList<QString> tmp = pather_klient->get_det().get_tel_list();
            if (tmp.size() > 0){return tmp.at(0);}
            return "";
        }
        if (arg_vname == "_kl_det_tel1"){
            QList<QString> tmp = pather_klient->get_det().get_tel_list();
            if (tmp.size() > 1){return tmp.at(1);}
            return "";
        }
        if (arg_vname == "_kl_det_tel2"){
            QList<QString> tmp = pather_klient->get_det().get_tel_list();
            if (tmp.size() > 2){return tmp.at(2);}
            return "";
        }
        if (arg_vname == "_kl_det_tel3"){
            QList<QString> tmp = pather_klient->get_det().get_tel_list();
            if (tmp.size() > 3){return tmp.at(3);}
            return "";
        }
        if (arg_vname == "_kl_det_tel4"){
            QList<QString> tmp = pather_klient->get_det().get_tel_list();
            if (tmp.size() > 4){return tmp.at(4);}
            return "";
        }
    // Факсы
        if (arg_vname == "_kl_det_fax"){
            QList<QString> tmp = pather_klient->get_det().get_fax_list();
            if (tmp.size() > 0){return tmp.at(0);}
            return "";
        }
        if (arg_vname == "_kl_det_fax1"){
            QList<QString> tmp = pather_klient->get_det().get_fax_list();
            if (tmp.size() > 1){return tmp.at(1);}
            return "";
        }
        if (arg_vname == "_kl_det_fax2"){
            QList<QString> tmp = pather_klient->get_det().get_fax_list();
            if (tmp.size() > 2){return tmp.at(2);}
            return "";
        }
        if (arg_vname == "_kl_det_fax3"){
            QList<QString> tmp = pather_klient->get_det().get_fax_list();
            if (tmp.size() > 3){return tmp.at(3);}
            return "";
        }
        if (arg_vname == "_kl_det_fax4"){
            QList<QString> tmp = pather_klient->get_det().get_fax_list();
            if (tmp.size() > 4){return tmp.at(4);}
            return "";
        }
    // Адрес почтовый
        if (arg_vname == "_kl_padr_cont") return pather_klient->get_padr().get_country();
        if (arg_vname == "_kl_padr_statclass") return pather_klient->get_padr().get_state_class();
        if (arg_vname == "_kl_padr_state") return pather_klient->get_padr().get_state();
        if (arg_vname == "_kl_padr_stdistr") return pather_klient->get_padr().get_state_distr();
        if (arg_vname == "_kl_padr_citycl") return pather_klient->get_padr().get_city_class();
        if (arg_vname == "_kl_padr_city") return pather_klient->get_padr().get_city();
        if (arg_vname == "_kl_padr_distr") return pather_klient->get_padr().get_district();
        if (arg_vname == "_kl_padr_strcl") return pather_klient->get_padr().get_street_class();
        if (arg_vname == "_kl_padr_str") return pather_klient->get_padr().get_street();
        if (arg_vname == "_kl_padr_bnum"){
            if (pather_klient->get_padr().get_building_num() == 0) return "";
            return QString::number(pather_klient->get_padr().get_building_num());
        }
        if (arg_vname == "_kl_padr_blit") return pather_klient->get_padr().get_building_lit();
        if (arg_vname == "_kl_padr_ofnum"){
            if (pather_klient->get_padr().get_office_num() == 0) return "";
            return QString::number(pather_klient->get_padr().get_office_num());
        }
        if (arg_vname == "_kl_padr_oflit") return pather_klient->get_padr().get_office_lit();
        if (arg_vname == "_kl_padr_postind"){
            if (pather_klient->get_padr().get_post_index() == 0) return "";
            return QString::number(pather_klient->get_padr().get_post_index());
        }
    // Адрес юридический
        if (arg_vname == "_kl_uadr_cont") return pather_klient->get_uadr().get_country();
        if (arg_vname == "_kl_uadr_statclass") return pather_klient->get_uadr().get_state_class();
        if (arg_vname == "_kl_uadr_state") return pather_klient->get_uadr().get_state();
        if (arg_vname == "_kl_uadr_stdistr") return pather_klient->get_uadr().get_state_distr();
        if (arg_vname == "_kl_uadr_citycl") return pather_klient->get_uadr().get_city_class();
        if (arg_vname == "_kl_uadr_city") return pather_klient->get_uadr().get_city();
        if (arg_vname == "_kl_uadr_distr") return pather_klient->get_uadr().get_district();
        if (arg_vname == "_kl_uadr_strcl") return pather_klient->get_uadr().get_street_class();
        if (arg_vname == "_kl_uadr_str") return pather_klient->get_uadr().get_street();
        if (arg_vname == "_kl_uadr_bnum"){
            if (pather_klient->get_uadr().get_building_num() == 0) return "";
            return QString::number(pather_klient->get_uadr().get_building_num());
        }
        if (arg_vname == "_kl_uadr_blit") return pather_klient->get_uadr().get_building_lit();
        if (arg_vname == "_kl_uadr_ofnum"){
            if (pather_klient->get_uadr().get_office_num() == 0) return "";
            return QString::number(pather_klient->get_uadr().get_office_num());
        }
        if (arg_vname == "_kl_uadr_oflit") return pather_klient->get_uadr().get_office_lit();
        if (arg_vname == "_kl_uadr_postind"){
            if (pather_klient->get_uadr().get_post_index() == 0) return "";
            return QString::number(pather_klient->get_uadr().get_post_index());
        }
    // Адрес фактический
        if (arg_vname == "_kl_fadr_cont") return pather_klient->get_fadr().get_country();
        if (arg_vname == "_kl_fadr_statclass") return pather_klient->get_fadr().get_state_class();
        if (arg_vname == "_kl_fadr_state") return pather_klient->get_fadr().get_state();
        if (arg_vname == "_kl_fadr_stdistr") return pather_klient->get_fadr().get_state_distr();
        if (arg_vname == "_kl_fadr_citycl") return pather_klient->get_fadr().get_city_class();
        if (arg_vname == "_kl_fadr_city") return pather_klient->get_fadr().get_city();
        if (arg_vname == "_kl_fadr_distr") return pather_klient->get_fadr().get_district();
        if (arg_vname == "_kl_fadr_strcl") return pather_klient->get_fadr().get_street_class();
        if (arg_vname == "_kl_fadr_str") return pather_klient->get_fadr().get_street();
        if (arg_vname == "_kl_fadr_bnum"){
            if (pather_klient->get_fadr().get_building_num() == 0) return "";
            return QString::number(pather_klient->get_fadr().get_building_num());
        }
        if (arg_vname == "_kl_fadr_blit") return pather_klient->get_fadr().get_building_lit();
        if (arg_vname == "_kl_fadr_ofnum"){
            if (pather_klient->get_fadr().get_office_num() == 0) return "";
            return QString::number(pather_klient->get_fadr().get_office_num());
        }
        if (arg_vname == "_kl_fadr_oflit") return pather_klient->get_fadr().get_office_lit();
        if (arg_vname == "_kl_fadr_postind"){
            if (pather_klient->get_fadr().get_post_index() == 0) return "";
            return QString::number(pather_klient->get_fadr().get_post_index());
        }
        return "NULL";
    }
    return "NULL";
}
QList<QPair<QTime, QTime>> var_adapter::get_maxt_list() const
{
    return pather_obj->get_maxt_list();
}
QList<QPair<QTime, QTime> > var_adapter::get_mint_list() const
{
    return pather_obj->get_mint_list();

}
QList<apparaturs*> var_adapter::get_app_list() const
{
    return  pather_obj->get_app_list();
}
QList<QList<QString> > var_adapter::get_app_table() const
{
    QList<QList<QString> > ret;
    QList<apparaturs*> tmpap = pather_obj->get_app_list();
    for (auto it : tmpap){
        QList<QString> tmplist;
        tmplist.append(it->get_name()); // Название прибора
        tmplist.append(it->get_mdata().toString()); // Дата... чего-то там, пока непонятно (выпуска наверное)
        // Номер свидетельства о поверке, дата поверки, дата очередной поверки
        QList<QPair<QPair<QString, QDate>, QDate>> tmpver = it->get_verification_list();
        if (!tmpver.empty()){
            tmplist.append("");
            tmplist.append("");
            tmplist.append("");
        } else {
            QPair<QPair<QString, QDate>, QDate> tmpv = *std::max_element(tmpver.begin(), tmpver.end(), [](const QPair<QPair<QString, QDate>, QDate>& arg1,
                                                                        const QPair<QPair<QString, QDate>, QDate>& arg2){ return arg1.second < arg2.second;});
            tmplist.append(tmpv.first.first);
            tmplist.append(tmpv.first.second.toString());
            tmplist.append(tmpv.second.toString());
        }
        tmplist.append(it->get_type()); // Класс прибора (Тип СИ)
        tmplist.append(it->get_mnom()); // Заводской номер
        tmplist.append(it->get_clas()); // Класс точности
    }
    return ret;
}
QPair<QString, QString> var_adapter::get_maxt_int() const
{
    QPair<QString, QString> ret;
    QList<QPair<QTime, QTime> > tmpint = pather_obj->get_maxt_list();
    QPair<QTime, QTime> tmpi = *std::max_element(tmpint.begin(), tmpint.end(), [](const QPair<QTime, QTime>& arg1,
                                                const QPair<QTime, QTime>& arg2){return (arg1.second.msecsSinceStartOfDay() - arg1.first.msecsSinceStartOfDay()) < (arg2.second.msecsSinceStartOfDay() - arg2.first.msecsSinceStartOfDay());});
    ret.first = tmpi.first.toString();
    ret.second = tmpi.second.toString();
    return  ret;
}
QPair<QString, QString> var_adapter::get_mint_int() const
{
    QPair<QString, QString> ret;
    QList<QPair<QTime, QTime> > tmpint = pather_obj->get_mint_list();
    QPair<QTime, QTime> tmpi = *std::max_element(tmpint.begin(), tmpint.end(), [](const QPair<QTime, QTime>& arg1,
                                                const QPair<QTime, QTime>& arg2){return (arg1.second.msecsSinceStartOfDay() - arg1.first.msecsSinceStartOfDay()) < (arg2.second.msecsSinceStartOfDay() - arg2.first.msecsSinceStartOfDay());});
    ret.first = tmpi.first.toString();
    ret.second = tmpi.second.toString();
    return  ret;
}
