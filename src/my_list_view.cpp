#include "my_list_view.h"

my_list_view::my_list_view(bool *arg, QWidget *par) : QListView(par)
{
    this->flag_edit = arg;
}
void my_list_view::mousePressEvent(QMouseEvent * arg)
{
    if (arg->buttons() == Qt::RightButton){
        QMenu *mnu = new QMenu(this);
        mnu->setEnabled(true);
        QAction *make_str = new QAction(trUtf8("Добавить"), this);
        QObject::connect(make_str, SIGNAL(triggered()), this, SLOT(slot_add()));
        mnu->addAction(make_str);
      if (this->indexAt(arg->pos()).isValid()){
        this->curs = arg->pos();
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
    QListView::mousePressEvent(arg);
}
void my_list_view::mouseDoubleClickEvent(QMouseEvent* arg)
{
    this->curs = arg->pos();
    if (this->indexAt(arg->pos()).isValid()){
          this->slot_edit();
    } else {
        this->slot_add();
    }
    QListView::mouseDoubleClickEvent(arg);
}
void my_list_view::slot_add()
{
    QString tmp1 = "Номер: ";
    QString tmp2 = "";
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        int i = model()->rowCount();
        model()->setData(model()->index(i, 0, QModelIndex()), QVariant(stred->result()), Qt::EditRole);
        model()->layoutChanged();
       *flag_edit = true;
    }
    delete stred;
}
void my_list_view::slot_edit()
{
    QString tmp1 = "Номер: ";
    QString tmp2 = this->indexAt(curs).data(Qt::EditRole).value<QString>();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        model()->setData(this->indexAt(curs), QVariant(stred->result()), Qt::EditRole);
        model()->layoutChanged();
       *flag_edit = true;
    }
    delete stred;
}
void my_list_view::slot_delete()
{
    model()->removeRow(this->indexAt(curs).row(),QModelIndex());
    model()->layoutChanged();
    *flag_edit = true;
}
