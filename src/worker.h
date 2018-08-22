#ifndef WORKER_H
#define WORKER_H

#include "address.h"
#include <QString>
#include <QVariant>
#include <QDomDocument>
#include <QDomElement>
#include <utility>
//#include <openssl/sha.h>
enum class fio{nf_surname, surname_nf, name_surname, surname_name, full};
// Этот класс хранит данные сотрудника
class worker
{
public:
    worker();
    worker(const worker& arg) = default;
    worker(worker&& arg) = default;
    worker& operator=(const worker& arg) = default;
    worker& operator=(worker&& arg) = default;
    bool operator==(worker& arg);
    bool operator!=(worker& arg);
    int set_name(const QString& arg);     // Установить имя
    int set_name(QString&& arg);      // Установить имя (перегруженная)
    QString get_name() const;       // Возвращает имя
    int set_surname(const QString& arg);  // Установить фамилию
    int set_surname(QString&& arg);   // Установить фамилию (перегруженная)
    QString get_surname() const;    // Возвращает фамилию
    int set_fname(const QString& arg);    // Установить отчество
    int set_fname(QString&& arg);     // Установить отчество (перегруженная)
    QString get_fname() const;      // Возвращает отчество
    int set_position(const QString& arg); // Установить должность
    int set_position(QString&& arg);  // Установить должность (перегруженная)
    QString get_position() const;   // Возвращает должность
    int set_tel(const QString& arg);      // Установить телефон
    int set_tel(QString&& arg);       // Установить телефон (перегруженная)
    QString get_tel() const;        // Возвращает телефон
    int set_post(const QString& arg);     // Установить Email
    int set_post(QString&& arg);      // Установить Email (перегруженная)
    QString get_post() const;       // Возвращает Email
    int set_login(const QString& arg, const QString& arg2); // Установить логин
    QString get_login() const;                  // Возвращает логин
    int set_pass(const QString& arg, const QString& arg2);  // Установить пароль
    bool test_pass(const QString& arg);               // Тестирует пароль
    int set_adr(address *arg);                  // Установить адрес
    int set_adr(address arg);                   // Установить адрес (перегруженная)
    address get_adr();                          // Возвращает адрес
    void inv_meneger();                 // Сменить статус начальника лаборатории
    bool test_meneger() const;          // Проверить является ли начальником маборатории

    static QString get_fio(const worker& arg, fio format = fio::nf_surname);
    int load_xml(QDomNode *arg);            // Заполняет объект их xml
    QDomElement make_xml();                 // Создаёт xml из объекта
    int load_db();
    int save_db();

    worker null_worker();

private:
    QString name{""};
    QString surname{""};
    QString fname{""};
    QString position{""};
    QString tel{""};
    QString post{""};
    QString login{""};
    QString pass{""};
    bool manager{false};  // Директор ли этот сотрудник. Директоров может быть больше одного, но учитывается только первый из них.
    address adr;
};
Q_DECLARE_METATYPE(worker)
#endif // WORKER_H
