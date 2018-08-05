#ifndef P_TYO_SELECT_VIEW_H
#define P_TYO_SELECT_VIEW_H

#include <QObject>
#include <QObject>
#include <QWidget>
#include <QAbstractItemView>
#include <QTableView>
#include <QMouseEvent>
#include <QMenu>
#include <QVariant>
#include <QString>
#include <QPoint>
#include <tuple>
#include "ppair_type.h"
// Вид для отображения и выбора типов констант для протокола
class p_tyo_select_view : public QTableView
{
public:
    p_tyo_select_view(QWidget *par = nullptr);
    void mousePressEvent(QMouseEvent * arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
    std::tuple<QString, QString, QString> result();
public slots:
    void slot_select();
private:
    std::tuple<QString, QString, QString> ret{std::make_tuple("", "", "")};
    QPoint curs;
};

#endif // P_TYO_SELECT_VIEW_H
