#include "directory_app.h"

directory_app::directory_app()
{
    settings& tmps = settings::GetInstance();
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(tmps.get_data_patch() + tmps.get_data_dir() + "/data.db3");
    if (!_db.open()){
    QMessageBox::information(nullptr, "Отладка", "Не открывается справочник приборов");
    } else {
        fab_app tmp_fap;
        QSqlQuery app_query(_db);
        QSqlQuery ver_query(_db);
        if (!app_query.exec("SELECT * FROM app;")) {
            this->create_db();
            }
        QSqlRecord rec_1 = app_query.record();
        QSqlRecord rec_2;
        QList<QPair<QPair<QString, QDate>, QDate>> tmp_vlist;
        QPair<QPair<QString, QDate>, QDate> tmp_ver;
        QDateTime tmp_dat;
        while (app_query.next()){
            apparaturs* tmp = tmp_fap.create_app();
            tmp->set_clas(app_query.value(rec_1.indexOf("cls")).toString());
            tmp->set_type(app_query.value(rec_1.indexOf("type")).toString());
            tmp_dat.setMSecsSinceEpoch(app_query.value(rec_1.indexOf("mdata")).value<qint64>());
            tmp->set_mdata(tmp_dat.date());
            tmp->set_mnom(app_query.value(rec_1.indexOf("mnom")).toString());
            tmp->set_name(app_query.value(rec_1.indexOf("name")).toString());
            tmp->set_uniq(app_query.value(rec_1.indexOf("pr_in")).toString());
            if (!ver_query.exec("SELECT * FROM ver WHERE pr_in = '" + tmp->get_uniq() + "';")){
                QMessageBox::information(nullptr, "Отладка", "Проблема со обращением к справочнику приборов, таблица поверки");
            }
            rec_2 = ver_query.record();
            while (ver_query.next()) {
                tmp_ver.first.first = ver_query.value(rec_2.indexOf("vernom")).toString();
                tmp_dat.setMSecsSinceEpoch(ver_query.value(rec_2.indexOf("date")).value<qint64>());
                tmp_ver.first.second = tmp_dat.date();
                tmp_dat.setMSecsSinceEpoch(ver_query.value(rec_2.indexOf("nextdate")).value<qint64>());
                tmp_ver.second = tmp_dat.date();
                tmp_vlist.append(tmp_ver);
            }
            tmp->set_verification_list(&tmp_vlist);
            _data.append(tmp);
            tmp_vlist.clear();
        }
    }
}
directory_app::~directory_app()
{
    _db.close();
}
void directory_app::append(apparaturs arg)
{
    QDateTime date_tmp(arg.get_mdata());
    QDateTime date_tmp2;
    QSqlQuery add_app_query(_db);
    QSqlQuery add_ver_query(_db);
    if (this->is_made_num(arg.get_mnom())){
        QMessageBox::information(nullptr, "Отладка", "Прибор с таким заводским номером уже существует");
        return;
    }
     if (add_app_query.exec("INSERT INTO app(name, mdata, type, mnom, cls) VALUES ('" +
                                       arg.get_name() + "', '" + QString::number(date_tmp.toMSecsSinceEpoch()) + "', '" +
                                       arg.get_type() + "', '" +
                                       arg.get_mnom() + "', '" + arg.get_clas() + "');")){
         QString tmp_id = this->get_inq_for_mnom(arg.get_mnom());
         if (tmp_id == "0"){ return; }
         arg.set_uniq(tmp_id);
         QList<QPair<QPair<QString, QDate>, QDate>> tmp_vlist = arg.get_verification_list();
         QList<QPair<QPair<QString, QDate>, QDate>>::iterator it = tmp_vlist.begin();
         QString ver_prep;
         while (it != tmp_vlist.end()){
             date_tmp.setDate((*it).first.second);
             date_tmp2.setDate((*it).second);
             ver_prep = "INSERT INTO ver(vernom, date, nextdate, mnom, pr_in) VALUES('" + (*it).first.first + "', '" +
                     QString::number(date_tmp.toMSecsSinceEpoch()) + "', '" +
                     QString::number(date_tmp2.toMSecsSinceEpoch()) + "', '" + arg.get_mnom() + "', '" + tmp_id  + "');";
             if (!add_ver_query.exec(ver_prep)){
                  QMessageBox::information(nullptr, "Отладка", "Что-то пошло не так при добавлении записи о поверки (при добавлении прибора)");
             }
             ++it;
         }
          fab_app tmp_fap;
          apparaturs* tmp = tmp_fap.create_app();
          tmp->init(&arg);
         _data.append(tmp);
      } else {
         QMessageBox::information(nullptr, "Отладка", "Что-то пошло совсем не так при добавлении записи о приборе");
     }
}
void directory_app::replace(int row, apparaturs arg)
{
    QDateTime date_tmp(arg.get_mdata());
    QDateTime date_tmp2;
    QSqlQuery tmp_query(_db);
    QSqlQuery add_app_query(_db);
    QSqlQuery add_ver_query(_db);
    QString old_mnom = _data.at(row)->get_mnom();
    QString app_prep = "UPDATE app SET name = '" + arg.get_name() + "', mdata = '" +
            QString::number(date_tmp.toMSecsSinceEpoch()) + "', type = '" + arg.get_type() + "', mnom = '" +
            arg.get_mnom() + "', cls = '" + arg.get_clas() + "' WHERE mnom ='" + old_mnom + "';" ;
    if (add_app_query.exec(app_prep)){
        QList<QPair<QPair<QString, QDate>, QDate>> tmp_vlist = arg.get_verification_list();
        QList<QPair<QPair<QString, QDate>, QDate>>::iterator it = tmp_vlist.begin();
        QString ver_prep = "DELETE FROM ver WHERE pr_in = '" + arg.get_uniq() + "';"; // Просто удалим нафиг все записи о поверки и запишем те, что есть в переданном объекте. Нерационально с виду, затьо сильно проще чем следить за изменениями :)
        if(!tmp_query.exec(ver_prep)) {
            QMessageBox::information(nullptr, "Отладка", "Что-то пошло не так при удалении записи о поверке");
        }
        while (it != tmp_vlist.end()){
            date_tmp.setDate((*it).first.second);
            date_tmp2.setDate((*it).second);
            ver_prep = "INSERT INTO ver(vernom, date, nextdate, mnom, pr_in) VALUES('" + (*it).first.first + "', '" +
                    QString::number(date_tmp.toMSecsSinceEpoch()) + "', '" +
                    QString::number(date_tmp2.toMSecsSinceEpoch()) + "', '" +
                    arg.get_mnom() + "', '" + arg.get_uniq() + "');";
              if (!add_ver_query.exec(ver_prep)){
                     QMessageBox::information(nullptr, "Отладка", "Что-то пошло не так при добовлении записи о поверке");
             }
            ++it;
        }
        fab_app tmp_fap;
        apparaturs* tmp = tmp_fap.create_app();
        tmp->init(&arg);
        _data.replace(row, tmp);
    } else {
        QMessageBox::information(nullptr, "Отладка", "Что-то пошло совсем не так при обновлении записи о приборе");
    }
}
apparaturs directory_app::search_made_num(QString arg) const
{
    QSqlQuery app_query(_db);
    QSqlQuery ver_query(_db);
    QDateTime tmp_dat;
    if (app_query.exec("SELECT * FROM app WHERE mnom = '" + arg + "';")) {
        QSqlRecord rec_1 = app_query.record();
        QSqlRecord rec_2;
        QList<QPair<QPair<QString, QDate>, QDate>> tmp_vlist;
        QPair<QPair<QString, QDate>, QDate> tmp_ver;
        app_query.first();
        apparaturs tmp;
        tmp.set_clas(app_query.value(rec_1.indexOf("cls")).toString());
        tmp.set_type(app_query.value(rec_1.indexOf("type")).toString());
        tmp_dat.setMSecsSinceEpoch(app_query.value(rec_1.indexOf("mdata")).value<qint64>());
        tmp.set_mdata(tmp_dat.date());
        tmp.set_mnom(app_query.value(rec_1.indexOf("mnom")).toString());
        tmp.set_name(app_query.value(rec_1.indexOf("name")).toString());
        tmp.set_uniq(app_query.value(rec_1.indexOf("pr_in")).toString());
        if (!ver_query.exec("SELECT * FROM ver WHERE pr_in = '" + tmp.get_uniq() + "';")){
            QMessageBox::information(nullptr, "Отладка", "Проблема со обращением к справочнику приборов, таблица поверки");
        }
        rec_2 = ver_query.record();
        while (ver_query.next()) {
            tmp_ver.first.first = ver_query.value(rec_2.indexOf("vernom")).toString();
            tmp_dat.setMSecsSinceEpoch(ver_query.value(rec_2.indexOf("date")).value<qint64>());
            tmp_ver.first.second = tmp_dat.date();
            tmp_dat.setMSecsSinceEpoch(ver_query.value(rec_2.indexOf("nextdate")).value<qint64>());
            tmp_ver.second = tmp_dat.date();
            tmp_vlist.append(tmp_ver);
        }
        tmp.set_verification_list(&tmp_vlist);
        return tmp;
        }
    return apparaturs();
}
QString directory_app::get_inq_for_mnom(const QString arg) const
{
    QSqlQuery app_query(_db);
    if (app_query.exec("SELECT * FROM app WHERE mnom = '" + arg + "';")) {
        QSqlRecord rec_1 = app_query.record();
        app_query.first();
        return app_query.value(rec_1.indexOf("pr_in")).toString();
        }
    return "0";
}
bool directory_app::is_made_num(const QString& arg) const
{
        QSqlQuery app_query(_db);
        if (app_query.exec("SELECT * FROM app WHERE mnom = '" + arg + "';")) {
            if (app_query.first()){return true;}
            return false;
            }
        return false;
}
int directory_app::count()
{
    return _data.count();
}
QList<apparaturs *> directory_app::ret_app_list() const
{
   return _data;
}
void directory_app::removeAt(int row)
{
    QSqlQuery rem_query(_db);
    QString rem_prep;
    QString mun = _data.at(row)->get_uniq();
    rem_prep = "DELETE FROM app WHERE pr_in = '" + mun + "';";
    if (!rem_query.exec(rem_prep)) {
        QMessageBox::information(nullptr, "Отладка", "Что-то пошло совсем не так при удалении записи о приборе");
    } else {
        _data.removeAt(row);
        rem_prep = "DELETE FROM ver WHERE pr_in = '" + mun + "';";
        if (!rem_query.exec(rem_prep)){
            QMessageBox::information(nullptr, "Отладка", "Что-то пошло совсем не так при удалении записи о поверке");
        }
    }
}
apparaturs directory_app::at(int row)
{
    return *(_data.at(row));
}
int directory_app::is_row(const QString arg) const
{
    QList<apparaturs*>::const_iterator it = _data.begin();
    int res{0};
    while (it != _data.end()){
        if ((*it)->get_mnom() == arg) return res;
        ++res;
        ++it;
    }
    return res;
}
void directory_app::create_db()
{
    // Добавить создание БД в случае её отсутствия
    QSqlQuery app_query(_db);
    QSqlQuery ver_query(_db);

    if (!app_query.exec("CREATE TABLE app (name TEXT NOT NULL, mdata INTEGER, type TEXT, mnom TEXT NOT NULL UNIQUE, cls TEXT, pr_in INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL);")){
        QMessageBox::information(nullptr, "Отладка", "Проблема со обращением к справочнику приборов");
    }
    if (!ver_query.exec("CREATE TABLE ver (vernom TEXT UNIQUE NOT NULL, date INTEGER, nextdate INTEGER, mnom TEXT NOT NULL, pr_in INTEGER NOT NULL DEFAULT (0));")){
        QMessageBox::information(nullptr, "Отладка", "Проблема со обращением к справочнику приборов");
    }
}
