#include "protocol_list_load.h"

QList<protocol*> prt_fun::loap_p_list(const QString& path)
{
    QList<protocol*> ret = QList<protocol*>();
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", "SecondDB");
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
            tmpp->set_prttxt(prt_query.value(rec.indexOf("prt_text")).toString());
            tmpp->set_endtxt(prt_query.value(rec.indexOf("end_text")).toString());
            tmpp->set_type(prt_query.value(rec.indexOf("prt_type")).toString());
            ret.append(tmpp);
        }
    }
    db.close();
    return ret;
}
std::unique_ptr<protocol> loap_prot(const QString& path, const QString& uin)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", "SecondDB");
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
    ret->set_prttxt(prt_query.value(rec.indexOf("prt_text")).toString());
    ret->set_endtxt(prt_query.value(rec.indexOf("end_text")).toString());
    ret->set_type(prt_query.value(rec.indexOf("prt_type")).toString());
    db.close();
    return ret;
}
QString prt_fun::add_prt(const QString& path, const protocol& prt)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", "SecondDB");
    db.setDatabaseName(path);
    if (!db.open()){
        QMessageBox::information(nullptr, "Отладка", "Не открывается база протоколов клиента: <br>"
                                 + path + "<br> Будет создан пустой файл протоколов");
        prt_fun::create_base(path.right(path.size() - path.lastIndexOf("/") - 1),
                             path.left(path.size() - path.lastIndexOf("/")));
    }
    QSqlQuery prt_query(db);
    QString query_str{""};
    if (!prt_query.exec("SELECT * FROM prot WHERE uin = '" + prt.get_uin() + "';")) {
        query_str = "INSERT INTO prot(uin, prt_text, end_text, prt_type) VALUES('" + prt.get_uin() + "', '" +
                prt.get_prttxt() + "', '" + prt.get_endtxt() + "', '" + prt.get_type() + "');";
        if (!prt_query.exec(query_str)){
            QMessageBox::information(nullptr, "Отладка", "Не получается добавить протокол");
        }
    } else {
        query_str = "UPDATE prot SET prt_text = '" + prt.get_prttxt() + "', end_text = '" +
                    prt.get_endtxt() + "', prt_type = '" + prt.get_type() + "' WHERE uin ='" + prt.get_uin() + "';";
        if (!prt_query.exec(query_str)){
            QMessageBox::information(nullptr, "Отладка", "Не получается обновить протокол");
        }
    }
    db.close();
    return prt.get_uin();
}
bool prt_fun::save_p_list(const QList<protocol*>& arg)
{
    for (auto it : arg)
    return false;
}
    bool prt_fun::create_base(const QString& path, const QString& name)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", "SecondDB");
    db.setDatabaseName(path + "/" + name);
    if (!db.open()){
        QMessageBox::information(nullptr, "Отладка", "Не открывается база протоколов клиента");
        return false;
    }
    QSqlQuery prt_query(db);
    if (prt_query.exec("SELECT * FROM prot;")) {
        return true;
    }

    if (!prt_query.exec("CREATE TABLE prot (uin TEXT UNIQUE NOT NULL, prt_text TEXT, end_text TEXT, prt_type TEXT, id_ INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL);")){
        QMessageBox::information(nullptr, "Отладка", "Проблема со обращением к базе протоколов клиента");
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
QString prt_fun::getnum()
{
    static unsigned int nm{0};
    return QString::number(nm++);
}
