#ifndef PPAIR_TYPE_H
#define PPAIR_TYPE_H
#include <QPair>
#include <QString>
#include <QDate>
typedef QPair<QPair<QString, QDate>, QDate> ppair_type;
Q_DECLARE_METATYPE(ppair_type);
#endif // PPAIR_TYPE_H
