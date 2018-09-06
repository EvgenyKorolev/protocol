#ifndef FAB_KLIENT_H
#define FAB_KLIENT_H
#include "klient.h"
#include "create_klent_menu.h"
class klient;
// Класс создающий klient и выделяющий под него память
class fab_klient
{
public:
    fab_klient();
    klient* create() const;
    klient* create_new() const;
};

#endif // FAB_KLIENT_H
