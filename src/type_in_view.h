#ifndef TYPE_IN_VIEW_H
#define TYPE_IN_VIEW_H

#include <QObject>
#include <QMouseEvent>
#include <QMenu>
#include <QTableView>
#include <QVariant>
#include <QString>
#include <tuple>
#include "type_in_direct.h"
#include "pair_type.h"
// Класс представления для выбора типа набора констант из общего списка
class type_in_direct;
class type_in_view : public QTableView
{
    Q_OBJECT
public:
    type_in_view(QWidget *par = nullptr);
    void mousePressEvent(QMouseEvent * arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
    void set_pather(type_in_direct* arg);
    std::tuple<QString, QString, QString> result();
public slots:
    void slot_return(); // Возвращает выбранный прибор и закрывается
private:
    QPoint curs;
    type_in_direct* pather;
    std::tuple<QString, QString, QString> ret;
};

#endif // TYPE_IN_VIEW_H
