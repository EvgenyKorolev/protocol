#include "editor_klient.h"

editor_klient::~editor_klient()
{
    delete full_name_label;
    delete email_label;
    delete name_label;
    delete inn_label;
    delete dir_n_label;
    delete dir_p_label;
    delete fadr_label;
    delete fadr_scroll;
    delete padr_label;
    delete padr_scroll;
    delete uadr_label;
    delete uadr_scroll;
    delete tellist;
    delete faxlist;
}
editor_klient::editor_klient(klient *arg, QWidget *parent) : QDialog(parent)
{
    flag_edit = false;
    main_obj = arg;
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Редактор клиента");
// Название
    name_label = new QLabel();
    name_label->setText(arg->get_name());
    QLabel *name_kl = new QLabel();
    name_kl->setText("<b>Название: </b>");
    QPushButton *name_ed = new QPushButton("Изменить...");
    name_ed->setMaximumWidth(100);
    name_ed->setMinimumWidth(100);
    QObject::connect(name_ed, SIGNAL(clicked()), this, SLOT(name_edit()));
    QBoxLayout *name_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    name_lay->addWidget(name_kl);
    name_lay->addWidget(name_label);
    name_lay->addWidget(name_ed);
// Полное наименование
    full_name_label = new QLabel();
    full_name_label->setText(main_obj->get_full_name());
    QLabel *full_name_kl = new QLabel();
    full_name_kl->setText("Полное название: ");
    QPushButton *full_name_ed = new QPushButton("Изменить...");
    full_name_ed->setMaximumWidth(100);
    full_name_ed->setMinimumWidth(100);
    QObject::connect(full_name_ed, SIGNAL(clicked()), this, SLOT(slot_full_name_edit()));
    QBoxLayout *full_name_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    full_name_lay->addWidget(full_name_kl);
    full_name_lay->addWidget(full_name_label);
    full_name_lay->addWidget(full_name_ed);
// Email
    email_label = new QLabel();
    email_label->setText(main_obj->get_email());
    QLabel *email_kl = new QLabel();
    email_kl->setText("Email: ");
    QPushButton *email_ed = new QPushButton("Изменить...");
    email_ed->setMaximumWidth(100);
    email_ed->setMinimumWidth(100);
    QObject::connect(email_ed, SIGNAL(clicked()), this, SLOT(slot_email_edit()));
    QBoxLayout *email_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    email_lay->addWidget(email_kl);
    email_lay->addWidget(email_label);
    email_lay->addWidget(email_ed);
// ИНН
    QString tmpst;
    this->inn_label = new QLabel();
    inn_label->setText(tmpst.setNum(arg->get_det().get_inn()));
    QLabel *inn_kl = new QLabel();
    inn_kl->setText("<b>ИНН: </b>");
    QPushButton *inn_ed = new QPushButton("Изменить...");
    inn_ed->setMaximumWidth(100);
    inn_ed->setMinimumWidth(100);
    QObject::connect(inn_ed, SIGNAL(clicked()), this, SLOT(inn_edit()));
    QBoxLayout *inn_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    inn_lay->addWidget(inn_kl);
    inn_lay->addWidget(inn_label);
    inn_lay->addWidget(inn_ed);

// Директор - должность + ФИО
    this->dir_n_label = new QLabel();
    dir_n_label->setText(arg->get_det().get_dir().second);
    this->dir_p_label = new QLabel();
    if (arg->get_det().get_dir().first == ""){
        dir_p_label->setText("<b>Руководитель</b>");
    } else {
       dir_p_label->setText(arg->get_det().get_dir().first);
    }
    QPushButton *dir_ed = new QPushButton("Изменить...");
    dir_ed->setMaximumWidth(100);
    dir_ed->setMinimumWidth(100);
    QObject::connect(dir_ed, SIGNAL(clicked()), this, SLOT(dir_edit()));
    QBoxLayout *dir_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    dir_lay->addWidget(dir_p_label);
    dir_lay->addWidget(dir_n_label);
    dir_lay->addWidget(dir_ed);

// Реквизиты организации
    QBoxLayout *det_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    // адреса
    QLabel *uadr_txt = new QLabel();
    QLabel *padr_txt = new QLabel();
    uadr_txt->setText("<H4><CENTER>Юридический адрес: <CENTER></H4>");
    padr_txt->setText("<H4><CENTER>Почтовый адрес: <CENTER></H4>");
     QBoxLayout *det_paddress_all = new QBoxLayout(QBoxLayout::LeftToRight);
     QBoxLayout *det_uaddress_all = new QBoxLayout(QBoxLayout::LeftToRight);
    this->padr_scroll = new QScrollArea();
     padr_scroll->setFrameStyle(QFrame::NoFrame);
     padr_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
     padr_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
     padr_scroll->widgetResizable();
     this->padr_label = new QLabel();
    this->uadr_scroll = new QScrollArea();
     uadr_scroll->setFrameStyle(QFrame::NoFrame);
     uadr_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
     uadr_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
     uadr_scroll->widgetResizable();
     this->uadr_label = new QLabel();
    QPushButton *padr_ed = new QPushButton("Изменить...");
    QPushButton *uadr_ed = new QPushButton("Изменить...");
    QObject::connect(padr_ed, SIGNAL(clicked()), this, SLOT(p_address_edit()));
    QObject::connect(uadr_ed, SIGNAL(clicked()), this, SLOT(u_address_edit()));
    padr_ed->setMaximumWidth(100);
    padr_ed->setMinimumWidth(100);
    uadr_ed->setMaximumWidth(100);
    uadr_ed->setMinimumWidth(100);
    address ptmp = arg->get_det().get_ur_post();
    address utmp = arg->get_det().get_re_post();
    this->adr_label_set(padr_label, &ptmp);
    this->adr_label_set(uadr_label, &utmp);
    padr_scroll->setWidget(padr_label);
        padr_label->adjustSize();
    uadr_scroll->setWidget(uadr_label);
        uadr_label->adjustSize();
    det_paddress_all->addWidget(padr_scroll);
    det_paddress_all->addWidget(padr_ed);
    det_uaddress_all->addWidget(uadr_scroll);
    det_uaddress_all->addWidget(uadr_ed);
    padr_scroll->adjustSize();
    uadr_scroll->adjustSize();
    det_layout->addWidget(padr_txt);
    det_layout->addLayout(det_paddress_all);
    det_layout->addWidget(uadr_txt);
    det_layout->addLayout(det_uaddress_all);
// Поле для фактического адреса
    QLabel *fadr_txt = new QLabel();
    fadr_txt->setText("<H4><CENTER>Фактический адрес: <CENTER></H4>");
    QBoxLayout *adr_l = new QBoxLayout(QBoxLayout::LeftToRight);
    this->fadr_scroll = new QScrollArea();
    fadr_scroll->setFrameStyle(QFrame::NoFrame);
    fadr_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    fadr_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    fadr_scroll->widgetResizable();
    this->fadr_label = new QLabel();
    QPushButton *adr_ed = new QPushButton("Изменить...");
    adr_ed->setMaximumWidth(100);
    adr_ed->setMinimumWidth(100);
    address tmp_adr = arg->get_fadr();
    this->adr_label_set(this->fadr_label, &tmp_adr);
    fadr_scroll->setWidget(fadr_label);
        fadr_label->adjustSize();
    adr_l->addWidget(fadr_scroll);
        fadr_scroll->adjustSize();
    adr_l->addWidget(adr_ed);
    QObject::connect(adr_ed, SIGNAL(clicked()), this, SLOT(f_address_edit()));
// Области списков (телефоны и заявки)
    QBoxLayout *main_list_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        QBoxLayout *telfax_lay = new QBoxLayout(QBoxLayout::LeftToRight);
        main_list_lay->addLayout(telfax_lay);
     QBoxLayout *tel_list = new QBoxLayout(QBoxLayout::TopToBottom);
     QBoxLayout *fax_list = new QBoxLayout(QBoxLayout::TopToBottom);
        QLabel *fax_lab = new QLabel();
            fax_lab->setText("<b>Факсы: </b>");
        QLabel *tel_lab = new QLabel();
            tel_lab->setText("<b>Телефоны: </b>");
      telfax_lay->addLayout(tel_list);
      telfax_lay->addLayout(fax_list);
        tel_list->addWidget(tel_lab);
        fax_list->addWidget(fax_lab);
//    QList<QString> list_tel;        // Список телефонов
        this->tellist = new QList<QString>(this->main_obj->get_det().get_tel_list());
        my_list_model *listmodtel = new my_list_model(this->tellist);
        my_list_view *viewtel = new my_list_view(&this->flag_edit, this);
        viewtel->setFlow(QListView::TopToBottom);
        viewtel->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tel_list->addWidget(viewtel);
        viewtel->setModel(listmodtel);
//    QList<QString> list_fax;        // Список факсов
        this->faxlist = new QList<QString>(this->main_obj->get_det().get_fax_list());
        my_list_model *listmodfax = new my_list_model(this->faxlist);
        my_list_view *viewfax = new my_list_view(&this->flag_edit, this);
        viewfax->setFlow(QListView::TopToBottom);
        viewfax->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
         fax_list->addWidget(viewfax);
        viewfax->setModel(listmodfax);
// Финальные кнопки
    QBoxLayout *push_list = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton *push_ok = new QPushButton("Сохранить");
    QPushButton *push_cancel = new QPushButton("Не сохранять");
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(save_klient()));
    push_list->addWidget(push_ok);
    push_list->addWidget(push_cancel);
