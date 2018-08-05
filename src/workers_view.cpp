#include "workers_view.h"

workers_view::workers_view(bool *arg, QWidget *par) : QTableView(par)
{
    this->flag_edit = arg;
}
void workers_view::mousePressEvent(QMouseEvent * arg)
{
    if (arg->buttons() == Qt::RightButton){
        QMenu *mnu = new QMenu(this);
        mnu->setEnabled(true);
        QAction *make_app = new QAction(trUtf8("Добавить"), this);
        QObject::connect(make_app, SIGNAL(triggered()), this, SLOT(slot_add()));
        mnu->addAction(make_app);
        if (this->indexAt(arg->pos()).isValid()){
            this->curs = arg->pos();
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
void workers_view::mouseDoubleClickEvent(QMouseEvent* arg)
{
    this->curs = arg->pos();
    if (this->indexAt(arg->pos()).isValid()){
          this->slot_edit();
    } else {
        this->slot_add();
    }
    QTableView::mouseDoubleClickEvent(arg);
}
void workers_view::slot_edit()
{
    worker tmw;
    tmw = this->indexAt(curs).data(Qt::EditRole).value<worker>();
    editor_worker *workedit = new editor_worker(&tmw);
    if (workedit->exec() == QDialog::Accepted){
        model()->setData(this->indexAt(curs), QVariant::fromValue(tmw), Qt::EditRole);
        model()->layoutChanged();
        *flag_edit = true;
    }
}
void workers_view::slot_delete()
{
    model()->removeRow(this->indexAt(curs).row(),QModelIndex());
    model()->layoutChanged();
    *flag_edit = true;
}
void workers_view::slot_add()
{
    worker tmw;
    editor_worker *workedit = new editor_worker(&tmw);
    if (workedit->exec() == QDialog::Accepted){
        int i = 0;
        i = model()->rowCount();
        model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(tmw), Qt::EditRole);
        model()->layoutChanged();
        *flag_edit = true;
    }
}
