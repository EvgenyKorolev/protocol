#ifndef SAVE_KLIENT_H
#define SAVE_KLIENT_H
#include <QFile>
#include <QDialog>
#include <QObject>
#include <QTextStream>
#include <QDomNode>
#include "yes_no.h"
#include "klient.h"
// Класс для сохранения клиента в файл
class save_klient
{
public:
    save_klient() = default;
    static bool save_xml(klient* arg, QString p);
    static bool save_db(klient* arg, QString p);
    static bool save_all(klient* arg, QString p);
};

#endif // SAVE_KLIENT_H
