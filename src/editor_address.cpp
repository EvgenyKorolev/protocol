#include "editor_address.h"
editor_address::editor_address(address *arg, QWidget *par) : QDialog(par)
{
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Адрес");
    _obj_adr = new address();
    _country_edit = new QLineEdit();
    _state_edit = new QLineEdit();
    _state_class_edit = new QLineEdit();
    _state_distr_edit = new QLineEdit();
    _city_edit = new QLineEdit();
    _city_class_edit = new QLineEdit();
    _district_edit = new QLineEdit();
    _street_edit = new QLineEdit();
    _street_class_edit = new QLineEdit();
    _building_n_edit = new QLineEdit();
    _building_l_edit = new QLineEdit();
    _office_n_edit = new QLineEdit();
    _office_l_edit = new QLineEdit();
    _post_index_edit = new QLineEdit();

        _country_edit->setMaxLength(100);
        _state_edit->setMaxLength(100);
        _state_class_edit->setMaxLength(100);
        _state_distr_edit->setMaxLength(100);
        _city_edit->setMaxLength(100);
        _city_class_edit->setMaxLength(100);
        _district_edit->setMaxLength(100);
        _street_edit->setMaxLength(100);
        _street_class_edit->setMaxLength(100);
        _building_n_edit->setMaxLength(5);
        _building_l_edit->setMaxLength(20);
        _office_n_edit->setMaxLength(5);
        _office_l_edit->setMaxLength(20);
        _post_index_edit->setMaxLength(10);

        _country_edit->setInputMask("");
        _state_edit->setInputMask("");
        _state_class_edit->setInputMask("");
        _state_distr_edit->setInputMask("");
        _city_edit->setInputMask("");
        _city_class_edit->setInputMask("");
        _district_edit->setInputMask("");
        _street_edit->setInputMask("");
        _street_class_edit->setInputMask("");
        _building_n_edit->setInputMask("00000");
        _building_l_edit->setInputMask("");
        _office_n_edit->setInputMask("00000");
        _office_l_edit->setInputMask("");
        _post_index_edit->setInputMask("0000000000");

_country_edit->setText(arg->get_country());
_state_edit->setText(arg->get_state());
_state_class_edit->setText(arg->get_state_class());
_state_distr_edit->setText(arg->get_state_distr());
_city_edit->setText(arg->get_city());
_city_class_edit->setText(arg->get_city_class());
_district_edit->setText(arg->get_district());
_street_edit->setText(arg->get_street());
_street_class_edit->setText(arg->get_street_class());
_building_n_edit->setText(QString::number(arg->get_building_num()));
_building_l_edit->setText(arg->get_building_lit());
_office_n_edit->setText(QString::number(arg->get_office_num()));
_office_l_edit->setText(arg->get_office_lit());
_post_index_edit->setText(QString::number(arg->get_post_index()));

_country_edit->setMinimumWidth(200);
_state_edit->setMinimumWidth(200);
_state_class_edit->setMinimumWidth(200);
_state_distr_edit->setMinimumWidth(200);
_city_edit->setMinimumWidth(200);
_city_class_edit->setMinimumWidth(200);
_district_edit->setMinimumWidth(200);
_street_edit->setMinimumWidth(200);
_street_class_edit->setMinimumWidth(200);
_building_n_edit->setMinimumWidth(200);
_building_l_edit->setMinimumWidth(200);
_office_n_edit->setMinimumWidth(200);
_office_l_edit->setMinimumWidth(200);
_post_index_edit->setMinimumWidth(200);

    QLabel *country_label = new QLabel("Страна:");
    QLabel *state_label = new QLabel("Регион:");
    QLabel *state_class_label = new QLabel("Статус региона:");
    QLabel *state_distr_label = new QLabel("Район региона:");
    QLabel *city_label = new QLabel("Населенный пункт:");
    QLabel *city_class_label = new QLabel("Вид населенного <br> пункта:");
    QLabel *district_label = new QLabel("Район нас. пункта:");
    QLabel *street_label = new QLabel("Улица: ");
    QLabel *street_class_label = new QLabel("Вид улицы:");

    QLabel *building_n_label = new QLabel("Номер дома:");
    QLabel *building_l_label = new QLabel("Литер:");

    QLabel *office_n_label = new QLabel("Номер помещения:");
    QLabel *office_l_label = new QLabel("Литер:");

    QLabel *post_index_label = new QLabel("Почтовый индекс:");


    country_label->setMinimumWidth(130);
    state_label->setMinimumWidth(130);
    state_class_label->setMinimumWidth(130);
    state_distr_label->setMinimumWidth(130);
    city_label->setMinimumWidth(130);
    city_class_label->setMinimumWidth(130);
    district_label->setMinimumWidth(130);
    street_label->setMinimumWidth(80);
    street_class_label->setMinimumWidth(130);
    building_n_label->setMinimumWidth(130);
    building_l_label->setMinimumWidth(80);
    office_n_label->setMinimumWidth(130);
    office_l_label->setMinimumWidth(80);
    post_index_label->setMinimumWidth(130);

    QPushButton *a_ok = new QPushButton("Готово");
    QPushButton *a_cancel = new QPushButton("Отмена");
    QObject::connect(a_ok, SIGNAL(clicked()), this, SLOT(adr_save()));
    QObject::connect(a_cancel, SIGNAL(clicked()), this, SLOT(reject()));

    QBoxLayout *lay_adr = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *lay_country = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *lay_state = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *lay_state_distr = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *lay_city = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *lay_district = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *lay_street = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *lay_building = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *lay_office = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *lay_post_index = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *lay_end = new QBoxLayout(QBoxLayout::LeftToRight);

    lay_country->addWidget(country_label);
    lay_country->addWidget(_country_edit);
    lay_state->addWidget(state_class_label);
    lay_state->addWidget(_state_class_edit);
    lay_state->addWidget(state_label);
    lay_state->addWidget(_state_edit);
    lay_state_distr->addWidget(state_distr_label);
    lay_state_distr->addWidget(_state_distr_edit);
    lay_city->addWidget(city_class_label);
    lay_city->addWidget(_city_class_edit);
    lay_city->addWidget(city_label);
    lay_city->addWidget(_city_edit);
    lay_district->addWidget(district_label);
    lay_district->addWidget(_district_edit);
    lay_street->addWidget(street_class_label);
    lay_street->addWidget(_street_class_edit);
    lay_street->addWidget(street_label);
    lay_street->addWidget(_street_edit);
    lay_building->addWidget(building_n_label);
    lay_building->addWidget(_building_n_edit);
    lay_building->addWidget(building_l_label);
    lay_building->addWidget(_building_l_edit);
    lay_office->addWidget(office_n_label);
    lay_office->addWidget(_office_n_edit);
    lay_office->addWidget(office_l_label);
    lay_office->addWidget(_office_l_edit);
    lay_post_index->addWidget(post_index_label);
    lay_post_index->addWidget(_post_index_edit);

    lay_end->addWidget(a_ok);
    lay_end->addWidget(a_cancel);

    lay_adr->addStretch(0);
    lay_adr->addLayout(lay_country);
    lay_adr->addStretch(1);
    lay_adr->addLayout(lay_state);
    lay_adr->addStretch(2);
    lay_adr->addLayout(lay_state_distr);
    lay_adr->addStretch(3);
    lay_adr->addLayout(lay_city);
    lay_adr->addStretch(4);
    lay_adr->addLayout(lay_district);
    lay_adr->addStretch(5);
    lay_adr->addLayout(lay_street);
    lay_adr->addStretch(6);
    lay_adr->addLayout(lay_building);
    lay_adr->addStretch(7);
    lay_adr->addLayout(lay_office);
    lay_adr->addStretch(8);
    lay_adr->addLayout(lay_post_index);
    lay_adr->addStretch(9);
    lay_adr->addLayout(lay_end);
    this->setLayout(lay_adr);
}
void editor_address::adr_save()
{
    _obj_adr->set_country(_country_edit->text());
    _obj_adr->set_state(_state_edit->text());
    _obj_adr->set_state_class(_state_class_edit->text());
    _obj_adr->set_state_distr(_state_distr_edit->text());
    _obj_adr->set_city(_city_edit->text());
    _obj_adr->set_city_class(_city_class_edit->text());
    _obj_adr->set_district(_district_edit->text());
    _obj_adr->set_street(_street_edit->text());
    _obj_adr->set_street_class(_street_class_edit->text());
    _obj_adr->set_building_num(_building_n_edit->text().toInt());
    _obj_adr->set_building_lit(_building_l_edit->text());
    _obj_adr->set_office_num(_office_n_edit->text().toInt());
    _obj_adr->set_office_lit(_office_l_edit->text());
    _obj_adr->set_post_index(_post_index_edit->text().toUInt());
    emit accept();
}
address editor_address::close_ret()
{
    return *_obj_adr;
}
editor_address::~editor_address()
{
    delete _obj_adr;
    delete _country_edit;
    delete _state_edit;
    delete _state_class_edit;
    delete _state_distr_edit;
    delete _city_edit;
    delete _city_class_edit;
    delete _district_edit;
    delete _street_edit;
    delete _street_class_edit;
    delete _building_n_edit;
    delete _building_l_edit;
    delete _office_n_edit;
    delete _office_l_edit;
    delete _post_index_edit;
}
