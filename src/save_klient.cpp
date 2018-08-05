#include "save_klient.h"

save_klient::save_klient()
{
}
bool save_klient::save(klient* arg, QString p)
{
    QDomDocument savedoc = arg->make_xml();
    QFile out(p);
    if (out.open(QIODevice::WriteOnly)){
        QTextStream stream(&out);
        savedoc.save(stream, 1);
        out.close();
    }
    return true;
}
