#ifndef TYPE_ADAPTER_H
#define TYPE_ADAPTER_H

#include "type_const_loader.h"
#include "type_obj.h"
#include <QString>
#include <QList>
#include <algorithm>
#include <cstddef>

class type_adapter
{
public:
    type_adapter();
    type_adapter(const QList<type_obj>& arg);
    void set_lst(const QList<type_obj>& arg);
    void add_type(const QString& arg);
    void del_type(const QString& arg);
    QString get_var(const QString &cls, const QString &varname) const;
    bool test_duplicate() const;
    void clear();
private:
    void test_d();
    QList<type_obj> data_list{QList<type_obj>()};
    bool duplication{false};
};

#endif // TYPE_ADAPTER_H
