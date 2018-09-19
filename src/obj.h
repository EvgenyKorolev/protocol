#ifndef OBJ_H
#define OBJ_H
#include "apparaturs.h"
#include "protocol.h"
#include "address.h"
#include "my_function.h"
#include "transformator.h"
#include "fab_app.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDomText>
#include <QList>
#include <QPair>
#include <QTime>
class order;
class protocol;

// Это базовый класс объекта, на его снове создаются классы объектов ЦП и КТП
class obj
{
public:
    obj();                   // Конструктор по умолчанию
    obj(order *arg);         // Конструктор с указанием родителя (заказа)
    obj(const obj &arg);     // Конструктор копировщик
    virtual ~obj();
// Переопределение операций которые возможны с реквезитами
    bool operator == (const obj &arg);            // Равенство
    bool operator != (const obj &arg);            // Неравенство
    obj &operator =(const obj &arg);              // Присваивание

    virtual obj null_obj_1();                               // Обнуляет объект и возвращает пустой объект

    virtual void set_up(order *arg);                         // Устанавливает ссылку на родителя (заказ)
    virtual void set_up(obj *arg);                          // Устанавливает ссылку на родителя (ЦП) Перегруженнная.
    virtual order* get_up() const;                           // Возвращает ссылку на родителя (заказ)
    virtual obj* get_ups() const;                        // Возвращает ссылку на родителя (ЦП)

    virtual int set_name(const QString& arg);                     // Устанавливает имя объекта
    virtual QString get_name() const;                             // Возвращает имя объекта

    virtual int set_voltage(int arg);                      // Устанавливает номинальное напряжение
    virtual int get_voltage() const;                              // Возвращает номинальное напряжение

    virtual int add_pro(protocol *arg);                // Добовляет протокол в список протоколов
    virtual QList<protocol*> get_pro_list() const;            // Возвращает список протоклов
    virtual int clear_pro_list();                           // Очищает список протоколов
    virtual int del_top_pro();                              // Удаляет последний протокло в списке
    virtual int remove_n_pro(int arg);                      // Удаляет протокл под номером АРГ из списка

    virtual int set_adr(address *arg);                      // Устанавливает адрес объекта
    virtual int set_adr(address arg);                      // Устанавливает адрес объекта (Перегруженная)
    virtual address get_adr() const;                              // Возвращает адрес объекта
    virtual int set_sh(const QString& arg);                       // Устанавливает параметр СШ
    virtual QString get_sh() const;                               // Возвращает параметр СШ
    virtual void set_schema(const QString& arg);                       // Устанавливает место обозначения в схеме
    virtual QString get_schema() const;                               // Возвращает место обозначения в схеме

    virtual int set_cp();                                   // Устанавливает статус объекта как ЦП
    virtual int set_ktp();                                  // Устанавливает статус объекта как КТП
    virtual QString get_status() const;                           // Возвращает статус объекта

    virtual int add_maxt(QPair<QTime, QTime> *arg);         // Добавляетм интервал времени макс. нагрузок
    virtual QList<QPair<QTime, QTime>> get_maxt_list() const;    // Возвращает список интервалов времени макс. нагрузок
    virtual int clear_maxt_list();                          // Очищает список интервалов времени макс. нагрузок
    virtual int del_top_maxt();                             // Удаляет порследний интервал времени макс. нагрузок в списке
    virtual int remove_n_maxt(int arg);                     // Удаляет интервал времени макс. нагругок под номером АРГ
    virtual bool add_max_list(QList<QPair<QTime, QTime>> *arg); // Устанвавливает список интервалов времени макс. нагрузок
    virtual bool add_max_list(QList<QPair<QTime, QTime>> arg); // Устанвавливает список интервалов времени макс. нагрузок (Перегруженная)

