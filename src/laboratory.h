#ifndef LABORATORY_H
#define LABORATORY_H

#include "address.h"
#include "details.h"
#include "worker.h"
#include "my_function.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>
#include <QDate>
#include <QMessageBox>
#include <algorithm>

// Класс лаборатории
class laboratory
{
private:
    laboratory();
    laboratory(const laboratory&);
    laboratory& operator=(laboratory&);
public:
    static laboratory& getInstance(){
        static laboratory instance;
        return instance;
    }
    int set_name(QString *arg);     // Установить название организации
    int set_name(QString arg);      // Установить название организации перегруженная
    QString get_name();             // Возвращает название организации
    int set_attestat(QString *arg); // Установить номер аттестата акредитации
    int set_attestat(QString arg);  // Установить номер аттестата акредитации перегруженная
    QString get_attestat();         // Возвращает номер аттестата акредитации
    void set_att_date(QDate *arg); // Установить дату аттестата акредитации
    void set_att_date(QDate arg);  // Установить дату аттестата акредитации перегруженная
    QDate get_att_date();         // Возвращает дату аттестата акредитации

    int set_adr(address *arg);    // Установить адрес
    address get_adr();            // Получить адрес
    void set_det(details *arg);   // Установить реквизиты
    details get_det();            // Получить реквизиты

    int set_uadr(address *arg);   // Установить юридический адрес
    address get_uadr();           // Получить юридичсекий адрес
    int set_padr(address *arg);   // Установить почтовый адрес
    address get_padr();           // Получить почтовы адрес
    worker get_labdir();          // Вернуть начальника лаборатории

    void set_email(const QString &arg);         // Задать email
    QString get_email() const;                  // Получить email
    void set_full_name(const QString& arg);    // Задать полное наименование
    QString get_full_name() const;             // Получить полное наименование

    int set_inn(unsigned long long int arg);    // Устанавливает ИНН
    int set_dir(QPair<QString, QString> arg);   // Устанавливает руководителя
    void set_tel_list(QList<QString> arg);   // Установить список телефонов
    void set_fax_list(QList<QString> arg);   // Установить список факсов

    int add_workers(worker *arg);             // Добавляет работника
    int add_workers(worker arg);             // Добавляет работника
    int set_workers_list(QList<worker>* arg); // Устанавливает список работников
    int set_workers_list(QList<worker> arg);  // Устанавливает список работников (перегруженная)
    QList<worker> get_workers_list();         // Возвращает список работников
    int clear_workers();                      // Очистить список работников

    worker get_manager();      // Возвращает объект работника для начальника лаборатории
    bool test_manager();       // Проверяет есть ли уже начальник лаборатории
    QDomDocument make_xml();
    void laod_xml(QDomDocument *arg);

    int load_db();
    int save_db();

private:
    QString name;
    QString attestat;
    QDate att_date;
    address adr;
    details det;
    QList<worker> workers;

};

#endif // LABORATORY_H
