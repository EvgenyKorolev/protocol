#include "save_klient.h"

bool save_klient::save_xml(klient* arg, QString p)
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

// Надо переделать эти функции для сохранения всего клиента и только базы
bool save_db(klient* arg, QString p)
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
bool save_all(klient* arg, QString p)
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
