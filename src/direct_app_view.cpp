#include "direct_app_view.h"

direct_app_view::direct_app_view(QWidget *par) : QTableView(par)
{
    _pather = nullptr;
}
void direct_app_view::mousePressEvent(QMouseEvent* arg)
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
void direct_app_view::mouseDoubleClickEvent(QMouseEvent* arg)
{
    this->_curs = arg->pos();
    if (this->indexAt(arg->pos()).isValid()){
          this->slot_edit();
    } else {
        this->slot_add();
    }
    QTableView::mouseDoubleClickEvent(arg);
}
void direct_app_view::slot_edit()
{
    apparaturs tmpap;
    tmpap = this->indexAt(_curs).data(Qt::EditRole).value<apparaturs>();
    app_editor *appedit = new app_editor(&tmpap, true);
    if (appedit->exec() == QDialog::Accepted){
        tmpap = appedit->result();
        model()->setData(this->indexAt(_curs), QVariant::fromValue(tmpap), Qt::EditRole);
        model()->layoutChanged();
    }
}
void direct_app_view::slot_delete()
{
    model()->removeRow(this->indexAt(_curs).row(),QModelIndex());
    model()->layoutChanged();
}
void direct_app_view::slot_add()
{
    apparaturs ttmma;
    app_editor *appedit = new app_editor(&ttmma, true);
    if (appedit->exec() == QDialog::Accepted){
        int i = model()->rowCount();
        ttmma = appedit->result();
        model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(ttmma), Qt::EditRole);
        model()->layoutChanged();
        if (_pather != nullptr){_pather->slot_reset_list();}
    }
    delete appedit;
}
void direct_app_view::set_pather(direct_app_listing* arg)
{
    _pather = arg;
}
