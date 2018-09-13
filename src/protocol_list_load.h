#ifndef PROTOCOL_LIST_LOAD_H
#define PROTOCOL_LIST_LOAD_H
#include "protocol.h"
#include <QList>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDateTime>
#include <random>
#include <memory>

class protocol;
namespace prt_fun {
    QList<protocol*> loap_p_list(const QString& path);
    QList<protocol*> loap_prot(const QString& path, const QString& uin);
    QString add_prt(const QString& path, const protocol& prt, const QString &prttxt, const QString &endtxt);
    bool save_p_list(const QString& path, const QList<protocol*>& arg);
    bool create_base(const QString& path, const QString& name);
    QString create_uin();

    QString get_prt_text(QSqlDatabase& db, const QString& uin);
    QString get_end_text(QSqlDatabase& db, const QString& uin);
    bool set_prt_text(QSqlDatabase& db, const QString& uin, const QString& text);
    bool set_end_text(QSqlDatabase& db, const QString& uin, const QString& text);
    // Вспомогательные функции
    QString add_prt_l(QSqlDatabase& db, const protocol& prt, const QString &prttxt, const QString &endtxt);
    QString get_prt_l(QSqlDatabase& db, const QString& uin, const QString& arg);
    bool set_prt_l(QSqlDatabase& db, const QString& uin, const QString& text, const QString& arg);
}
#endif // PROTOCOL_LIST_LOAD_H
