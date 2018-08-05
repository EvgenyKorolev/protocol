#ifndef TYPE_ADAPTER_H
#define TYPE_ADAPTER_H

#include <QString>
#include <QList>
#include <algorithm>
#include "type_const_loader.h"

class type_adapter
{
public:
    type_adapter();
    QString get_var(const QString &type, const QString &varname);
};

#endif // TYPE_ADAPTER_H
