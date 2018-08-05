#ifndef WORKER_H
#define WORKER_H

#include <QString>
#include <QVariant>
#include <QDomDocument>
#include <QDomElement>
//#include <openssl/sha.h>
#include "address.h"

// Этот класс хранит данные сотрудника

class worker
{
public:
    worker();

    int set_name(QString *arg);     // Установить имя
    int set_name(QString arg);      // Установить имя (перегруженная)
    QString get_name() const;       // Возвращает имя
    int set_surname(QString *arg);  // Установить фамилию
    int set_surname(QString arg);   // Установить фамилию (перегруженная)
    QString get_surname() const;    // Возвращает фамилию
    int set_fname(QString *arg);    // Установить отчество
    int set_fname(QString arg);     // Установить отчество (перегруженная)
    QString get_fname() const;      // Возвращает отчество
    int set_position(QString *arg); // Установить должность
    int set_position(QString arg);  // Установить должность (перегруженная)
    QString get_position() const;   // Возвращает должность
    int set_tel(QString *arg);      // Установить телефон
    int set_tel(QString arg);       // Установить телефон (перегруженная)
    QString get_tel() const;        // Возвращает телефон
    int set_post(QString *arg);     // Установить Email
    int set_post(QString arg);      // Установить Email (перегруженная)
    QString get_post() const;       // Возвращает Email
    int set_login(QString *arg, QString *arg2); // Установить логин
    int set_login(QString arg, QString arg2);   // Установить логин (перегруженная)
    QString get_login() const;                  // Возвращает логин
    int set_pass(QString *arg, QString *arg2);  // Установить пароль
    int set_pass(QString arg, QString arg2);    // Установить пароль (перегруженная)
    bool test_pass(QString *arg);               // Тестирует пароль
    bool test_pass(QString arg);                // Тестирует пароль (перегруженная)
    int set_adr(address *arg);                  // Установить адрес
    int set_adr(address arg);                   // Установить адрес (перегруженная)
    address get_adr();                          // Возвращает адрес

    int load_xml(QDomNode *arg);            // Заполняет объект их xml
    QDomElement make_xml();                     // Создаёт xml из объекта
    int load_db();
    int save_db();

    worker null_worker();

private:
    QString name;
    QString surname;
    QString fname;
    QString position;
    QString tel;
    QString post;
    QString login;
    QString pass;
    address adr;
};
Q_DECLARE_METATYPE(worker)
#endif // WORKER_H
