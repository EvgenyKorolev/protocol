#ifndef CONST_ADAPTER_H
#define CONST_ADAPTER_H

#include <QString>
#include <QList>
#include <algorithm>
#include <memory>
#include "const_loader.h"
#include "const_obj.h"

class const_adapter
{
public:
    const_adapter(const QString& type);
    const_adapter(const_adapter& arg);
    const_adapter(const_adapter&& arg);
    const_adapter& operator=(const_adapter& arg);
    const_adapter& operator=(const_adapter&& arg);
    bool is_valid();
    QString get_var(const QString &varname);
    bool change_type(const QString& type);
private:
    const_obj data;
    bool valid{false};
};

#endif // CONST_ADAPTER_H
