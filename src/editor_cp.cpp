#include "editor_cp.h"

editor_cp::~editor_cp()
{
    delete name_label;
    delete adr_label;
    delete sh_label;
    delete volt_label;
    delete _tr_label;
    delete _tr_scroll;
    delete adr_scroll;
    delete max_time_list;
    delete min_time_list;
    delete apprat;
}
editor_cp::editor_cp(obj *arg, QWidget *parent) : QDialog(parent)
{
    this->edited = false;
    this->main_data = arg;
    this->setWindowTitle("Центр притния");
    this->setWindowIcon(QIcon(":/pic/images/KlogoS.png"));
    this->setMinimumWidth(900);
//QString name - Название объекта
    this->name_label = new QLabel;
    name_label->setText(this->main_data->get_name());
    QLabel *name_cp = new QLabel();
    name_cp->setText("<b>Центр питания: </b>");
    QPushButton *name_ed = new QPushButton("Изменить...");
    name_ed->setMaximumWidth(100);
    name_ed->setMinimumWidth(100);
    QObject::connect(name_ed, SIGNAL(clicked()), this, SLOT(slot_name_edit()));
    QBoxLayout *name_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    name_lay->addWidget(name_cp);
    name_lay->addWidget(this->name_label);
    name_lay->addWidget(name_ed);
//int voltage;                             // Напряжение номинальное
    this->volt_label = new QLabel;
    QString tmps;
    volt_label->setText(tmps.setNum(this->main_data->get_voltage()));
    QLabel *volt_cp = new QLabel();
    volt_cp->setText("<b>Номинальное напряжение: </b>");
    QPushButton *volt_ed = new QPushButton("Изменить...");
    volt_ed->setMaximumWidth(100);
    volt_ed->setMinimumWidth(100);
    QObject::connect(volt_ed, SIGNAL(clicked()), this, SLOT(slot_volt_edit()));
    QBoxLayout *volt_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    volt_lay->addWidget(volt_cp);
    volt_lay->addWidget(this->volt_label);
    volt_lay->addWidget(volt_ed);
//address adr;                             // Адрес объекта
    QLabel *adr_txt = new QLabel();
    adr_txt->setText("<H4><CENTER>Адрес центра питания: <CENTER></H4>");
    QBoxLayout *adr_l = new QBoxLayout(QBoxLayout::LeftToRight);
    this->adr_scroll = new QScrollArea();
    adr_scroll->setFrameStyle(QFrame::NoFrame);
    adr_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    adr_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    adr_scroll->widgetResizable();
    this->adr_label = new QLabel();
    QPushButton *adr_ed = new QPushButton("Изменить...");
    adr_ed->setMaximumWidth(100);
    adr_ed->setMinimumWidth(100);
    address tmp_adr = this->main_data->get_adr();
    this->adr_label_set(this->adr_label, &tmp_adr);
    adr_scroll->setWidget(adr_label);
        adr_label->adjustSize();
    adr_l->addWidget(adr_scroll);
        adr_scroll->adjustSize();
    adr_l->addWidget(adr_ed);
    QObject::connect(adr_ed, SIGNAL(clicked()), this, SLOT(slot_address_edit()));
//Трансформатор;                             // Трансформатор
    QLabel *tr_txt = new QLabel();
    tr_txt->setText("<H4><CENTER>Трансформатор: <CENTER></H4>");
    QBoxLayout *tr_l = new QBoxLayout(QBoxLayout::LeftToRight);
    _tr_scroll = new QScrollArea();
    _tr_scroll->setFrameStyle(QFrame::NoFrame);
    _tr_scroll->setMinimumHeight(140);
    _tr_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    _tr_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    _tr_scroll->widgetResizable();
    _tr_label = new QLabel();
    QPushButton *tr_ed = new QPushButton("Изменить...");
    tr_ed->setMaximumWidth(100);
    tr_ed->setMinimumWidth(100);
    transformator tmp_tr = this->main_data->get_tr();
    this->tr_label_set(_tr_label, &tmp_tr);
    _tr_scroll->setWidget(_tr_label);
        _tr_label->adjustSize();
    tr_l->addWidget(_tr_scroll);
        _tr_scroll->adjustSize();
    tr_l->addWidget(tr_ed);
    QObject::connect(tr_ed, SIGNAL(clicked()), this, SLOT(slot_tr_edit()));
//QString sh; // Строковой параметр СШ
    this->sh_label = new QLabel;
    sh_label->setText(this->main_data->get_sh());
    QLabel *sh_cp = new QLabel();
    sh_cp->setText("<b>параметр СШ: </b>");
    QPushButton *sh_ed = new QPushButton("Изменить...");
    sh_ed->setMaximumWidth(100);
    sh_ed->setMinimumWidth(100);
    QObject::connect(sh_ed, SIGNAL(clicked()), this, SLOT(slot_sh_edit()));
    QBoxLayout *sh_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    sh_lay->addWidget(sh_cp);
    sh_lay->addWidget(this->sh_label);
    sh_lay->addWidget(sh_ed);

// Области списков (максимальные и минимаотные диапазоны)
        QBoxLayout *main_time_lay = new QBoxLayout(QBoxLayout::LeftToRight);
            QBoxLayout *time_lay = new QBoxLayout(QBoxLayout::LeftToRight);
            main_time_lay->addLayout(time_lay);
         QBoxLayout *max_list = new QBoxLayout(QBoxLayout::TopToBottom);
         QBoxLayout *min_list = new QBoxLayout(QBoxLayout::TopToBottom);
            QLabel *min_lab = new QLabel();
                min_lab->setText("<b>Диапазоны максимума: </b>");
            QLabel *max_lab = new QLabel();
                max_lab->setText("<b>Диапазоны минимума: </b>");
          time_lay->addLayout(max_list);
          time_lay->addLayout(min_list);
            max_list->addWidget(max_lab);
            min_list->addWidget(min_lab);
    //QList<QPair<QTime, QTime>> max_time;     // Список периодов максимальной нагрузки
    this->max_time_list = new QList<QPair<QTime, QTime>>(this->main_data->get_maxt_list());
    my_time_model *max_modtel = new my_time_model(this->max_time_list);
    my_time_view *view_max = new my_time_view(&this->edited, this);
    view_max->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    max_list->addWidget(view_max);
    view_max->setModel(max_modtel);
    view_max->setColumnWidth(0, 150);
    view_max->horizontalHeader()->setStretchLastSection(true);
    view_max->setMidLineWidth(300);
    view_max->setMaximumHeight(120);
    view_max->setMinimumHeight(120);
    //QList<QPair<QTime, QTime>> min_time;     // Список периодов минимальной нагрузки
    this->min_time_list = new QList<QPair<QTime, QTime>>(this->main_data->get_mint_list());
    my_time_model *min_modtel = new my_time_model(this->min_time_list);
    my_time_view *view_min = new my_time_view(&this->edited, this);
    view_min->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    min_list->addWidget(view_min);
    view_min->setModel(min_modtel);
    view_min->setColumnWidth(0, 150);
    view_min->horizontalHeader()->setStretchLastSection(true);
    view_min->setMaximumHeight(120);
    view_min->setMinimumHeight(120);
    // QList<apparaturs> appr;                  // Список приборов
    QLabel *app_lbl = new QLabel();
        app_lbl->setText("<b>Приборы:</b>");
    QLayout *app_lst = new QBoxLayout(QBoxLayout::TopToBottom);
    apprat = new QList<apparaturs*>(this->main_data->get_app_list());
    app_data_model *app_mod = new app_data_model(this->apprat);
    app_data_view *app_view = new app_data_view(&this->edited, this);
    app_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    app_lst->addWidget(app_lbl);
    app_lst->addWidget(app_view);
    app_view->setModel(app_mod);
    app_view->setMinimumHeight(180);
    app_view->setColumnWidth(0, 203);
    app_view->setColumnWidth(1, 203);
    app_view->horizontalHeader()->setStretchLastSection(true);
        //QList<main_protocol*> p_list;            // Список протоколов на объекте

// Финальные кнопки
    QBoxLayout *push_list = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton *push_ok = new QPushButton("Сохранить");
    QPushButton *push_cancel = new QPushButton("Не сохранять");
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(slot_save_cp()));
    push_list->addWidget(push_ok);
    push_list->addWidget(push_cancel);
