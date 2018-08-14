#ifndef LAB_ADAPTER_H
#define LAB_ADAPTER_H

#include <QString>
#include "laboratory.h"

class lab_adapter
{
public:
    lab_adapter();
    QString get_var(const QString& arg, const QString& style) const;
};

#endif // LAB_ADAPTER_H
