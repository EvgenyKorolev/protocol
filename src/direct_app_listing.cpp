#include "direct_app_listing.h"

direct_app_listing::direct_app_listing()
{
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Справочник приборов");
    this->setMinimumWidth(860);
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QPushButton* ok = new QPushButton("Закрыть");
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    _apdm = new direct_app_model();
    _apdv = new direct_app_view();
    _apdv->set_pather(this);
    QSortFilterProxyModel* proxy_mod = new QSortFilterProxyModel();
    proxy_mod->setSourceModel(_apdm);
    _apdv->setModel(proxy_mod);
    _apdv->setSortingEnabled(true);
    ok->setMinimumWidth(100);
    _apdv->setColumnWidth(0, 200);
    _apdv->setColumnWidth(1, 120);
    _apdv->setColumnWidth(2, 150);
    _apdv->setColumnWidth(3, 150);
    _apdv->horizontalHeader()->setStretchLastSection(true);
    _apdv->setMinimumHeight(400);
    _apdv->scrollToBottom();

    QBoxLayout* but_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton* add_but = new QPushButton("Добавить");
    add_but->setMaximumWidth(80);
    add_but->setMinimumWidth(80);
    QObject::connect(add_but, SIGNAL(clicked()), _apdv, SLOT(slot_add()));
    _find_str = new QComboBox();
    _find_str->setMaximumWidth(120);
    _find_str->setMinimumWidth(120);
    _find_status = new QComboBox();
    _find_status->setMaximumWidth(100);
    _find_status->setMinimumWidth(100);
    QPushButton* find_but = new QPushButton("Найти");
    QPushButton* reset_but = new QPushButton("Сбросить");
    QObject::connect(find_but, SIGNAL(clicked()), this, SLOT(slot_filtr()));
    QObject::connect(reset_but, SIGNAL(clicked()), this, SLOT(slot_reset_list()));
    _find_status->setMaximumWidth(80);
    _find_status->setMinimumWidth(80);
    _find_ar = new QLineEdit();
    _find_ar->setMinimumWidth(300);
    _find_str->addItem("Название", QVariant("name"));
    _find_str->addItem("Тип прибора", QVariant("type"));
    _find_str->addItem("Завод №", QVariant("mnom"));
    _find_str->addItem("Кл. точн.", QVariant("cls"));

    _find_status->addItem("содержит", QVariant("incl"));
    _find_status->addItem("равно", QVariant("eq"));

    but_lay->addWidget(add_but);
    but_lay->addWidget(_find_str);
    but_lay->addWidget(_find_status);
    but_lay->addWidget(_find_ar);
    but_lay->addWidget(find_but);
    but_lay->addWidget(reset_but);
    main_lay->addLayout(but_lay);
    main_lay->addWidget(_apdv);
    main_lay->addWidget(ok);
    this->setLayout(main_lay);
}
void direct_app_listing::slot_reset_list()
{
    QSortFilterProxyModel* proxy_mod = new QSortFilterProxyModel();
    proxy_mod->setSourceModel(_apdm);
    _apdv->setModel(proxy_mod);
    _apdv->setColumnWidth(0, 200);
    _apdv->setColumnWidth(1, 120);
    _apdv->setColumnWidth(2, 150);
    _apdv->setColumnWidth(3, 150);
    _apdv->horizontalHeader()->setStretchLastSection(true);
    _apdv->scrollToBottom();
}
void direct_app_listing::slot_filtr()
{
    QSortFilterProxyModel* proxy_model = new QSortFilterProxyModel();
    proxy_model->setSourceModel(_apdm);
    bool eq;
    if (_find_status->itemData(_find_status->currentIndex()).toString() == "eq"){
        eq = true;
    } else { eq = false;}
    if (_find_str->itemData(_find_str->currentIndex()).toString() == "name"){proxy_model->setFilterKeyColumn(0);}
    if (_find_str->itemData(_find_str->currentIndex()).toString() == "type"){proxy_model->setFilterKeyColumn(2);}
    if (_find_str->itemData(_find_str->currentIndex()).toString() == "mnom"){proxy_model->setFilterKeyColumn(3);}
    if (_find_str->itemData(_find_str->currentIndex()).toString() == "cls"){proxy_model->setFilterKeyColumn(4);}
    filter_maker fltr(_find_ar->text(), eq);
    QRegExp my_reg_string = fltr.result();
    proxy_model->setFilterRegExp(my_reg_string);
    _apdv->setModel(proxy_model);
}