// Расставляем виджеты
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    main_lay->addLayout(name_lay);
    main_lay->addLayout(volt_lay);
    main_lay->addWidget(adr_txt);
    main_lay->addLayout(adr_l);
    main_lay->addWidget(tr_txt);
    main_lay->addLayout(tr_l);
    main_lay->addLayout(sh_lay);
    main_lay->addLayout(app_lst);
    main_lay->addLayout(main_time_lay);
    main_lay->addLayout(push_list);
    this->setLayout(main_lay);
}
bool editor_cp::is_edit()
{
    return this->edited;
}
void editor_cp::slot_name_edit()
{
    QString tmp1 = "Наименование ЦП: ";
    QString tmp2 = this->main_data->get_name();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_data->set_name(stred->result());
        this->name_label->setText(main_data->get_name());
        this->name_label->adjustSize();
      this->edited = true;
    }
    delete stred;
}
void editor_cp::slot_save_cp()
{
    if (this->main_data->get_name() != "") {
        this->main_data->add_max_list(this->max_time_list);
        this->main_data->add_min_list(this->min_time_list);
        this->main_data->set_app_list(this->apprat);
        this->main_data->time_ktp();
        emit accept();
    }
    else {
        QMessageBox *tmoer = new QMessageBox();
        tmoer->setWindowTitle("Внимание!");
        tmoer->setText("Нельзя создавать ЦП совсем без имени");
        tmoer->exec();
        delete tmoer;
    }
}
void editor_cp::slot_volt_edit()
{
    QString tmp1 = "Напряжение: ";
    int_editor *ined = new int_editor(this->main_data->get_voltage(), &tmp1, 7);
    if (ined->exec() == QDialog::Accepted){
        this->main_data->set_voltage(ined->result());
        this->volt_label->setText(tmp1.setNum(main_data->get_voltage()));
        this->volt_label->adjustSize();
      this->edited = true;
    }
    delete ined;
}
void editor_cp::slot_address_edit()
{
    address tmp1 = main_data->get_adr();
    address *tmpa = new address();
    tmpa = &tmp1;
    editor_address *aded = new editor_address(tmpa, this);
    if (aded->exec() == QDialog::Accepted){
        tmp1 = aded->close_ret();
        main_data->set_adr(tmp1);
        this->adr_label_set(this->adr_label, tmpa);
        this->edited = true;
    }
    delete aded;
}
void editor_cp::slot_sh_edit()
{
    QString tmp1 = "Параметр СШ: ";
    QString tmp2 = this->main_data->get_sh();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_data->set_sh(stred->result());
        this->sh_label->setText(main_data->get_sh());
        this->sh_label->adjustSize();
      this->edited = true;
    }
    delete stred;
}
void editor_cp::slot_tr_edit()
{
    transformator tmp1 = main_data->get_tr();
    transformator *tmpa = new transformator();
    tmpa = &tmp1;
    editor_trans *tred = new editor_trans(tmpa, this);
    if (tred->exec() == QDialog::Accepted){
        tmp1 = tred->close_ret();
        main_data->set_tr(tmp1);
        this->tr_label_set(_tr_label, tmpa);
        this->edited = true;
    }
    delete tred;
}
void editor_cp::tr_label_set(QLabel* argl, transformator* arga)
{
    argl->setText(this->get_tr_str(arga));
    argl->adjustSize();
}
void editor_cp::adr_label_set(QLabel *argl, address *arga)
{
   argl->setText(this->get_adr_str(arga));
   argl->adjustSize();
}
QString editor_cp::get_adr_str(address *arg)
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
QString editor_cp::get_tr_str(transformator *arg)
{
    QString tmp_str;
//Тип: 								ЗНОЛ-НТЗ-35.
    tmp_str.append("<b>Тип: </b>");
    tmp_str.append(arg->get_type());
//Заводской №: 						07194, 07427, 07196.
    tmp_str.append("&nbsp; &nbsp; &nbsp;<b>Заводской №: </b>");
    tmp_str.append(arg->get_mnom());
//Класс точности:						0,5
    tmp_str.append("&nbsp; &nbsp; &nbsp;<b>Класс точности: </b>");
    tmp_str.append(arg->get_cls());
    tmp_str.append("<br>");
//Номинальная полная мощность нагрузки
//Sн для указанного класса точности, ВА:		30, 30, 30
    tmp_str.append("<b>Номинальная полная мощность нагрузки <br> Sн для указанного класса точности, ВА: </b>");
    tmp_str.append(arg->get_nom_power());
    tmp_str.append("<br>");
//Схема соединения обмоток (усл. обозначение):	1/1/1-0-0
    tmp_str.append("<b>Схема соединения обмоток (усл. обозначение): </b>");
    tmp_str.append(arg->get_obm());
    tmp_str.append("<br>");
//Номинальное напряжение
//основной вторичной обмотки U2 ном, В:		100√3
    tmp_str.append("<b>Номинальное напряжение основной <br> вторичной обмотки U2 ном, В: </b>");
    tmp_str.append(arg->get_nom_u_2());
    tmp_str.append("<br>");
//Номинальное напряжение
//первичной обмотки U1 ном, кВ:				35√3
    tmp_str.append("<b>Номинальное напряжение основной <br> вторичной обмотки U1 ном, кВ: </b>");
    tmp_str.append(arg->get_nom_u_1());
    tmp_str.append("<br>");
    if (1 == arg->test_f()){
        tmp_str.append("Однофазный");
    } else if (3 == arg->test_f()) {
        tmp_str.append("Трехфазный");
    }
 return tmp_str;
}
