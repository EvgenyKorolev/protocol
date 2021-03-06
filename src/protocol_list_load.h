#ifndef PROTOCOL_LIST_LOAD_H
#define PROTOCOL_LIST_LOAD_H
#include <QList>
#include <QSqlDatabase>
class klient;
class protocol;
namespace prt_fun {
    QList<protocol*> loap_p_list(const QString& path);
    QList<protocol*> loap_prot(const QString& path, const QString& uin);
    QString add_prt(const QString& path, const protocol& prt, const QString &prttxt, const QString &endtxt);
    bool save_p_list(const QString& path, const QList<protocol*>& arg);
    bool create_base(const QString& path, const QString& name);
    QString update_prt(const QString& path, const protocol& prt, const QString& prttxt, const QString& endtxt);
    bool delete_prt(const QString& pathname, const QString& uin);
    QString create_uin();

    void erase_lost_protocols(klient* arg);
    // Вспомогательные функции

    QString get_prt_text(const QString& path, const QString& uin);
    QString get_end_text(const QString& path, const QString& uin);
    bool set_prt_text(const QString& path, const QString& uin, const QString& text);
    bool set_end_text(const QString& path, const QString& uin, const QString& text);

    QString add_prt_l(const QSqlDatabase& db, const protocol& prt, const QString &prttxt, const QString &endtxt);
    QString get_prt_l(const QString& path, const QString& uin, const QString& arg);
    bool set_prt_l(const QString& path, const QString& uin, const QString& text, const QString& arg);
    QString update_prt_l(const QSqlDatabase& db, const protocol& prt, const QString &prttxt, const QString &endtxt);

    bool del_prt_list(const QString& path, QList<QString> uins);

    QString base64_plus(const QString &arg);
    QString base64_minus(const QString& argx);
}
#endif // PROTOCOL_LIST_LOAD_H
