#include "open_klient.h"

open_klient::open_klient()
{
}
klient* open_klient::load(QString p)
{
    QDomDocument savedoc;
    QFile in(p);
    if (in.open(QIODevice::ReadOnly)){
        savedoc.setContent(&in);
        in.close();
    }
    fab_klient fabk;
    klient *ret = fabk.create();
    ret->load_xml(&savedoc);
    return ret;
}
