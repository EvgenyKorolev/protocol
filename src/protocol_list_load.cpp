#include "protocol_list_load.h"

QList<protocol*> prt_fun::loap_p_list(const QString& path)
{
    QList<protocol*> ret = QList<protocol*>();
}
QString prt_fun::add_prt(const QString& path, const protocol& prt)
{

}
bool prt_fun::save_p_list(const QList<protocol*>& arg)
{

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

    if (!prt_query.exec("CREATE TABLE prot (uin TEXT NOT NULL, prt_text TEXT, end_text TEXT, prt_type TEXT, id_ INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL);")){
        QMessageBox::information(nullptr, "Отладка", "Проблема со обращением к базе протоколов клиента");
        return false;
    }
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
