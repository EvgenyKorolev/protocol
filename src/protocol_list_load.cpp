#include "protocol_list_load.h"
#include "klient.h"
#include "protocol.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>
#include <random>
#include <memory>
#include <algorithm>

QList<protocol*> prt_fun::loap_p_list(const QString& path)
{
    QList<protocol*> ret = QList<protocol*>();
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", prt_fun::create_uin().right(5) + "RSecondDBloap");
    db.setDatabaseName(path);
    if (!db.open()){
        QMessageBox::information(nullptr, "Отладка", "Не открывается база протоколов клиента: <br>"
                                 + path + "<br> Будет создан пустой файл протоколов");
        prt_fun::create_base(path.right(path.size() - path.lastIndexOf("/") - 1),
                             path.left(path.size() - path.lastIndexOf("/")));
    }
    QSqlQuery prt_query(db);
    QSqlRecord rec;
    if (prt_query.exec("SELECT * FROM prot;")) {
        while (prt_query.next()){
            rec = prt_query.record();
            protocol* tmpp = new protocol(prt_query.value(rec.indexOf("uin")).toString());
            tmpp->set_prttxt(prt_fun::base64_minus(prt_query.value(rec.indexOf("prt_text")).toString()));
            tmpp->set_endtxt(prt_fun::base64_minus(prt_query.value(rec.indexOf("end_text")).toString()));
            ret.append(tmpp);
        }
    }
    db.close();
    return ret;
}
std::unique_ptr<protocol> loap_prot(const QString& path, const QString& uin)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", prt_fun::create_uin().right(5) + "TSecondDB_prot");
    db.setDatabaseName(path);
    if (!db.open()){
        QMessageBox::information(nullptr, "Отладка", "Не открывается база протоколов клиента: <br>"
                                 + path + "<br> Будет создан пустой файл протоколов");
        prt_fun::create_base(path.right(path.size() - path.lastIndexOf("/") - 1),
                             path.left(path.size() - path.lastIndexOf("/")));
    }
    QSqlQuery prt_query(db);
    QSqlRecord rec;
    if (!prt_query.exec("SELECT * FROM prot WHERE uin = '" + uin + "';")) {
        QMessageBox::information(nullptr, "Отладка", "Нет такого протокола");
        return std::make_unique<protocol>(new protocol(QString::number(-1)));
    }
    rec = prt_query.record();
    prt_query.first();
    std::unique_ptr<protocol> ret(new protocol(uin));
    ret->set_prttxt(prt_fun::base64_minus(prt_query.value(rec.indexOf("prt_text")).toString()));
    ret->set_endtxt(prt_fun::base64_minus(prt_query.value(rec.indexOf("end_text")).toString()));
    db.close();
    return ret;
}
QString prt_fun::add_prt(const QString& path, const protocol& prt, const QString& prttxt, const QString& endtxt)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", prt_fun::create_uin().right(5) + "FSecondDBadd_prt");
    db.setDatabaseName(path);
    if (!db.open()){
        QMessageBox::information(nullptr, "Отладка", "Не открывается база протоколов клиента: <br>"
                                 + path + "<br> Будет создан пустой файл протоколов");
        prt_fun::create_base(path.right(path.size() - path.lastIndexOf("/") - 1),
                             path.left(path.size() - path.lastIndexOf("/")));
        return "";
    }
    QString ret = prt_fun::add_prt_l(db, prt, prttxt, endtxt);
    db.close();
    return ret;
}
QString prt_fun::add_prt_l(const QSqlDatabase& db, const protocol& prt, const QString &prttxt, const QString &endtxt)
{
    QSqlQuery prt_query(db);
    QString query_str{""};
        query_str = "INSERT INTO prot(uin, prt_text, end_text) VALUES('" + prt.get_uin() + "', '" + prt_fun::base64_plus(prttxt) +
                "', '" + prt_fun::base64_plus(endtxt) + "');";
        if (!prt_query.exec(query_str)){
            QMessageBox::information(nullptr, "Отладка", "Не получается добавить протокол");
            return "";
        }
    return prt.get_uin();
}
QString prt_fun::update_prt(const QString& path, const protocol& prt, const QString& prttxt, const QString& endtxt)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", prt_fun::create_uin().right(5) + "GSecondDBadd_prt");
    db.setDatabaseName(path);
    if (!db.open()){
        QMessageBox::information(nullptr, "Отладка", "Не открывается база протоколов клиента: <br>"
                                 + path + "<br> Будет создан пустой файл протоколов");
        prt_fun::create_base(path.right(path.size() - path.lastIndexOf("/") - 1),
                             path.left(path.size() - path.lastIndexOf("/")));
    }
    QString ret = prt_fun::add_prt_l(db, prt, prttxt, endtxt);
    db.close();
    return ret;
}
QString prt_fun::update_prt_l(const QSqlDatabase& db, const protocol& prt, const QString &prttxt, const QString &endtxt)
{
    QSqlQuery prt_query(db);
    QString query_str{""};
        query_str = "UPDATE prot SET prt_text = '" + prt_fun::base64_plus(prttxt) + "', end_text = '" + prt_fun::base64_plus(endtxt) +
                "' WHERE uin = '" + prt.get_uin() + "';";
        if (!prt_query.exec(query_str)){
            QMessageBox::information(nullptr, "Отладка", "Не получается обновить протокол");
        }
    return prt.get_uin();
}
bool prt_fun::create_base(const QString& path, const QString& name)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", prt_fun::create_uin().right(5) + "HSecondDB_base");
    db.setDatabaseName(path + "/" + name);
    if (!db.open()){
        QMessageBox::information(nullptr, "Отладка", "Не открывается база протоколов клиента");
        return false;
    }
    QSqlQuery prt_query(db);
    if (prt_query.exec("SELECT * FROM prot;")) {
        return true;
    }
    if (!prt_query.exec("CREATE TABLE prot (uin TEXT UNIQUE NOT NULL, prt_text VARCHAR, end_text VARCHAR, id_ INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL);")){
        QMessageBox::information(nullptr, "Отладка", "Проблема со обращением к базе протоколов клиента");
        db.close();
        return false;
    }
    db.close();
