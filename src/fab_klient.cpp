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
        klient* ret = new klient();
        // Название клиента Путь к файлу Имя файла
        // std::tuple<QString, QString, QString> result() const;
        std::tuple<QString, QString, QString> tmp = newkln->result();
        ret->set_name(std::get<0>(tmp));
        ret->set_patch(std::get<1>(tmp));
        ret->set_fname(std::get<2>(tmp));
        ret->set_pdirname(std::get<2>(tmp));
        return ret;
    }
    return nullptr;
}
