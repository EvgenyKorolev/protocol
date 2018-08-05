#include "my_time_view.h"

my_time_view::my_time_view(bool *arg, QWidget *par) : QTableView(par)
{
    _flag_edit = arg;
    _edited = true;
}
void my_time_view::mousePressEvent(QMouseEvent * arg)
{
   if (_edited){
    if (arg->buttons() == Qt::RightButton){
        QMenu *mnu = new QMenu(this);
        mnu->setEnabled(true);
        QAction *make_str = new QAction(trUtf8("Добавить"), this);
        QObject::connect(make_str, SIGNAL(triggered()), this, SLOT(slot_add()));
        mnu->addAction(make_str);
      if (this->indexAt(arg->pos()).isValid()){
        _curs = arg->pos();
        QAction *del_str = new QAction("Удалить", this);
        QAction *edit_str = new QAction("Изменить", this);
        QObject::connect(del_str, SIGNAL(triggered()), this, SLOT(slot_delete()));
        QObject::connect(edit_str, SIGNAL(triggered()), this, SLOT(slot_edit()));
        mnu->addAction(del_str);
        mnu->addAction(edit_str);
      }
    mnu->popup(arg->globalPos());
    mnu->show();
    }
   }
    QTableView::mousePressEvent(arg);
}
void my_time_view::mouseDoubleClickEvent(QMouseEvent* arg)
{
    this->_curs = arg->pos();
    if (this->indexAt(arg->pos()).isValid()){
          this->slot_edit();
    } else {
        this->slot_add();
    }
    QTableView::mouseDoubleClickEvent(arg);
}
void my_time_view::slot_edit()
{
    QPair<QTime,QTime> tmpp;
    pair_type tmpt;
    tmpt = this->indexAt(_curs).data(Qt::EditRole).value<pair_type>();
    tmpp.first = tmpt.first;
    tmpp.second = tmpt.second;
    QString str1 = "Начало интервала:";
    QString str2 = "Конец интервала:";
    pair_time_editor *pairedit = new pair_time_editor(tmpp, str1, str2);
    if (pairedit->exec() == QDialog::Accepted){
        tmpt.first = pairedit->get_result().first;
        tmpt.second = pairedit->get_result().second;
        model()->setData(this->indexAt(_curs), QVariant::fromValue(tmpt), Qt::EditRole);
        model()->layoutChanged();
       *_flag_edit = true;
    }
    delete pairedit;
}
void my_time_view::slot_delete()
{
    model()->removeRow(this->indexAt(_curs).row(), QModelIndex());
    model()->layoutChanged();
    *_flag_edit = true;
}
void my_time_view::slot_add()
{
    QPair<QTime, QTime> tmpt;
    tmpt.first.setHMS(0, 0, 0);
    tmpt.second.setHMS(0, 0, 0);
    QString str1 = "Начало интервала:";
    QString str2 = "Конец интервала:";
    pair_time_editor *pairedit = new pair_time_editor(tmpt, str1, str2);
    if (pairedit->exec() == QDialog::Accepted){
        int i = model()->rowCount();
        pair_type tmpp;
        tmpp.first = pairedit->get_result().first;
        tmpp.second = pairedit->get_result().second;
        model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(tmpp), Qt::EditRole);
        model()->layoutChanged();
       *_flag_edit = true;
    }
    delete pairedit;
}
void my_time_view::set_edit(bool arg)
{
    _edited = arg;
}
bool my_time_view::is_edit()
{
    return _edited;
}
