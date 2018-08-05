#include "p_types_view.h"

p_types_view::p_types_view(QWidget *par) : QTableView(par)
{

}
void p_types_view::mousePressEvent(QMouseEvent * arg)
{
    if (arg->buttons() == Qt::RightButton) {
        QMenu *mnu = new QMenu(this);
        mnu->setEnabled(true);
        curs = arg->pos();
        QAction *add_app = new QAction("Добавить из списка", this);
        QObject::connect(add_app, SIGNAL(triggered()), this, SLOT(slot_add()));
      if (this->indexAt(arg->pos()).isValid()){
        QAction *del_app = new QAction("Удалить", this);
        QObject::connect(del_app, SIGNAL(triggered()), this, SLOT(slot_delete()));
        mnu->addAction(del_app);
      }
      mnu->addAction(add_app);
      mnu->popup(arg->globalPos());
      mnu->show();
    }
    QTableView::mousePressEvent(arg);
}
void p_types_view::slot_add()
{
    type_in_direct* ptid = new type_in_direct();
    if (ptid->exec() == QDialog::Accepted){
        model()->setData(QModelIndex(), QVariant::fromValue(ptid->get_result()), Qt::EditRole);
        model()->layoutChanged();
    }
    delete ptid;
}
void p_types_view::slot_delete()
{
    model()->removeRow(this->indexAt(curs).row(),QModelIndex());
    model()->layoutChanged();
}
