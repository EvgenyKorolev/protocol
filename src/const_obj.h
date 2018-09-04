#ifndef CONST_OBJ_H
#define CONST_OBJ_H

#include <QString>
#include <QList>
#include <QDomDocument>
#include <QVariant>
#include <algorithm>
#include <QMessageBox>
#include <utility>

/* Класс для хранение информации о списке константных строк
текста относящихся к одному тимпу протоколоа
1. ОПИСАНИЕ 2. ТЕКСТ 3. ИМЯ ПЕРЕМЕННОЙ */

typedef QList<QPair<QPair<QString, QString>, QString>> listing_type;

class const_obj
{
public:
    const_obj();
    const_obj(const_obj& arg);
    const_obj(const const_obj& arg);
    const_obj(const_obj&& arg);
    const_obj& operator=(const const_obj& arg);
    const_obj& operator=(const_obj&& arg);
    QString get_name() const;
    void set_name(const QString& arg);
    QString get_vname() const;
    void set_vname(const QString& arg);
    void append(QPair<QPair<QString, QString>, QString> arg);
    QPair<QPair<QString, QString>, QString> at(int arg) const;
    void removeAt(int arg);
    void replace(int row, QPair<QPair<QString, QString>, QString> arg);
    listing_type get_data() const;
    QString get_vdata(const QString& vname);
    int count() const;
    QDomElement make_xml();
    void load_xml(QDomElement arg);
private:
    QString name;
    QString var_name;
    listing_type data;
};
#endif // CONST_OBJ_H
