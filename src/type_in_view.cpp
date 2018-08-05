#include "type_in_view.h"

type_in_view::type_in_view(QWidget *par) : QTableView(par){}
void type_in_view::mousePressEvent(QMouseEvent * arg)
{
    if (arg->buttons() == Qt::RightButton) {
      if (this->indexAt(arg->pos()).isValid()){
        QMenu *mnu = new QMenu(this);
        mnu->setEnabled(true);
        curs = arg->pos();
        QAction *select_app = new QAction("Выбрать", this);
        QObject::connect(select_app, SIGNAL(triggered()), this, SLOT(slot_return()));
        mnu->addAction(select_app);
        mnu->popup(arg->globalPos());
        mnu->show();
      }
    }
    QTableView::mousePressEvent(arg);
}
void type_in_view::mouseDoubleClickEvent(QMouseEvent* arg)
{
    this->curs = arg->pos();
    if (this->indexAt(arg->pos()).isValid()){
          this->slot_return();
    }
    QTableView::mouseDoubleClickEvent(arg);
}
void type_in_view::set_pather(type_in_direct* arg)
{
    pather = arg;
}
std::tuple<QString, QString, QString> type_in_view::result()
{
    return  ret;
}
void type_in_view::slot_return()
{
    ret = this->indexAt(curs).data(Qt::EditRole).value<tuple_qss>();
    if (pather != nullptr){
        pather->result();
    }
}
