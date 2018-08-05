#ifndef TYPE_CONST_LOADER_H
#define TYPE_CONST_LOADER_H

#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QMessageBox>
#include <algorithm>
#include "type_obj.h"

/* Этот класс - одиночка читает список переменных из файла,
 хранит их и выдаёт для устаноки в модель и иных нужд а так же умеет сохранять */
class type_const_loader
{
private:
    type_const_loader();
    type_const_loader(const type_const_loader&);
    type_const_loader& operator=(type_const_loader&);
public:
    static type_const_loader& getInstance(){
        static type_const_loader instance;
        return instance;
    }
    void save();
    QList<QString> get_id_list() const;
    QList<QString> get_var_list() const;
    type_obj get_obj(const QString &key) const;
    bool add_obj(type_obj& arg);
    bool change_obj(type_obj& arg, QString key);
    bool del_type(const QString& key);
private:
    QList<type_obj*> data_list;
};

#endif // TYPE_CONST_LOADER_H
