#ifndef OPEN_KLIENT_H
#define OPEN_KLIENT_H
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include "klient.h"
#include "fab_klient.h"
// Класс для загрузки клиента из файла
class open_klient
{
public:
    open_klient();
    klient* load(QString p);
};

#endif // OPEN_KLIENT_H
