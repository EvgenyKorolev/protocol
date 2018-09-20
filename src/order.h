#ifndef ORDER_H
#define ORDER_H
#include "my_function.h"
#include <QString>
#include <QDate>
#include <QVariant>
class QDomNode;
class QDomElement;
class obj;
class klient;

// Это заказ клиента он хранит информацию об объектах на которых проводятся испытания
class order
{
public:
    order();                                        // Конструктор по умолчанию
    order(klient *arg);                             // Конструктор c указанием родителя
    order(const order &arg);                        // Конструктор копировщик
    ~order();
// Переопределение операций которые возможны с реквезитами
    bool operator == (const order &arg);            // Равенство
    bool operator != (const order &arg);            // Неравенство
    order &operator =(const order &arg);            // Присваивание

    int set_up(klient *arg);                        // Установить родителья (клиента)
    klient* get_up();                               // Узнать родителя (клиента)

    int set_num(unsigned int arg);                  // Установить уникальный номенр
    unsigned int get_num() const;                         // Получить уникальный номер
    int set_uniq(QString arg);                      // Установить уникальную строку
    QString get_uniq() const;                             // Получить уникальную строку
    int set_date(QDate arg);                        // Установить дату
    QDate get_date() const;                               // Получить дату

    int add_obj(obj *arg);                          // Добавить объект к списку
    int set_obj_list(QList<obj*>* arg);             // Установить список объектов
    QList<obj*> get_obj_list() const;                     // Получить список объектов
    int clear_obj_list();                           // Очистить список объектов
    int del_n_obj(int arg);                         // Удалить объект под номером АРГ из списка
    int del_top_obj();                              // Удалить последний объект из списка

    QDomElement make_xml();                         // Сформировать xml из объекта
    int load_xml(QDomNode *arg, klient *ups);   // Создать объект их xml
    QString type() {return "ord";}     // Возвращает тип записи
    order ret(){return *this;}             // Возвращает значение объекта
    void init(const order &arg);                      // Инициализирует объект другим объектом
    void init_new(const order &arg);   // Инициализирует объект другим объектом меняя уникальные номера протоколов
    QString get_bd_name() const;     // Сообщает имя файла БД клиента
    QList<QString> ret_uids() const;       // Возвращает список существующих протоколов

private:
    QString uniq;               // Уникальная строка
    QDate date;                 // Дата создания заявки (можно менять)
    unsigned int number;        // Уникальный номер
    QList<obj*> obj_list;       // Список объектов в заказе
    klient *up;                 // Указатель на родительский объект клиента сделавшего заказ

    friend int my_fnc::xml_to_date(QDomElement arg, QDate &dat);
};
Q_DECLARE_METATYPE(order*)
#endif // ORDER_H
