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
    static klient* create();
    static klient* create_new();
};

#endif // FAB_KLIENT_H
