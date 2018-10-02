#ifndef VAR_ADAPTER_H
#define VAR_ADAPTER_H

#include "klient.h"
#include "order.h"
#include "obj.h"
#include "cp.h"
#include "ktp.h"
#include "apparaturs.h"
#include "lab_adapter.h"
#include <QString>
#include <QList>
#include <QTime>
#include <algorithm>
// Адаптер переменных зависящих от родительских объектов (клиента) и настроек лаборатории.
class var_adapter
{
public:
    var_adapter() = delete;
    var_adapter(const var_adapter& arg) = delete;
    var_adapter(var_adapter&& arg);
    var_adapter(obj* pat);
    ~var_adapter();
    QString get_var(const QString& arg_type, const QString& arg_vname, const QString& style = "") const;
    QList<QPair<QTime, QTime>> get_maxt_list() const;
    QList<QPair<QTime, QTime> > get_mint_list() const;
    QList<apparaturs*> get_app_list() const;
    QList<QList<QString> > get_app_table() const;
    QPair<QString, QString> get_maxt_int() const;
    QPair<QString, QString> get_mint_int() const;
    static QString get_app_table(const QList<apparaturs*>* lst, const QString& source, const QString& style = "")
    {
        if (lst == nullptr || lst->size() == 0) return "";
        QString ret{""};
        QString act_adta{""}, next_data{""};
        if (lst->size() == 0) return "";
        ret += "<table";
        if (style != ""){
            ret += " style = \"" + style + "\"";
        } else {
            ret += " width=\"100%\" align=\"center\" bordercolor=\"black\" border=\"1\" cellspacing=\"0\"";
        }
        ret += ">";
        ret += "<tr>"
               "<td align=\"center\">  №<br> п/<br>п "
                "</td>"
                "<td align=\"center\"> Наименование<br> СИ "
                "</td>"
                "<td align=\"center\"> Тип СИ "
                "</td>"
                "<td align=\"center\"> Заводской<br> номер "
                "</td>"
                "<td align=\"center\"> Номер <br>свидетельства о <br>поверке и дата <br>поверки "
                "</td>"
                "<td align=\"center\"> Дата <br>очередной <br>поверки "
                "</td>";
        ret += "</tr>";
        int i{0};
        for (auto it = lst->begin(); it != lst->end(); ++it){
            ++i;
            if (source.back() == "p"){
                act_adta = (*it)->get_act_date().toString() + "&nbspг.";
                next_data = (*it)->get_next_date().toString() + "&nbspг.";
            }
            if (source.back() == "1"){
                act_adta = (*it)->get_act_date().toString("dd.MM.yyyy") + "&nbspг.";
                next_data = (*it)->get_next_date().toString("dd.MM.yyyy") + "&nbspг.";
            }
            if (source.back() == "2"){
                act_adta = (*it)->get_act_date().toString("dd.MM.yy") + "&nbspг.";
                next_data = (*it)->get_next_date().toString("dd.MM.yy") + "&nbspг.";
            }
            if (source.back() == "3"){
                act_adta = (*it)->get_act_date().toString("dd.MMM.yyyy") + "&nbspг.";
                next_data = (*it)->get_next_date().toString("dd.MMM.yyyy") + "&nbspг.";
            }
            if (source.back() == "4"){
                act_adta = (*it)->get_act_date().toString("dd.MMMM.yyyy") + "&nbspг.";
                next_data = (*it)->get_next_date().toString("dd.MMMM.yyyy") + "&nbspг.";
            }
            ret += "<tr>"
                   "<td align=\"center\"> " + QString::number(i) +
                    "</td>"
                    "<td align=\"center\"> " + (*it)->get_name() +
                    "</td>"
                    "<td align=\"center\"> " + (*it)->get_type() +
                    "</td>"
                    "<td align=\"center\"> " + (*it)->get_mnom() +
                    "</td>"
                    "<td align=\"center\"> " + (*it)->get_act_nom() + "<br>" + act_adta +
                    "</td>"
                    "<td align=\"center\"> " + next_data +
                    "</td>";
            ret += "</tr>";
        }
        ret += "</table>";
        return ret;
    }
private:
    QString get_app_table(const QString& source, const QString& style = "") const;
    obj* pather_obj;
    obj* pather_cp;
    order* pather_order;
    klient* pather_klient;
    lab_adapter* labad;
};

#endif // VAR_ADAPTER_H
