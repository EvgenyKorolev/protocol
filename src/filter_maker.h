#ifndef FILTER_MAKER_H
#define FILTER_MAKER_H

#include <QString>
#include <QRegExp>

class filter_maker
{
public:
    filter_maker(QString arg, bool eq);
    QRegExp result();
private:
    QRegExp _res_reg;
};

#endif // FILTER_MAKER_H
