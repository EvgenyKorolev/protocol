#ifndef ADDRESS_H
#define ADDRESS_H

#include <QString>
#include <QPair>
#include <QDomNode>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>

// Этот класс хранит компоненты адреса

class address
{
public:
    address();                                  // Конструктор по умолчанию
    address(const address &arg);                // Конструктор копировщик
    ~address();                                 // Деструктор
    int clear_address();                        // Функция очищающая объект "адрес"

    int set_country(QString* str);              // Установить название страны
    QString get_country() const;                      // Получить название страны
    int set_state(QString* str);                // Установить регион (субъект РФ)
    QString get_state() const;                        // Получить регион (субъект РФ)
    int set_state_distr(QString* str);          // Установить район в регионе
    QString get_state_distr() const;                  // Получить район в регионе
    int set_city(QString* str);                 // Установить город (населенный пункт)
    QString get_city() const;                         // Получить город (населенный пункт)
    int set_district(QString* str);             // Установить район
    QString get_district() const;                     // Получить район
    int set_street(QString* str);               // Установить улица
    QString get_street() const;                       // Получить улица
    int set_street_class(QString* str);         // Установить вид улицы (улица, проспект...)
    QString get_street_class() const;                 // Получить вид улицы (улица, проспект...)
    int set_building(QPair<int, QString>* pr);  // Установить Номер дома и литер если есть
    QPair<int, QString> get_building() const;         // Получить Номер дома и литер если есть
    int set_office(QPair<int, QString>* pr);    // Установить Номер офиса (и литер если есть)
    QPair<int, QString> get_office() const;           // Получить Номер офиса (и литер если есть)
    unsigned int get_post_index() const;              // Получить Почтовый индекс
    int set_post_index(unsigned int ind);       // Установить Почтовый индекс
    int set_state_class(QString* str);          // Установить Класс региона (республика, область...)
    QString get_state_class() const;                  // Получить Класс региона (республика, область...)
    int set_city_class(QString* str);           // Установить Класс населенного пункта (Город, село...)
    QString get_city_class() const;                   // Получить Класс населенного пункта (Город, село...)
    QString get_adr_str() const;                      // Выдаёт строчу с адресом

    int set_office_num(int arg);                // Установить номер офиса отдельно
    int set_building_num(int arg);              // Установить номер здания отдельно
    int set_office_lit(QString* arg);           // Установить литер офиса отдельно
    int set_building_lit(QString* arg);         // Установить литер офиса отдельно

    int get_office_num() const;                       // Получить номер офиса отдельно
    int get_building_num() const;                     // Получить номер здания отдельно
    QString get_office_lit() const;                   // Получить литер офиса отдельно
    QString get_building_lit() const;                 // Получить литер офиса отдельно

    int load_xml(QDomNode *my_dom);         // Загружает данные в объект из переданного по ссылке объекта XML объект долен быть QDomDocument с дочерним элиментом "address" содержащим наши данные
    QDomElement make_xml() const;                     // Возвращает XML объект QDomElement с именем "address" содержащий данные объекта
    int load_db();                         // Должен выполнить подготовку к получению из базы данных. Надо реализовать
    int save_db() const;                         // Должен выполнить подготовку к загрузке в базу данных. Надо реализовать
// Переопределение операций которые возможны с адресом
    bool operator == (const address &arg);      // Равенство
    bool operator != (const address &arg);      // Неравенство
    address& operator = (const address &arg);   // Присваивание
// Перегрузка функций устанавливающих различные значения
    int set_country(QString str);              // Установить название страны
    int set_state(QString str);                // Установить Регион (субъект РФ)
    int set_state_distr(QString str);          // Установить район в регионе
    int set_city(QString str);                 // Установить Город (населенный пункт)
    int set_district(QString str);             // Установить Район
    int set_street(QString str);               // Установить Улица
    int set_street_class(QString str);         // Установить вид улицы (улица, проспект...)
    int set_building(QPair<int, QString> pr);  // Установить Номер дома и литер если есть
    int set_office(QPair<int, QString> pr);    // Установить Номер офиса (и литер если есть)
    int set_state_class(QString str);          // Установить Класс региона (республика, область...)
    int set_city_class(QString str);           // Установить Класс населенного пункта (Город, село...)
    int set_office_lit(QString arg);           // Установить литер офиса отдельно
    int set_building_lit(QString arg);         // Установить литер офиса отдельно

private:
    QString country{""};                 // Страна
    QString state{""};                   // Регион (субъект РФ)
    QString state_class{""};             // Класс региона (республика, область...)
    QString state_district{""};          // Район региона (Пестречинский и т.д.)
    QString city{""};                    // Город (населенный пункт)
    QString city_class{""};              // Класс населенного пункта (Город, село...)
    QString district{""};                // Район
    QString street{""};                  // Улица
    QString street_class{""};            // Вид улицы (улица, проспект...)
    QPair<int, QString> building;    // Номер дома и литер если есть
    QPair<int, QString> office;      // Номер офиса (и литер если есть)
    unsigned int post_index{0};         // Почтовый индекс

};

#endif // ADDRESS_H