// Расставляем виджеты
    QBoxLayout *edit_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    edit_layout->addLayout(name_lay);
    edit_layout->addLayout(full_name_lay);
    edit_layout->addLayout(inn_lay);
    edit_layout->addLayout(dir_lay);
    edit_layout->addLayout(email_lay);
    edit_layout->addLayout(det_layout);
    edit_layout->addWidget(fadr_txt);
    edit_layout->addLayout(adr_l);
    edit_layout->addLayout(main_list_lay);
    edit_layout->addStretch(0);
    edit_layout->addLayout(push_list);
    this->setLayout(edit_layout);
    this->setParent(parent);
}
address editor_klient::address_edit(address *arg)
{
    editor_address *aded = new editor_address(arg, this);
    address ret = *arg;
    if (aded->exec() == QDialog::Accepted){
    ret = aded->close_ret();
    delete aded;
    flag_edit = true;
    return ret;
    }
    return ret;
}
void editor_klient::f_address_edit()
{
    address tmp1 = main_obj->get_fadr();
    address *tmp = new address();
    tmp = &tmp1;
    tmp1 = this->address_edit(tmp);
    main_obj->set_fadr(tmp);
    this->adr_label_set(fadr_label, tmp);
}
void editor_klient::p_address_edit()
{
    address tmp1 = main_obj->get_padr();
    address *tmp = new address();
    tmp = &tmp1;
    tmp1 = this->address_edit(tmp);
    main_obj->set_padr(tmp);
    this->adr_label_set(padr_label, tmp);
}
void editor_klient::u_address_edit()
{
    address tmp1 = main_obj->get_uadr();
    address *tmp = new address();
    tmp = &tmp1;
    tmp1 = this->address_edit(tmp);
    main_obj->set_uadr(tmp);
    this->adr_label_set(uadr_label, tmp);
}
void editor_klient::adr_label_set(QLabel *argl, address *arga)
{
   argl->setText(this->get_adr_str(arga));
   argl->adjustSize();
}
void editor_klient::inn_edit()
{
    QString tmp1 = "ИНН: ";
    int_editor *ined = new int_editor(this->main_obj->get_det().get_inn(), &tmp1, 13);
    if (ined->exec() == QDialog::Accepted){
        this->main_obj->set_inn(ined->result());
        this->inn_label->setText(tmp1.setNum(main_obj->get_det().get_inn()));
        this->inn_label->adjustSize();
      flag_edit = true;
    }
    delete ined;
}
void editor_klient::name_edit()
{
    QString tmp1 = "Наименование клиента: ";
    QString tmp2 = this->main_obj->get_name();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_obj->set_name(stred->result());
        this->name_label->setText(main_obj->get_name());
        this->name_label->adjustSize();
      flag_edit = true;
    }
    delete stred;
}
void editor_klient::slot_full_name_edit()
{
    QString tmp1 = "Полное название: ";
    QString tmp2 = main_obj->get_full_name();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 500);
    if (stred->exec() == QDialog::Accepted){
        this->main_obj->set_full_name(stred->result());
        this->full_name_label->setText(main_obj->get_full_name());
        this->full_name_label->adjustSize();
        flag_edit = true;
    }
    delete stred;
}
void editor_klient::slot_email_edit()
{
    QString tmp1 = "Email: ";
    QString tmp2 = main_obj->get_email();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_obj->set_email(stred->result());
        this->email_label->setText(main_obj->get_email());
        this->email_label->adjustSize();
        flag_edit = true;
    }
    delete stred;
}
void editor_klient::dir_edit()
{
    QString tmp1 = "Руководитель: ";
    QString tmp2 = "Должность: ";
    QString tmp3 = "Имя (Ф.И.О): ";
    pair_editor *dired = new pair_editor(this->main_obj->get_det().get_dir(), &tmp1, &tmp2, &tmp3, 300, 300, 100, 100);
    if (dired->exec() == QDialog::Accepted){
        this->main_obj->set_dir(dired->result());
        dir_n_label->setText(main_obj->get_det().get_dir().second);
        dir_p_label->setText(main_obj->get_det().get_dir().first);
        dir_n_label->adjustSize();
        dir_p_label->adjustSize();
      flag_edit = true;
    }
    delete dired;
}
klient editor_klient::result() {return *this->main_obj;}
void editor_klient::save_klient()
{
   if (main_obj->get_name() != "") {
       main_obj->set_fax_list(*(this->faxlist));
       main_obj->set_tel_list(*(this->tellist));
       emit accept();
   }
   else {
       QMessageBox *tmoer = new QMessageBox();
       tmoer->setWindowTitle("Внимание!");
       tmoer->setText("Нельзя создавать клиента совсем без имени");
       tmoer->exec();
       delete tmoer;
   }
}
QString editor_klient::get_adr_str(address *arg)
{
    QString tmp1;
    QString tmp_str;
    bool status1 = false;
    bool status2 = false;
     if (arg->get_country() != "") {tmp_str.append(arg->get_country()); tmp_str.append(", "); status1 = true;}
     if ((arg->get_state_class() !="") || (arg->get_state() != "")) {tmp_str.append(arg->get_state_class()); tmp_str.append(" "); tmp_str.append(arg->get_state()); tmp_str.append("<br>");}
        else status2 = true;
     if (status2 == true && status1 == true) {tmp_str.append("<br>");}
   status1 = false; status2 = false;
     if (arg->get_state_distr() != "") {tmp_str.append(arg->get_state_distr()); tmp_str.append(", "); status1 = true;}
     if ((arg->get_city_class() != "") || (arg->get_city() != "")) {tmp_str.append(arg->get_city_class()); tmp_str.append(" "); tmp_str.append(arg->get_city()); tmp_str.append(", "); status1 = true;}
     if (arg->get_district() != "") {tmp_str.append(arg->get_district()); tmp_str.append("<br>");}
        else status2 = true;
     if (status2 == true && status1 == true) {tmp_str.append("<br>");}
   status1 = false; status2 = false;
      if ((arg->get_street_class() != "") || (arg->get_street() !="")) {tmp_str.append(arg->get_street_class()); tmp_str.append(" "); tmp_str.append(arg->get_street()); tmp_str.append(" ");status1 = true;}
      if ((arg->get_building_num()) || (arg->get_building_lit() != ""))  {tmp_str.append("дом №"); tmp_str.append(" "); tmp_str.append(tmp1.setNum(arg->get_building_num())); tmp_str.append(arg->get_building_lit()); tmp_str.append(" ");status1 = true;}
      if ((arg->get_office_num() != 0) || (arg->get_office_lit() != "")) {tmp_str.append("Офис"); tmp_str.append(" "); tmp_str.append(tmp1.setNum(arg->get_office_num())); tmp_str.append(arg->get_office_lit()); tmp_str.append("<br>");}
         else status2 = true;
      if (status2 == true && status1 == true) {tmp_str.append("<br>");}
    status1 = false; status2 = false;
        if (arg->get_post_index() != 0) {tmp_str.append("Индекс:"); tmp_str.append(" "); tmp_str.append(tmp1.setNum(arg->get_post_index())); tmp_str.append("<br>");}
        return tmp_str;
}
bool editor_klient::is_edit()
{
    return flag_edit;
}
