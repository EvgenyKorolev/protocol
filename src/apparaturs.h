#ifndef APPARATURS_H
#define APPARATURS_H

#include <QString>
#include <QPair>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>
#include <QDate>
#include <QVariant>
#include "my_function.h"

// Это базовый класс для всех приборов

class apparaturs
{
public:
    apparaturs();
    apparaturs(apparaturs *arg);
    apparaturs(const apparaturs& arg);

    virtual void init(apparaturs *arg);

    virtual int set_name(QString *arg); // Установить имя
    virtual int set_name(QString arg);  // Установить имя (перегруженная)
    virtual QString get_name() const;         // Узнать имя
    virtual int set_mdata(QDate *arg);  // Установить дату выпуска прибора
    virtual int set_mdata(QDate arg);   // Установить дату выпуска прибора (перегруженная)
    virtual QDate get_mdata() const;          // Узнать дату выпуска прибора
    virtual QDate get_real_ver();     // Узнать дату последней поверки

    virtual int add_verification(QPair<QPair<QString, QDate>, QDate> *arg);             // Добавить в список дат и номеров свидетельств поверки значение
    virtual int set_verification_list(QList<QPair<QPair<QString, QDate>, QDate>>* arg); // Установить список дат и номеров свидетельств поверки
    virtual  QList<QPair<QPair<QString, QDate>, QDate>> get_verification_list() const;        // Возвращает список дат и номеров свидетельств поверки
    virtual int clear_verification();                                                   // Очищает список дат и номеров свидетельств поверки

    virtual int set_type(QString *arg);  // Установить класс СИ
    virtual int set_type(QString arg);   // Установить класс СИ (перегруженная)
    virtual QString get_type() const;          // Узнать класс СИ
    virtual int set_mnom(QString *arg); // Установить заводской номер
    virtual int set_mnom(QString arg);  // Установить заводской номер (перегруженная)
    virtual QString get_mnom() const;         // Узнать заводской номер
    virtual QString get_clas() const;         // Узнать класс точности
    virtual void set_clas(QString arg);  // Установить класс точности

    virtual void load_xml(QDomNode *my_dom);
    virtual QDomElement make_xml();
    virtual int load_xml_1(QDomNode *my_dom);
    virtual QDomElement make_xml_1();
    virtual int load_db_1();
    virtual int save_db_1();
    void set_uniq(QString arg);
    QString get_uniq() const;

protected:
    QString _name;       // Название прибора
    QDate _mdata;        // Дата... чего-то там, пока непонятно (выпуска наверное)
    QList<QPair<QPair<QString, QDate>, QDate>> _verification;   // Номер свидетельства о поверке, дата поверки, дата очередной поверки
    QString _type;        // Класс прибора (Тип СИ)
    QString _mnom;       // Заводской номер
    QString _cls;      // Класс точности
    QString _uniq;    // Уникальный номер для базы данных, пользователю не показывать :)
};
Q_DECLARE_METATYPE(apparaturs*)
Q_DECLARE_METATYPE(apparaturs)
#endif // APPARATURS_H
