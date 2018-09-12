#ifndef KLIENT_H
#define KLIENT_H

#include "address.h"
#include "details.h"
#include "fab_order.h"
#include <QVariant>
#include <QString>
#include <QList>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>

class order;

// Этот класс хранит информацию о клиенте
class klient
{
public:
    klient();                               // Конструктор
    klient(const klient &arg);              // Конструктор копировщик
    ~klient();
// Переопределение операций которые возможны с реквезитами
    bool operator == (const klient &arg);   // Равенство
    bool operator != (const klient &arg);   // Неравенство
    klient& operator = (const klient &arg); // Присваивание

    void set_name(QString arg);              // Установить имя
    QString get_name() const;                     // Получить имя
    void set_det(details *arg);              // Установить реквезиты
    details get_det() const;                      // Получить реквезиты

    void set_tel_list(QList<QString> arg);   // Установить список телефонов
    void set_fax_list(QList<QString> arg);   // Установить список факсов

    void set_uadr(address *arg);             // Установить юридический адрес
    address get_uadr() const;                     // Получить юридичсекий адрес
    void set_fadr(address *arg);             // Установить фактический адрес
    address get_fadr() const;                     // Получить фактический адрес
    void set_padr(address *arg);             // Установить почтовый адрес
    address get_padr() const;                     // Получить почтовы адрес

    void set_email(const QString &arg);         // Задать email
    QString get_email() const;                  // Получить email
    void set_full_name(const QString& arg);    // Задать полное наименование
    QString get_full_name() const;             // Получить полное наименование

    void add_orders(order *arg);                // Добавить заявку
    void set_orders_list(QList<order*> *arg);   // Установить список заявок
    QList<order*> get_order_list() const;            // Получить список заявок
    void clear_orders();                        // Очистить список заявок
    void del_n_order(int arg);                  // Удалить заявку под номером АРГ из списка
    void del_top_order();                       // Удалить последную заявку из списка
    int size_orders();                         // Возвращает число заявок в списке

    void set_inn(unsigned long long int arg);    // Устанавливает ИНН
    void set_dir(QPair<QString, QString> arg);   // Устанавливает руководителя

    QDomDocument make_xml();                 // Сформировать XML из объекта
    void load_xml(QDomDocument *arg);        // Сформировать объекти из XML

    int load_db();                          // Загрузить из базы данных
    int save_db();                          // Загрузить в базу данных

    klient null_klient();                   // Сбрасывает все значения и возвращает пустой объект
    QString type(){return "kli";}           // Возвращает тип записи
    klient ret(){return *this;}             // Возвращает значение объекта
    void init(klient *arg);                  // Инициализирует объект другим объектом

    void set_patch(const QString& arg);         // Задать путь к файлу
    QString get_patch() const;                 // Узнать путь к файлу
    void set_fname(const QString& arg);         // Задать имя файла
    QString get_fname() const;                 // Узнать имя файла
    void set_pdirname(const QString& arg);         // Задать имя директории с протоколами
    QString get_pdirname() const;                 // Узнать имя директории с протоколами

private:
    QString name{""};           // Название
    details det;            // Реквезиты
    address fadr;           // Фактический адрес
    QList<order*> orders;   // Список заявок
    QString pth{""};            // Путь к файлу
    QString fname{""};          // Имя файла
    QString pdirname{""};       // Имя файла с протоколами которая должна лежать в том же каталоге
};
Q_DECLARE_METATYPE(klient*)
#endif // KLIENT_H
