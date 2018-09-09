#include "fab_klient.h"

fab_klient::fab_klient(){}
klient* fab_klient::create()
{
    return new klient();
}
klient* fab_klient::create_new()
{
    create_klent_menu* newkln = new create_klent_menu();
    if (newkln->exec() == QDialog::Accepted){

    }
    return nullptr;
}
