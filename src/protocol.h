#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "my_function.h"
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
    protocol(obj* par, const QString& arg);
    ~protocol() = default;
    protocol(protocol& prt);
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
    QString get_number() const;
    QDate get_date() const;
    QString get_type() const;
    QString get_prttxt() const;
    QString get_endtxt() const;
    QString get_dr() const;

    QString ret_srctxt() const;  // Возвращает текст протокола как есть
    QString ret_endtxt() const;  // Возвращает текст протокола с выполненными скриптами

    QDomElement make_xml() const;
    int load_xml(QDomDocument *arg);
private:
    obj* parent;
    QString prt_number{""};  // Номер протокола
    QDate prt_date{0, 0, 0};  // Дата протокола
    QString prt_type{""};  // Тип протокола
    QString prt_text{""};  // Текст протокола (адрес файла в котором он лежит)
    QString end_text{""};  // Текст протокола без скриптов (с результатом их работы) (адрес файла в котором он лежит)
    QString dr{""}; // Путь к папке в которой лежит протокол
};
Q_DECLARE_METATYPE(protocol*)
#endif // PROTOCOL_H
