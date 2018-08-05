#include "p_tyo_select_view.h"

p_tyo_select_view::p_tyo_select_view(QWidget *par)  : QTableView(par){}
void p_tyo_select_view::mousePressEvent(QMouseEvent * arg)
{

}

void p_tyo_select_view::mouseDoubleClickEvent(QMouseEvent* arg)
{

}

std::tuple<QString, QString, QString> p_tyo_select_view::result()
{

}
void p_tyo_select_view::slot_select()
{
   //ret = model()->data(this->indexAt(curs), Qt::EditRole).value<tuple_qss>();
}
