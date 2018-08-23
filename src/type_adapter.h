#ifndef TYPE_ADAPTER_H
#define TYPE_ADAPTER_H

#include <QString>
#include <QList>
#include <algorithm>
#include "type_const_loader.h"

class type_adapter
{
public:
    type_adapter(const QList<type_obj>& arg);
    void add_type(const QString& arg);
    QString get_var(const QString &cls, const QString &varname);
private:
    QList<type_obj> data_list{QList<type_obj>()};
};

#endif // TYPE_ADAPTER_H
