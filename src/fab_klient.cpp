#include "fab_klient.h"

fab_klient::fab_klient(){}
klient* fab_klient::create()
{
    return new klient();
}
