#include "type_in_direct.h"

type_in_direct::type_in_direct()
{
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Выбрать набор констант");
    this->setMinimumWidth(630);
    ret = std::make_tuple("", "", "", "");
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QPushButton* ok = new QPushButton("Закрыть");
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(reject()));
    apdm = new p_types_model();
    type_const_loader &tcnl = type_const_loader::getInstance();
    QList<QString> tmpl = tcnl.get_var_list();
    int i{0};
    for (auto it : tmpl){
       type_obj tmpto = tcnl.get_obj(it);
       std::tuple<QString, QString, QString, QString> tmpt = std::make_tuple(tmpto.get_name(), tmpto.get_description(), tmpto.get_vname(), tmpto.get_cls());
       apdm->setData(QModelIndex(), QVariant::fromValue(tmpt), Qt::EditRole);
       ++i;
    }
    apdv = new type_in_view();
    apdv->set_pather(this);
    QSortFilterProxyModel* proxy_mod = new QSortFilterProxyModel();
    proxy_mod->setSourceModel(apdm);
    apdv->setModel(proxy_mod);
    apdv->setSortingEnabled(true);
    ok->setMinimumWidth(100);
    apdv->setColumnWidth(0, 150);
    apdv->horizontalHeader()->setStretchLastSection(true);
    apdv->setMinimumHeight(400);
    apdv->scrollToBottom();
    QBoxLayout* but_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* titl = new QLabel();
    titl->setText("Найти набор по названию: ");
    QPushButton* find_but = new QPushButton("Найти");
    find_but->setMinimumWidth(100);
    QPushButton* reset_but = new QPushButton("Сбросить");
    reset_but->setMinimumWidth(100);
    QObject::connect(find_but, SIGNAL(clicked()), this, SLOT(slot_filtr()));
    QObject::connect(reset_but, SIGNAL(clicked()), this, SLOT(slot_reset_list()));
    find_ar = new QLineEdit();
    find_ar->setMinimumWidth(200);
    but_lay->addWidget(titl);
    but_lay->addWidget(find_ar);
    but_lay->addWidget(find_but);
    but_lay->addWidget(reset_but);
    main_lay->addLayout(but_lay);
    main_lay->addWidget(apdv);
    main_lay->addWidget(ok);
    this->setLayout(main_lay);
}
void type_in_direct::result()
{
    ret = apdv->result();
    emit accept();
}
std::tuple<QString, QString, QString, QString> type_in_direct::get_result()
{
    return ret;
}
void type_in_direct::slot_reset_list()
{
    QSortFilterProxyModel* proxy_mod = new QSortFilterProxyModel();
    proxy_mod->setSourceModel(apdm);
    apdv->setModel(proxy_mod);
    apdv->setColumnWidth(0, 150);
    apdv->horizontalHeader()->setStretchLastSection(true);
    apdv->scrollToBottom();
}
void type_in_direct::slot_filtr()
{
    QSortFilterProxyModel* proxy_model = new QSortFilterProxyModel();
    proxy_model->setSourceModel(apdm);
    proxy_model->setFilterKeyColumn(0);
    filter_maker fltr(find_ar->text(), false);
    QRegExp my_reg_string = fltr.result();
    proxy_model->setFilterRegExp(my_reg_string);
    apdv->setModel(proxy_model);
}
