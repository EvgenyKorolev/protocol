#ifndef DIRECTORY_APP_H
#define DIRECTORY_APP_H

#include "settings.h"
#include "apparaturs.h"
#include "fab_app.h"
#include <QList>
#include <QString>
#include <QSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>
#include <QDateTime>
#include <QPair>
#include <memory>

class directory_app
{
private:
    directory_app();
    directory_app(const directory_app&);
    directory_app& operator=(directory_app&);
    ~directory_app();
    void create_db();
public:
    static directory_app& getInstance(){
        static directory_app instance;
        return instance;
    }
    void append(apparaturs arg);
    apparaturs search_made_num(QString arg) const;
    int count();
    void replace(int row, apparaturs arg);
    QList<apparaturs *> ret_app_list() const;
    void removeAt(int row);
    apparaturs at(int row);
    bool is_made_num(const QString& arg) const;
    QString get_inq_for_mnom(const QString arg) const;
    int is_row(const QString arg) const;
private:
    QSqlDatabase _db;
    QList<apparaturs*> _data;
};

#endif // DIRECTORY_APP_H
