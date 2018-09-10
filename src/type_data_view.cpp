#include "type_data_view.h"

type_data_view::type_data_view(QSortFilterProxyModel *arg, QWidget *par) : QTableView (par)
{
    pat_mod = arg;
}
void type_data_view::mousePressEvent(QMouseEvent * arg)
{
    if (arg->buttons() == Qt::RightButton) {
        QMenu *mnu = new QMenu(this);
        mnu->setEnabled(true);
        QAction *make_app = new QAction(trUtf8("Добавить"), this);
        QObject::connect(make_app, SIGNAL(triggered()), this, SLOT(slot_add()));
        mnu->addAction(make_app);
      if (this->indexAt(arg->pos()).isValid()){
        _curs = arg->pos();
        QAction *del_app = new QAction("Удалить", this);
        QAction *edit_app = new QAction("Изменить", this);
        QObject::connect(del_app, SIGNAL(triggered()), this, SLOT(slot_delete()));
        QObject::connect(edit_app, SIGNAL(triggered()), this, SLOT(slot_edit()));
        mnu->addAction(del_app);
        mnu->addAction(edit_app);
      }
    mnu->popup(arg->globalPos());
    mnu->show();
    }
    QTableView::mousePressEvent(arg);
}
void type_data_view::mouseDoubleClickEvent(QMouseEvent* arg)
{
    this->_curs = arg->pos();
    if (this->indexAt(arg->pos()).isValid()){
          this->slot_edit();
    } else {
        this->slot_add();
    }
    QTableView::mouseDoubleClickEvent(arg);
}
void type_data_view::slot_edit()
{
    tuple_type_s tmp_tup;
    tmp_tup = this->indexAt(_curs).data(Qt::EditRole).value<tuple_type_s>();
    std::tuple<QString, QString, QString, QString> tmp_tupl{std::get<0>(tmp_tup), std::get<1>(tmp_tup), std::get<2>(tmp_tup), std::get<3>(tmp_tup)};
    type_data_editor* cedit = new type_data_editor(tmp_tupl);
    int n{std::get<4>(tmp_tup)};
    if (cedit->exec() == QDialog::Accepted){
        tmp_tupl = cedit->result();
        tmp_tup = std::make_tuple(std::get<0>(tmp_tupl), std::get<1>(tmp_tupl), std::get<2>(tmp_tupl), std::get<3>(tmp_tupl), n);
        model()->setData(this->indexAt(_curs), QVariant::fromValue(tmp_tup), Qt::EditRole);
        model()->layoutChanged();
        pat_mod->invalidate();
    }
    delete cedit;
}
void type_data_view::slot_delete()
{
    emit signal_new();
    model()->removeRow(this->indexAt(_curs).row(),QModelIndex());
    model()->layoutChanged();
    emit signal_new();
}
void type_data_view::slot_add()
{
    std::tuple<QString, QString, QString, QString> tmp_tupl{};
    type_data_editor* cedit = new type_data_editor(tmp_tupl);
    if (cedit->exec() == QDialog::Accepted){
        tmp_tupl = cedit->result();
        tuple_type_s tmp_tup{std::get<0>(tmp_tupl), std::get<1>(tmp_tupl), std::get<2>(tmp_tupl), std::get<3>(tmp_tupl), model()->rowCount()};
        int i{model()->rowCount()};
        model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(tmp_tup), Qt::EditRole);
        model()->layoutChanged();
        pat_mod->invalidate();
    }
    delete cedit;
    emit signal_new();
}
