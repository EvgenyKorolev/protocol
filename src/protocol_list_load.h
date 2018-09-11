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
namespace prt_fun {
    QList<protocol*> loap_p_list(const QString& path);
    QString add_prt(const QString& path, const protocol& prt);
    bool save_p_list(const QList<protocol*>& arg);
    bool create_base(const QString& path, const QString& name);
    QString create_uin();
}
#endif // PROTOCOL_LIST_LOAD_H
