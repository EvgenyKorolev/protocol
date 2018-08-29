#ifndef PAIR_TYPE_H
#define PAIR_TYPE_H
#include <QPair>
#include <QTime>
#include <QList>
#include <QString>
#include <tuple>
typedef QPair<QTime, QTime> pair_type;
typedef QPair<QPair<QString, QString>, QString> pair_list_type;
typedef std::tuple<QString, QString, QString, int> tuple_type;
typedef std::tuple<QString, QString, QString, QString, int> tuple_type_s;
typedef std::tuple<QString, QString, QString> tuple_qss3;
typedef std::tuple<QString, QString, QString, QString> tuple_qss4;
typedef std::tuple<QString, QString, QString, QString, QString> tuple_qss5;
Q_DECLARE_METATYPE(pair_type);
Q_DECLARE_METATYPE(pair_list_type);
Q_DECLARE_METATYPE(tuple_type);
Q_DECLARE_METATYPE(tuple_type_s);
Q_DECLARE_METATYPE(tuple_qss3);
Q_DECLARE_METATYPE(tuple_qss4);
Q_DECLARE_METATYPE(tuple_qss5);
#endif // PAIR_TYPE_H
