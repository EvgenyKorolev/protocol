#ifndef APPARATURS_H
#define APPARATURS_H

#include "my_function.h"
#include <QString>
#include <QPair>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>
#include <QDate>
#include <QVariant>
#include <algorithm>

// Это базовый класс для всех приборов
using vared_type = QPair<QPair<QString, QDate>, QDate>;
class apparaturs
{
public:
    apparaturs();
    apparaturs(apparaturs *arg);
    apparaturs(const apparaturs& arg);
    apparaturs(apparaturs&& arg) = default;
    ~apparaturs() = default;
    apparaturs& operator=(const apparaturs& arg) = default;
    apparaturs& operator=(apparaturs&& arg) = default;
    void init(apparaturs *arg);

    int set_name(const QString& arg); // Установить имя
    int set_name(QString&& arg);  // Установить имя (перегруженная)
    QString get_name() const;         // Узнать имя
    int set_mdata(const QDate& arg);  // Установить дату выпуска прибора
    int set_mdata(QDate&& arg);   // Установить дату выпуска прибора (перегруженная)
    QDate get_mdata() const;          // Узнать дату выпуска прибора
    QDate get_real_ver();     // Узнать дату последней поверки

    int add_verification(QPair<QPair<QString, QDate>, QDate> *arg);             // Добавить в список дат и номеров свидетельств поверки значение
    int set_verification_list(QList<QPair<QPair<QString, QDate>, QDate>>* arg); // Установить список дат и номеров свидетельств поверки
    QList<QPair<QPair<QString, QDate>, QDate>> get_verification_list() const;        // Возвращает список дат и номеров свидетельств поверки
    int clear_verification();                                                   // Очищает список дат и номеров свидетельств поверки

    int set_type(const QString& arg);  // Установить класс СИ
    int set_type(QString&& arg);   // Установить класс СИ (перегруженная)
    QString get_type() const;          // Узнать класс СИ
    int set_mnom(const QString& arg); // Установить заводской номер
    int set_mnom(QString&& arg);  // Установить заводской номер (перегруженная)
    QString get_mnom() const;         // Узнать заводской номер
    QString get_clas() const;         // Узнать класс точности
    void set_clas(const QString& arg);  // Установить класс точности

    QString get_act_nom() const;  // Узнать последний номер поверки
    QDate get_act_date() const;   // Узнать последнюю дату поверки
    QDate get_next_date() const;  // Узнать дату следующей поверки

    void load_xml(QDomNode *my_dom);
    QDomElement make_xml();
    int load_xml_1(QDomNode *my_dom);
    QDomElement make_xml_1();
    int load_db_1();
    int save_db_1();
    void set_uniq(const QString& arg);
    QString get_uniq() const;

protected:
    void sort_date();   // Сортировка списка данных о поверках по дате поверки
    QPair<QPair<QString, QDate>, QDate> get_max_ver() const;   // Возвращает данные о последней поверке
    QString _name{""};       // Название прибора
    QDate _mdata{1, 1, 1};        // Дата... чего-то там, пока непонятно (выпуска наверное)
    QList<QPair<QPair<QString, QDate>, QDate>> _verification;   // Номер свидетельства о поверке, дата поверки, дата очередной поверки
    QString _type{""};        // Класс прибора (Тип СИ)
    QString _mnom{""};       // Заводской номер
    QString _cls{""};      // Класс точности
    QString _uniq{""};    // Уникальный номер для базы данных, пользователю не показывать :)
};
Q_DECLARE_METATYPE(apparaturs*)
Q_DECLARE_METATYPE(apparaturs)
#endif // APPARATURS_H
