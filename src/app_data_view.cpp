#include "app_data_view.h"

app_data_view::app_data_view(bool *arg, QWidget *par) : QTableView(par)
{
    this->flag_edit = arg;
}
void app_data_view::mousePressEvent(QMouseEvent * arg)
{
    if (arg->buttons() == Qt::RightButton) {
        QMenu *mnu = new QMenu(this);
        mnu->setEnabled(true);
        QAction *make_app = new QAction(trUtf8("Добавить"), this);
        QObject::connect(make_app, SIGNAL(triggered()), this, SLOT(slot_add()));
        QAction *insert_app = new QAction(trUtf8("Из справочника"), this);
        QObject::connect(insert_app, SIGNAL(triggered()), this, SLOT(slot_insert()));
        mnu->addAction(make_app);
        mnu->addAction(insert_app);
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
void app_data_view::mouseDoubleClickEvent(QMouseEvent* arg)
{
    this->_curs = arg->pos();
    if (this->indexAt(arg->pos()).isValid()){
          this->slot_edit();
    } else {
        this->slot_add();
    }
    QTableView::mouseDoubleClickEvent(arg);
}
void app_data_view::slot_edit()
{
    apparaturs *tmpap = new apparaturs();
    tmpap = this->indexAt(_curs).data(Qt::EditRole).value<apparaturs*>();
    app_editor *appedit = new app_editor(tmpap);
    if (appedit->exec() == QDialog::Accepted){
        *tmpap = appedit->result();
        model()->setData(this->indexAt(_curs), QVariant::fromValue(tmpap), Qt::EditRole);
        model()->layoutChanged();
        *flag_edit = true;
    }
}
void app_data_view::slot_delete()
{
    model()->removeRow(this->indexAt(_curs).row(),QModelIndex());
    model()->layoutChanged();
    *flag_edit = true;
}
void app_data_view::slot_add()
{
    apparaturs *ttmma = new apparaturs();
    app_editor *appedit = new app_editor(ttmma);
    if (appedit->exec() == QDialog::Accepted){
        int i = model()->rowCount();
        *ttmma = appedit->result();
        model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(ttmma), Qt::EditRole);
        model()->layoutChanged();
        *flag_edit = true;
    }
    delete appedit;
}
void app_data_view::slot_insert()
{
    app_in_direct* instr = new app_in_direct();
    if (instr->exec() == QDialog::Accepted){
        int i = model()->rowCount();
        apparaturs *ttmma = new apparaturs();
        *ttmma = instr->get_result();
        model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(ttmma), Qt::EditRole);
        model()->layoutChanged();
        *flag_edit = true;
    }
    delete instr;
}
