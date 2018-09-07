#ifndef CONST_LOADER_H
#define CONST_LOADER_H

#include "settings.h"
#include <QList>
#include <QString>
#include <QPair>
#include <QFile>
#include <QDomDocument>
#include <QMessageBox>
#include <QTextStream>
#include "const_obj.h"
#include <algorithm>
/* Этот класс - одиночка читает список констант (текстов) из файла,
 хранит их и выдаёт для устаноки в модель и иных нужд а так же умеет сохранять*/
class const_loader
{
private:
    const_loader();
    const_loader(const const_loader&);
    const_loader& operator=(const_loader&);
public:
    static const_loader& getInstance(){
        static const_loader instance;
        return instance;
    }
  void save();
  QList<QString> get_id_list() const;
  QList<QString> get_var_list() const;
  QList<QPair<QString, QString> > get_idv_list() const; // Возвращает список пар 1. имя типа 2. имя переменной
  const_obj get_obj(const QString &key) const;
  bool add_obj(const_obj& arg);
  bool change_obj(const_obj& arg, QString key);
  bool del_obj(const QString& key);
private:
    QList<const_obj*> data_list;
};

#endif // CONST_LOADER_H
