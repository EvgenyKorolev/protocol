#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "my_function.h"
#include "protocol_list_load.h"
#include <QVariant>
#include <QDomDocument>
#include <QDate>
#include <memory>
//#include "obj.h"

class obj;
// Этот класс хранения готовых протоколов
class protocol
{
public:
    protocol(obj* par);
    protocol(const QString& uin);
    protocol(QDomNode *arg);
    ~protocol();
    protocol(protocol& prt);
    protocol(protocol* prt);
    protocol(protocol&& prt);
    protocol& operator=(protocol& prt);
    protocol&& operator=(protocol&& prt);
    void set_parent(obj* par);
    obj* get_parent() const;
    void set_number(const QString& arg);
    void set_date(const QDate& arg);
    void set_type(const QString& arg);
    void set_prttxt(const QString& arg);
    void set_endtxt(const QString& arg);
    void set_dr(const QString& arg);
    void set_file(const QString& arg);
    void set_uin(const QString& arg);
    QString get_number() const;
    QDate get_date() const;
    QString get_type() const;
    QString get_prttxt() const;
    QString get_endtxt() const;
    QString get_dr() const;
    QString get_file() const;
    QString get_uin() const;
    bool set_data(const protocol& arg); /* Устанавливает: Номер протокола
            **Дата протокола Тип протокола
            **Название файла хранящего базу с протоколом
            ***Путь к папке в которой лежит файл с протоколами
            ** Копирует значения prttxt и  endtxt в базу под новым uin
            ** Родительский объект должен быть на момент вызова метода уже задан. */
    QString ret_srctxt() const;  // Возвращает текст протокола как есть
    QString ret_endtxt() const;  // Возвращает текст протокола с выполненными скриптами

    bool erase();   // Удаляет запись протокола из базы данных. Её надо вызывать перед полным удаления протокола.

    QDomElement make_xml() const;
    int load_xml(QDomNode *arg);
private:
    obj* parent = nullptr;
    QString prt_number{""};  // Номер протокола
    QDate prt_date{0, 0, 0};  // Дата протокола
    QString prt_type{""};  // Тип протокола
    QString file{""};  // Название файла хранящего базу с протоколом
    QString dr{""}; // Путь к папке в которой лежит файл с протоколами
    QString uin{""}; // Уникальный в масштабах клиента (но если формировать его с помошью prt_fun::create_uin() то колизии
                        // и у разных клиентов будут редки) номер (для хранения)
};
Q_DECLARE_METATYPE(protocol*)
#endif // PROTOCOL_H
