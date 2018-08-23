#ifndef TYPE_OBJ_H
#define TYPE_OBJ_H

#include <QString>
#include <QList>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDomDocument>
#include <tuple>
#include <utility>
#include <algorithm>

// Это объект представляющий их себя имя типа и список переменных к нему относящихся
enum class id_type{digit, string, boolean};
// имя переменной, описание, значение, тип переменной
using lst_type = QList<std::tuple<QString, QString, QString, QString>>;

class type_obj
{
public:
    type_obj();
    type_obj(const type_obj& arg);
    type_obj(type_obj&& arg);
    type_obj& operator=(type_obj& arg);
    type_obj& operator=(type_obj&& arg);
    QString get_name() const;
    void set_name(const QString& arg);
    QString get_vname() const;
    void set_vname(const QString& arg);
    QString get_description() const;
    void set_description(const QString& arg);
    QString get_cls() const;
    void set_cls(const QString& arg);
    void append(std::tuple<QString, QString, QString, QString> arg);
    std::tuple<QString, QString, QString, QString> at(int arg) const;
    QString get_vdata(const QString &key);
    void removeAt(int arg);
    void replace(int row, std::tuple<QString, QString, QString, QString> arg);
    lst_type get_data() const;
    int count() const;
    QDomElement make_xml();
    void load_xml(QDomElement arg);
private:
    QString name{""};
    QString var_name{""};
    QString description{""};
    QString cls{""}; // класс типа. (Несколько типов могут быть одного класса, таким образом реализованна их взаимозаменяемость при поимске переменной)
    lst_type data;
};

#endif // TYPE_OBJ_H
