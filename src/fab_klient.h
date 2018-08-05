#ifndef FAB_KLIENT_H
#define FAB_KLIENT_H
#include "klient.h"
class klient;
// Класс создающий klient и выделяющий под него память
class fab_klient
{
public:
    fab_klient();
    klient* create();
};

#endif // FAB_KLIENT_H
