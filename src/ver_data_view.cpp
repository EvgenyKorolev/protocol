#include "ver_data_view.h"

ver_data_view::ver_data_view(bool *arg, QWidget *par) : QTableView(par)
{
    this->flag_edit = arg;
}
void ver_data_view::mousePressEvent(QMouseEvent *arg)
{
    if(arg->buttons() == Qt::RightButton){
         QMenu *mnu = new QMenu(this);
         mnu->setEnabled(true);
         QAction *make_ver = new QAction(trUtf8("Добавить"), this);
         QObject::connect(make_ver, SIGNAL(triggered()), this, SLOT(slot_add()));
         mnu->addAction(make_ver);
    if ((arg->buttons() == Qt::RightButton) && (this->indexAt(arg->pos()).isValid())){
          this->curs = arg->pos();
          QAction *del_ver = new QAction("Удалить", this);
          QAction *edit_ver = new QAction("Изменить", this);
          QObject::connect(del_ver, SIGNAL(triggered()), this, SLOT(slot_delete()));
          QObject::connect(edit_ver, SIGNAL(triggered()), this, SLOT(slot_edit()));
          mnu->addAction(del_ver);
          mnu->addAction(edit_ver);
      }
    mnu->popup(arg->globalPos());
    mnu->show();
    }
    QTableView::mousePressEvent(arg);
}
void ver_data_view::mouseDoubleClickEvent(QMouseEvent* arg)
{
    this->curs = arg->pos();
    if (this->indexAt(arg->pos()).isValid()){
          this->slot_edit();
    } else {
        this->slot_add();
    }
    QTableView::mouseDoubleClickEvent(arg);
}
void ver_data_view::slot_edit()
{
    QPair<QPair<QString, QDate>, QDate> tmpp;
    ppair_type tmpt;
    tmpt = this->indexAt(curs).data(Qt::EditRole).value<ppair_type>();
    tmpp.first.first = tmpt.first.first;
    tmpp.first.second = tmpt.first.second;
    tmpp.second = tmpt.second;
    QString lbl0 = "Поверка прибора";
    QString lbl1 = "Номер свидетельства";
    QString lbl2 = "Дата поверки";
    QString lbl3 = "Дата следующей поверки";
    ver_editor *vered = new ver_editor(&tmpp, lbl0, lbl1, lbl2, lbl3);
    if (vered->exec() == QDialog::Accepted){
        tmpt.first.first = vered->result().first.first;
        tmpt.first.second = vered->result().first.second;
        tmpt.second = vered->result().second;
        model()->setData(this->indexAt(curs), QVariant::fromValue(tmpt), Qt::EditRole);
        model()->layoutChanged();
       *flag_edit = true;
    }
    delete vered;
}
void ver_data_view::slot_delete()
{
    model()->removeRow(this->indexAt(curs).row(), QModelIndex());
    model()->layoutChanged();
    *flag_edit = true;
}
void ver_data_view::slot_add()
{
    QString lbl0 = "Поверка прибора";
    QString lbl1 = "Номер свидетельства";
    QString lbl2 = "Дата поверки";
    QString lbl3 = "Дата следующей поверки";
    QPair<QPair<QString, QDate>, QDate> tmpt;
    ver_editor *vered = new ver_editor(&tmpt, lbl0, lbl1, lbl2, lbl3);
    if (vered->exec() == QDialog::Accepted){
        int i = model()->rowCount();
    ppair_type tmpp;
    tmpp.first.first = vered->result().first.first;
    tmpp.first.second = vered->result().first.second;
    tmpp.second = vered->result().second;
    model()->setData(model()->index(i, 0, QModelIndex()), QVariant::fromValue(tmpp), Qt::EditRole);
    model()->layoutChanged();
    *flag_edit = true;
    }
    delete vered;
}
