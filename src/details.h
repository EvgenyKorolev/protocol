#ifndef DETAILS_H
#define DETAILS_H

#include <QDomDocument>
#include <QDomElement>
#include <QDomText>
#include <QList>
#include <QString>
#include <QPair>
#include "address.h"

// Этот класс хранит реквезиты

class details
{
public:
    details();                                      // Конструктор по умолчанию
    details(const details& arg);                    // Конструктор копировщик
    details(details&& arg) = default;              // Конструктор копировщик
// Переопределение операций которые возможны с реквезитами
    bool operator == (const details& arg);          // Равенство
    bool operator != (const details& arg);          // Неравенство
    details& operator = (const details& arg);       // Присваивание
    details& operator = (details&& arg) = default;  // Присваивание

    int add_tel(QString* arg);                     // Добавить телефон в список
    int add_fax(QString* arg);                     // Добавить факс в список
    int add_tel(QString arg);                      // Добавить телефон в список (перегружена)
    int add_fax(QString arg);                      // Добавить факс в список (перегружена)

    int set_tel_list(QList<QString>* arg);          // Установить список телефонов
    int set_fax_list(QList<QString>* arg);          // Установить список факсов
    int set_tel_list(QList<QString> arg);           // Установить список телефонов (перегружена)
    int set_fax_list(QList<QString> arg);           // Установить список факсов (перегружена)
    QList<QString> get_tel_list() const;            // Получить список телефонов
    QList<QString> get_fax_list() const;            // Получить список факсов
    int clear_tel();                                // Очистить список телефонов
    int clear_fax();                                // Очистить список факсов
    int del_n_tel(int arg);                         // Удалить телефон под номером АРГ из списка
    int del_top_tel();                              // Удалить последний телефон из списка
    int del_n_fax(int arg);                         // Удалить факс под номером АРГ из списка
    int del_top_fax();                              // Удалить последний факс из списка

    int set_re_post(address* arg);                 // Задать фактический адрес
    int set_ur_post(address* arg);                 // Задать юридический адрес
    int set_re_post(address arg);                 // Задать фактический адрес перегруженная
    int set_ur_post(address arg);                 // Задать юридический адрес перегруженная
    int set_re_post(address& arg);                 // Задать фактический адрес перегруженная
    int set_ur_post(address& arg);                 // Задать юридический адрес перегруженная
    address get_re_post() const;                   // Получить фактический адрес
    address get_ur_post()const;                    // Получить юридический адрес
    int set_inn(unsigned long long int in);        // Задать ИНН
    unsigned long long get_inn() const;            // Получить ИНН
    int set_dir(QPair<QString, QString>* di);      // Задать имя и должность директора
    int set_dir(QPair<QString, QString> di);       // Задать имя и должность директора - перегруженная
    QPair<QString, QString> get_dir() const;       // Получить имя и должность директора
    void set_email(const QString &arg);         // Задать email
    QString get_email() const;                  // Получить email
    void set_name(const QString& arg);          // Задать полное наименование
    QString get_name() const;                   // Получить полное наименование

    QDomElement make_xml();                     // Сформировать XML
    int load_xml(QDomNode *arg);                // Создать объект из XML

    int load_db();                                  // Загрузить из базы даных
    int save_db();                                  // Загрузить в бвзу данных

private:
    QList<QString> list_tel;        // Список телефонов
    QList<QString> list_fax;        // Список факсов
    QPair<address, address> post;   // Адреса - юридический и почтовый
    unsigned long long inn{0};         // ИНН
    QPair<QString, QString> dir{"", ""};    // Директор - должность + ФИО
    QString email{""};                  // Электронная почта
    QString name{""};                   // Полное наименование
};

#endif // DETAILS_H
