#include "editor_laboratory.h"

editor_laboratory::~editor_laboratory()
{
    delete name_label;
    delete att_label;
    delete inn_label;
    delete dir_n_label;
    delete dir_p_label;
    delete full_name_label;
    delete email_label;
    delete fadr_label;
    delete fadr_scroll;
    delete padr_label;
    delete padr_scroll;
    delete uadr_label;
    delete uadr_scroll;
    delete tellist;
    delete faxlist;
}
editor_laboratory::editor_laboratory(QWidget *parent) : QDialog(parent)
{
    this->edited = false;
    this->main_obj = &laboratory::getInstance();
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Лаборатория");
    this->setMinimumWidth(825);
// Название
    this->name_label = new QLabel();
    name_label->setText(main_obj->get_name());
    QLabel *name_kl = new QLabel();
    name_kl->setText("Краткое название: ");
    QPushButton *name_ed = new QPushButton("Изменить...");
    name_ed->setMaximumWidth(100);
    name_ed->setMinimumWidth(100);
    QObject::connect(name_ed, SIGNAL(clicked()), this, SLOT(slot_name_edit()));
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
// Аттестат акредитации
    this->att_label = new QLabel();
    att_label->setText(main_obj->get_attestat());
    QLabel *name_att = new QLabel();
    name_att->setText("Аттестат: ");
    QPushButton *att_ed = new QPushButton("Изменить...");
    att_ed->setMaximumWidth(100);
    att_ed->setMinimumWidth(100);
    QObject::connect(att_ed, SIGNAL(clicked()), this, SLOT(slot_att_edit()));
    QBoxLayout *att_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    att_lay->addWidget(name_att);
    att_lay->addWidget(att_label);
    att_lay->addWidget(att_ed);
//    QDate Дата выдачи сертификата
    this->att_data_label = new QLabel();
    att_data_label->setText(main_obj->get_att_date().toString("dd.MM.yy"));
    QLabel *att_data_app = new QLabel();
    att_data_app->setText("Дата аттестата:");
    QPushButton *att_data_ed = new QPushButton("Изменить...");
    att_data_ed->setMaximumWidth(100);
    att_data_ed->setMinimumWidth(100);
    QObject::connect(att_data_ed, SIGNAL(clicked()), this, SLOT(att_data_edit()));
    QBoxLayout *att_data_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    att_data_lay->addWidget(att_data_app);
    att_data_lay->addWidget(att_data_label);
    att_data_lay->addWidget(att_data_ed);
// ИНН
    QString tmpst;
    this->inn_label = new QLabel();
    inn_label->setText(tmpst.setNum(main_obj->get_det().get_inn()));
    QLabel *inn_kl = new QLabel();
    inn_kl->setText("ИНН: ");
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
    dir_n_label->setText(main_obj->get_det().get_dir().second);
    this->dir_p_label = new QLabel();
    if (main_obj->get_det().get_dir().first == ""){
        dir_p_label->setText("Руководитель");
    } else {
       dir_p_label->setText(main_obj->get_det().get_dir().first);
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
    padr_scroll->setMinimumHeight(80);
    this->padr_label = new QLabel();
    this->uadr_scroll = new QScrollArea();
    uadr_scroll->setFrameStyle(QFrame::NoFrame);
    uadr_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    uadr_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    uadr_scroll->widgetResizable();
    uadr_scroll->setMinimumHeight(80);
    this->uadr_label = new QLabel();
    QPushButton *padr_ed = new QPushButton("Изменить...");
    QPushButton *uadr_ed = new QPushButton("Изменить...");
    QObject::connect(padr_ed, SIGNAL(clicked()), this, SLOT(p_address_edit()));
    QObject::connect(uadr_ed, SIGNAL(clicked()), this, SLOT(u_address_edit()));
    padr_ed->setMaximumWidth(100);
    padr_ed->setMinimumWidth(100);
    uadr_ed->setMaximumWidth(100);
    uadr_ed->setMinimumWidth(100);
    address ptmp = main_obj->get_det().get_ur_post();
    address utmp = main_obj->get_det().get_re_post();
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
        fadr_scroll->setMinimumHeight(80);
        this->fadr_label = new QLabel();
        QPushButton *adr_ed = new QPushButton("Изменить...");
        adr_ed->setMaximumWidth(100);
        adr_ed->setMinimumWidth(100);
        address tmp_adr = this->main_obj->get_adr();
        this->adr_label_set(this->fadr_label, &tmp_adr);
        fadr_scroll->setWidget(fadr_label);
            fadr_label->adjustSize();
        adr_l->addWidget(fadr_scroll);
            fadr_scroll->adjustSize();
        adr_l->addWidget(adr_ed);
        QObject::connect(adr_ed, SIGNAL(clicked()), this, SLOT(f_address_edit()));

// Области списков (телефоны и факсы)
        QBoxLayout *main_list_lay = new QBoxLayout(QBoxLayout::LeftToRight);
            QBoxLayout *telfax_lay = new QBoxLayout(QBoxLayout::LeftToRight);
            main_list_lay->addLayout(telfax_lay);
         QBoxLayout *tel_list = new QBoxLayout(QBoxLayout::TopToBottom);
         QBoxLayout *fax_list = new QBoxLayout(QBoxLayout::TopToBottom);
            QLabel *fax_lab = new QLabel();
                fax_lab->setText("Факсы: ");
            QLabel *tel_lab = new QLabel();
                tel_lab->setText("Телефоны: ");
          telfax_lay->addLayout(tel_list);
          telfax_lay->addLayout(fax_list);
            tel_list->addWidget(tel_lab);
            fax_list->addWidget(fax_lab);
//    QList<QString> list_tel;        // Список телефонов
      this->tellist = new QList<QString>(this->main_obj->get_det().get_tel_list());
      my_list_model *listmodtel = new my_list_model(this->tellist);
      my_list_view *viewtel = new my_list_view(&this->edited, this);
      viewtel->setFlow(QListView::TopToBottom);
      viewtel->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
      tel_list->addWidget(viewtel);
      viewtel->setModel(listmodtel);
      viewtel->setMaximumHeight(60);
//    QList<QString> list_fax;        // Список факсов
      this->faxlist = new QList<QString>(this->main_obj->get_det().get_fax_list());
      my_list_model *listmodfax = new my_list_model(this->faxlist);
      my_list_view *viewfax = new my_list_view(&this->edited, this);
      viewfax->setFlow(QListView::TopToBottom);
      viewfax->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        fax_list->addWidget(viewfax);
      viewfax->setModel(listmodfax);
      viewfax->setMaximumHeight(60);

//   QList<worker> workers_list Список работников
      this->workers_list = this->main_obj->get_workers_list();
      workers_data *work_model = new workers_data(&this->workers_list);
      workers_view *work_view = new workers_view(&this->edited, this);
      work_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
      work_view->setModel(work_model);
      work_view->setColumnWidth(0, 199);
      work_view->setColumnWidth(1, 199);
      work_view->setColumnWidth(2, 199);
      work_view->horizontalHeader()->setStretchLastSection(true);
      work_view->setMinimumHeight(180);

// Финальные кнопки
            QBoxLayout *push_list = new QBoxLayout(QBoxLayout::LeftToRight);
            QPushButton *push_ok = new QPushButton("Сохранить");
            QPushButton *push_cancel = new QPushButton("Не сохранять");
            QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
            QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(save_lab()));
            push_list->addWidget(push_ok);
            push_list->addWidget(push_cancel);            
// Расставляем виджеты
            QBoxLayout *edit_layout = new QBoxLayout(QBoxLayout::TopToBottom);

            edit_layout->addLayout(name_lay);
            edit_layout->addLayout(full_name_lay);
            edit_layout->addLayout(att_lay);
            edit_layout->addLayout(att_data_lay);
            edit_layout->addLayout(inn_lay);
            edit_layout->addLayout(dir_lay);
            edit_layout->addLayout(email_lay);
            edit_layout->addLayout(main_list_lay);
            edit_layout->addLayout(det_layout);
            edit_layout->addWidget(fadr_txt);
            edit_layout->addLayout(adr_l);
            edit_layout->addWidget(work_view);
            edit_layout->addStretch(0);
            edit_layout->addLayout(push_list);
            this->setLayout(edit_layout);
            this->setParent(parent);
}
void editor_laboratory::adr_label_set(QLabel* argl, address* arga)
{
    argl->setText(this->get_adr_str(arga));
    argl->adjustSize();
}
QString editor_laboratory::get_adr_str(address *arg)
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
address editor_laboratory::address_edit(address *arg)
{
    editor_address *aded = new editor_address(arg, this);
    address ret = *arg;
    if (aded->exec() == QDialog::Accepted){
     ret = aded->close_ret();
     delete aded;
     edited = true;
     return ret;
    }
    return ret;
}
laboratory *editor_laboratory::result()
{
    return this->main_obj;
}
bool editor_laboratory::is_edit()
{
    return edited;
}
void editor_laboratory::slot_att_edit()
{
    QString tmp1 = "Аттестат акредитации: ";
    QString tmp2 = this->main_obj->get_attestat();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 500);
    if (stred->exec() == QDialog::Accepted){
        this->main_obj->set_attestat(stred->result());
        this->att_label->setText(main_obj->get_attestat());
        this->att_label->adjustSize();
        edited = true;
    }
    delete stred;
}
void editor_laboratory::slot_name_edit()
{
    QString tmp1 = "Краткое название: ";
    QString tmp2 = this->main_obj->get_name();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 600);
    if (stred->exec() == QDialog::Accepted){
        this->main_obj->set_name(stred->result());
        this->name_label->setText(main_obj->get_name());
        this->name_label->adjustSize();
        edited = true;
    }
    delete stred;
}
void editor_laboratory::slot_full_name_edit()
{
    QString tmp1 = "Полное название: ";
    QString tmp2 = main_obj->get_full_name();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 500);
    if (stred->exec() == QDialog::Accepted){
        this->main_obj->set_full_name(stred->result());
        this->full_name_label->setText(main_obj->get_full_name());
        this->full_name_label->adjustSize();
        edited = true;
    }
    delete stred;
}
void editor_laboratory::slot_email_edit()
{
    QString tmp1 = "Email: ";
    QString tmp2 = main_obj->get_email();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_obj->set_email(stred->result());
        this->email_label->setText(main_obj->get_email());
        this->email_label->adjustSize();
        edited = true;
    }
    delete stred;
}
void editor_laboratory::f_address_edit()
{
    address tmp1 = main_obj->get_adr();
    address *tmp = new address();
    tmp = &tmp1;
    tmp1 = this->address_edit(tmp);
    main_obj->set_adr(tmp);
    this->adr_label_set(fadr_label, tmp);
}
void editor_laboratory::p_address_edit()
{
    address tmp1 = main_obj->get_padr();
    address *tmp = new address();
    tmp = &tmp1;
    tmp1 = this->address_edit(tmp);
    main_obj->set_padr(tmp);
    this->adr_label_set(padr_label, tmp);
}
void editor_laboratory::u_address_edit()
{
    address tmp1 = main_obj->get_uadr();
    address *tmp = new address();
    tmp = &tmp1;
    tmp1 = this->address_edit(tmp);
    main_obj->set_uadr(tmp);
    this->adr_label_set(uadr_label, tmp);
}
void editor_laboratory::inn_edit()
{
    QString tmp1 = "ИНН: ";
    int_editor *ined = new int_editor(this->main_obj->get_det().get_inn(), &tmp1, 13);
    if (ined->exec() == QDialog::Accepted){
        this->main_obj->set_inn(ined->result());
        this->inn_label->setText(tmp1.setNum(main_obj->get_det().get_inn()));
        this->inn_label->adjustSize();
      edited = true;
    }
    delete ined;
}
void editor_laboratory::dir_edit()
{
    QString tmp1 = "Руководитель: ";
    QString tmp2 = "Должность: ";
    QString tmp3 = "Имя (Ф.И.О): ";
    pair_editor *dired = new pair_editor(this->main_obj->get_det().get_dir(), &tmp1, &tmp2, &tmp3, 300, 300);
    if (dired->exec() == QDialog::Accepted){
        this->main_obj->set_dir(dired->result());
        dir_n_label->setText(main_obj->get_det().get_dir().second);
        dir_p_label->setText(main_obj->get_det().get_dir().first);
        dir_n_label->adjustSize();
        dir_p_label->adjustSize();
      edited = true;
    }
    delete dired;
}
void editor_laboratory::save_lab()
{
    this->main_obj->set_workers_list(this->workers_list);
    this->main_obj->set_tel_list(*(this->tellist));
    this->main_obj->set_fax_list(*(this->faxlist));
    QDomDocument openlab = this->main_obj->make_xml();
    QFile labf("./data/lab.dat");
    if (labf.open(QIODevice::WriteOnly)){
        QTextStream stream(&labf);
        openlab.save(stream, 1);
        labf.close();
    } else {
        QMessageBox::information(nullptr, "Отладка", "Проблемы с сохранением данных о лаборатории");
    }
    emit accept();
}
void editor_laboratory::att_data_edit()
{
    QString tmp1 = "Дата аттестата: ";
    QDate tmp2 = this->main_obj->get_att_date();
    my_date_edit *ded = new my_date_edit(tmp2, tmp1);
    if (ded->exec() == QDialog::Accepted){
        this->main_obj->set_att_date(ded->result());
        this->att_data_label->setText(this->main_obj->get_att_date().toString("dd.MMMM.yyyy"));
        this->att_data_label->adjustSize();
    }
    delete ded;
}