return true;
}
QString prt_fun::create_uin()
{
    QString _hash_label = QString();
    _hash_label.append(QString::number(QDateTime::currentSecsSinceEpoch()));
    std::random_device gensc;
    std::mt19937 gen;
    gen.seed(gensc());
    _hash_label.append(QString::number(gen()));
    return  _hash_label;
}
QString prt_fun::get_prt_l(const QString& path, const QString& uin, const QString& arg)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", prt_fun::create_uin().right(5) + "BSecondDB_get_prt_l");
    db.setDatabaseName(path);
    QSqlQuery prt_query(db);
    QSqlRecord rec;
    if (!db.open()){
        QMessageBox::information(nullptr, "Отладка", "Не открывается база протоколов клиента");
        return "";
    }
    if (!prt_query.exec("SELECT * FROM prot WHERE uin = '" + uin + "';")) {
        QMessageBox::information(nullptr, "Отладка", "Нет такого протокола (1)");
        db.close();
        return "";
    }
    rec = prt_query.record();
    prt_query.first();
    QString ret = prt_fun::base64_minus(prt_query.value(rec.indexOf(arg)).toString());
    db.close();
    return ret;
}
bool prt_fun::set_prt_l(const QString &path, const QString& uin, const QString& text, const QString& arg)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", prt_fun::create_uin().right(5) + "CSecondDB_set_prt_l");
    db.setDatabaseName(path);
    if (!db.open()){
        QMessageBox::information(nullptr, "Отладка", "Не открывается база протоколов клиента");
        return false;
    }
    QSqlQuery prt_query(db);
    QSqlRecord rec;
    if (!prt_query.exec("UPDATE prot SET " + arg+  "= '" + prt_fun::base64_plus(text) + "' WHERE uin ='" + uin + "';")) {
        QMessageBox::information(nullptr, "Отладка", "Нет такого протокола (2)");
        db.close();
        return false;
    }
    db.close();
    return true;
}
bool prt_fun::delete_prt(const QString& pathname, const QString& uin)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", prt_fun::create_uin().right(5) + "XSecondDBdelete_prtX");
    db.setDatabaseName(pathname);
    if (!db.open()){
        QMessageBox::information(nullptr, "Отладка", "Не открывается база протоколов клиента");
        return false;
    }
    QSqlQuery prt_query(db);
    if (!prt_query.exec("DELETE FROM prot WHERE uin = '" + uin + "';")) {
        QMessageBox::information(nullptr, "Отладка", "Не могу удалить текст протокола");
        db.close();
        return false;
    }
    db.close();
    return true;
}
bool prt_fun::del_prt_list(const QString& path, QList<QString> uins)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", prt_fun::create_uin().right(5) + "XFSecondDBdeletelist");
    db.setDatabaseName(path);
    if (!db.open()){
        QMessageBox::information(nullptr, "Отладка", "Не открывается база протоколов клиента");
        return false;
    }
    QSqlQuery prt_query(db);
    for (auto it : uins){
        prt_query.exec("DELETE FROM prot WHERE uin = '" + it + "';");
    }
    db.close();
    return true;
}
QString prt_fun::get_prt_text(const QString& path, const QString& uin)
{
    return prt_fun::get_prt_l(path, uin, "prt_text");
}
QString prt_fun::get_end_text(const QString& path, const QString& uin)
{
    return prt_fun::get_prt_l(path, uin, "end_text");
}
bool prt_fun::set_prt_text(const QString& path, const QString& uin, const QString& text)
{
    return prt_fun::set_prt_l(path, uin, text, "prt_text");
}
bool prt_fun::set_end_text(const QString& path, const QString& uin, const QString& text)
{
    return prt_fun::set_prt_l(path, uin, text, "end_text");
}
void prt_fun::erase_lost_protocols(klient* arg)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", prt_fun::create_uin().right(5) + "LSeconderase_lost_protocols");
    db.setDatabaseName(arg->get_patch() + "/" + arg->get_pdirname());
    if (!db.open()){
        QMessageBox::information(nullptr, "Отладка", "Не открывается база протоколов клиента: <br>" + arg->get_patch() + "/" + arg->get_pdirname());
    }
    QSqlQuery prt_query(db);
    QSqlRecord rec;
    if (prt_query.exec("SELECT * FROM prot;")) {
        QList<QString> dirty_list{QList<QString>()};
        QList<QString> klient_list{arg->ret_uids()};
        while (prt_query.next()){
            rec = prt_query.record();
            dirty_list.append(prt_query.value(rec.indexOf("uin")).toString());
        }
        dirty_list.sort();
        klient_list.sort();
        std::list<QString> result_list{std::list<QString>()};
        std::set_difference(dirty_list.begin(), dirty_list.end(), klient_list.begin(), klient_list.end(), std::insert_iterator<std::list<QString>>(result_list, result_list.begin()));
        if (result_list.size() > 0){
            for (auto itz : result_list){
                prt_fun::delete_prt(arg->get_patch() + "/" + arg->get_pdirname(), itz);
            }
        }
    }
    db.close();
}
QString prt_fun::base64_plus(const QString& arg)
{
    QString ret{""};
    QByteArray retar;
    retar.append(arg);
    retar = retar.toBase64();
    ret = retar;
    return ret;
}
QString prt_fun::base64_minus(const QString& argx)
{
    QByteArray retar;
    QByteArray retar2;
    retar2.append(argx);
    retar = QByteArray::fromBase64(retar2);
    QString arg(retar);
    return arg;
}
