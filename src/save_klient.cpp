#include "save_klient.h"

bool save_klient::save_xml(klient* arg, const QString& p)
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
bool save_klient::save_db(klient* arg, const QString& p)
{
    return QFile::copy(arg->get_patch() + "/" + arg->get_pdirname(), p);
}
bool save_klient::save_all(klient* arg, const QString& p_xml, const QString& p_db)
{
    return (save_xml(arg, p_xml) || save_db(arg, p_db));
}