    virtual int add_mint(QPair<QTime, QTime> *arg);         // Добавляетм интервал времени мин. нагрузок
    virtual QList<QPair<QTime, QTime> > get_mint_list() const;    // Возвращает список интервалов времени мин.. нагрузок
    virtual int clear_mint_list();                          // Очищает список интервалов времени мин. нагрузок
    virtual int del_top_mint();                             // Удаляет порследний интервал времени мин. нагрузок в списке
    virtual int remove_n_mint(int arg);                     // Удаляет интервал времени мин. нагругок под номером АРГ
    virtual bool add_min_list(QList<QPair<QTime, QTime>> *arg); // Устанвавливает список интервалов времени мин. нагрузок
    virtual bool add_min_list(QList<QPair<QTime, QTime>> arg); // Устанвавливает список интервалов времени мин. нагрузок (Перегруженная)

    virtual void add_app(apparaturs *arg);                   // Добовляет прибор в список приборов
    virtual QList<apparaturs*> get_app_list() const;            // Возвращает список приборов
    virtual void clear_app_list();                           // Очищает список приборов
    virtual void del_top_app();                              // Удаляет последний прибор в списке
    virtual void remove_n_app(int arg);                      // Удаляет прибор под номером АРГ из списка
    virtual bool set_app_list(QList<apparaturs*> *arg); // Устанвавливает список приборов
    virtual bool set_app_list(QList<apparaturs*> arg); // Устанвавливает список приборов (Перегруженная)

    virtual QDomElement make_xml_1();                       // Создать xml из объекта, для того, чтобы добавить результат к xml наследуемого класса
    virtual int load_xml_1(QDomNode *arg);              // Загрузить данные из xml

    virtual QDomElement make_xml();                      // Эти методы должны быть проеделены в дочернем классе
    virtual int load_xml(QDomNode *arg);             // Предидущие методы для работы с xml используются как раз для упрощения их реализации
    virtual QString type() const;                           // Возвращает тип записи
    virtual void init(const obj& arg);                      // Инициализирует объект другим объектом
    virtual void init(const obj *arg);                    // Перегруженная функция инициализирует объект другим объектом

    // Это функции для солвместимости интерфейса, они реализованны только в центре питания.
    virtual int add_ktp(obj *arg);              // Добавить КТП
    virtual QList<obj*> get_ktp_list() const;           // Возвращает список содержащий КТП
    virtual int clear_ktp_list();               // Очищает список КТП
    virtual int del_top_ktp();                 // Удаляет последний КТП в списке
    virtual int remove_n_ktp(int arg);           // Удаляет КТП с номером arg из списка

    virtual int set_tr(transformator arg);      // Задаёт тип и параметры трансформатора
    virtual transformator get_tr() const;             // Возвращает ссылку на объект установленного в ЦП трансформатора
    virtual void time_ktp();                // Устанавливает у все ктп интервалы соотвествующие ЦП

    virtual QString get_bd_name() const;     // Сообщает имя файла БД клиента
    virtual QList<QString> ret_uids() const;    // Возвращает список существующих протоколов

protected:
   QString name{""};                            // Название объекта
   QList<protocol*> p_list{QList<protocol*>()};            // Список протоколов на объекте
   address adr{address()};                             // Адрес объекта
   QString sh{""};                              // Строковой параметр СШ
   QString schema{""};        // Место обозначения в схеме
   QString status{""};                          // Вид объекта
   QList<QPair<QTime, QTime>> max_time{QList<QPair<QTime, QTime>>()};     // Список периодов максимальной нагрузки
   QList<QPair<QTime, QTime>> min_time{QList<QPair<QTime, QTime>>()};     // Список периодов минимальной нагрузки
   int voltage{0};                             // Напряжение номинальное
   QList<apparaturs*> appr;                  // Список приборов
   order *up;                               // Ссылка на родиеля объекта (заказ)
   obj *ups;            // Ссылка на родиеля объекта (ЦП)

};
Q_DECLARE_METATYPE(obj*)
//Q_DECLARE_METATYPE(obj)
#endif // OBJ_H
