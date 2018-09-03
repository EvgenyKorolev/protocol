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
    var_adapter(const var_adapter&& arg);
    var_adapter(obj* pat);
    ~var_adapter();
    QString get_var(const QString& arg_type, const QString& arg_vname, const QString& style = "") const;
    QList<QPair<QTime, QTime>> get_maxt_list() const;
    QList<QPair<QTime, QTime> > get_mint_list() const;
    QList<apparaturs*> get_app_list() const;
    QList<QList<QString> > get_app_table() const;
    QPair<QString, QString> get_maxt_int() const;
    QPair<QString, QString> get_mint_int() const;
private:
    QString get_app_table(const QString& source, const QString& style = "") const;
    obj* pather_obj;
    obj* pather_cp;
    order* pather_order;
    klient* pather_klient;
    lab_adapter* labad;
};

#endif // VAR_ADAPTER_H
