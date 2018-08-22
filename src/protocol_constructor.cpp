#include "protocol_constructor.h"

protocol_constructor::protocol_constructor(protocol* act_prot, QWidget* par) : QDialog(par)
{
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Мастер подготовки протокола");
    this->setMinimumWidth(900);
    laboratory& tmplab = laboratory::getInstance();
   // padapt(new prot_act_adapter());
    actual_prot = act_prot;
    varad = new var_adapter(actual_prot->get_parent());
    vartype = new type_adapter();
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* combo_type_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* type_lab = new QLabel();
// Тип протокола
    type_lab->setText("Тип протокола: ");
    select_type = new QComboBox();
    const_loader& tmpl = const_loader::getInstance();
    model_type = new p_types_model();
    model_view = new p_types_view();
    model_view->setModel(model_type);
// Дата
    QLabel* dat_lab = new QLabel();
    dat_lab->setText("Дата формирования: ");
    dat_edit = new QDateEdit();
    dat_edit->setDate(QDate::currentDate());
// Выбор инженера
    QLabel* ing_lab = new QLabel();
    ing_lab->setText("Инженер: ");
    select_engineer = new QComboBox();
    QList<worker> tmpwl = tmplab.get_workers_list();
    QString tmps{""};
    for (auto it : tmpwl){
        if (it.get_name() != ""){
            tmps += it.get_name().left(1) + ". ";
        }
        if (it.get_fname() != ""){
            tmps += it.get_fname().left(1) + ". ";
        }
        tmps += it.get_surname();
        select_engineer->addItem(tmps, QVariant::fromValue(it));
        tmps = "";
    }
    padapt->set_worker(select_engineer->currentData().value<worker>());
// QList<apparaturs> appr;                  // Список приборов
    QLabel *app_lbl = new QLabel();
    app_lbl->setText("<b>Приборы:</b>");
    apprat = new QList<apparaturs*>(actual_prot->get_parent()->get_app_list());
    app_data_model *app_mod = new app_data_model(apprat);
    app_view = new app_data_view(this);
    QPushButton* add_app = new QPushButton("Добавить прибор");
    QObject::connect(add_app, SIGNAL(clicked()), app_view, SLOT(slot_add()));
    QBoxLayout* head_app_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    head_app_lay->addWidget(app_lbl);
    head_app_lay->addWidget(add_app);
    app_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    app_view->setModel(app_mod);
    app_view->setMinimumHeight(100);
    app_view->setColumnWidth(0, 203);
    app_view->setColumnWidth(1, 203);
    app_view->horizontalHeader()->setStretchLastSection(true);
// ------
    QBoxLayout* head_list_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* cns_lab = new QLabel();
    cns_lab->setText("<b>Наборы констант:</b>");
    QPushButton* add_cns = new QPushButton("Добавить набор");
    QObject::connect(add_cns, SIGNAL(clicked()), model_view, SLOT(slot_add()));
    head_list_lay->addWidget(cns_lab);
    head_list_lay->addWidget(add_cns);
    model_view->setMinimumHeight(100);
    model_view->setColumnWidth(0, 200);
    model_view->horizontalHeader()->setStretchLastSection(true);
    types = tmpl.get_idv_list();
    if (!types.empty()){
        varconst = new const_adapter(types.front().second);
    } else {
        QMessageBox::information(nullptr, "Отладка", "Нет не одного доступного типа протокола");
        varconst = new const_adapter("");
    }
    for (auto it : types){
        select_type->addItem(it.first, it.second);
    }
    QObject::connect(select_type, SIGNAL(currentTextChanged(QString)), this, SLOT(slot_change_type()));
    QBoxLayout* table_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* type_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* app_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    table_lay->addLayout(type_lay);
    table_lay->addLayout(app_lay);
    app_lay->addLayout(head_app_lay);
    app_lay->addWidget(app_view);
    type_lay->addLayout(head_list_lay);
    type_lay->addWidget(model_view);

    combo_type_lay->addWidget(type_lab);
    combo_type_lay->addWidget(select_type);
    combo_type_lay->addWidget(dat_lab);
    combo_type_lay->addWidget(dat_edit);
    combo_type_lay->addWidget(ing_lab);
    combo_type_lay->addWidget(select_engineer);
    QBoxLayout* buttons_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton* but_test = new QPushButton("Проверить");
    QObject::connect(but_test, SIGNAL(clicked()), this, SLOT(slot_test()));
    QPushButton* but_create = new QPushButton("Сформировать");
    QObject::connect(but_create, SIGNAL(clicked()), this, SLOT(slot_create()));
    QPushButton* but_cancel = new QPushButton("Отмена");
    QObject::connect(but_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    buttons_lay->addWidget(but_create);
    buttons_lay->addWidget(but_cancel);
    main_lay->addLayout(combo_type_lay);
    main_lay->addLayout(table_lay);
    main_lay->addWidget(but_test);


    main_lay->addLayout(buttons_lay);
    this->setLayout(main_lay);
}
protocol_constructor::~protocol_constructor()
{
   // delete varad;
    delete varconst;
    delete vartype;
    delete dat_edit;
}
void protocol_constructor::slot_change_type()
{
    delete varconst;
    varconst = new const_adapter(select_type->currentData().toString());
    if (is_tested) slot_test();
}
QString protocol_constructor::get_html()
{
    const_loader& tmpcl = const_loader::getInstance();
    const_obj tmpco = tmpcl.get_obj(select_type->currentData().toString());
     QString fname = "./data/prt_" + tmpco.get_vname() +".html";
     QFile con_f(fname);
     if (!con_f.exists()){
         con_f.open(QIODevice::WriteOnly);
         con_f.close();
     }
     QByteArray open_html;
     if (con_f.open(QIODevice::ReadOnly  | QIODevice::Text)){
         open_html = con_f.readAll();
         con_f.close();
     } else {
         QMessageBox::information(nullptr, "Отладка", "Не открывается файл с основным текстом протокола в HTML для чтения");
     }
     return  QString(open_html);
}
void protocol_constructor::parser_first(QString& argx)
{
    int pos_beg{0};
    std::string arg{argx.toStdString()};
    std::vector<std::pair<std::string, std::string> > parsres;
    std::string main_teg;
    std::vector<std::string> tegs{"type", "message", "vname", "style"};
    std::pair<int, int> reg = std::make_pair(0, 0);
    std::string t_var, m_var, v_var, s_var;
    std::string ins_str;
    std::vector<QString> type_teg{"_prot_type", "_parent_var", "_const_type", "_prot_con", "_set_adapt_var", "_ask_obj"};
    for (auto itx : type_teg){
        pos_beg = 0;
        do{
            reg = my_fnc::serch_teg(arg, itx.toStdString(), pos_beg);
            if (reg.second != -1 && reg.first != -1){
                main_teg = arg.substr(static_cast<size_t>(reg.first), static_cast<size_t>(reg.second - reg.first + 1));
                parsres = my_fnc::parse_teg(main_teg, tegs);
                auto res_t = std::find_if(parsres.begin(), parsres.end(), [](const std::pair<std::string, std::string>& arr)->bool{return arr.first == "type";});
                if (res_t == parsres.end()){
                    pos_beg += main_teg.size();
                    continue;
                }
                t_var = res_t->second;
                auto res_m =std::find_if(parsres.begin(), parsres.end(), [](const std::pair<std::string, std::string>& arr)->bool{return arr.first == "message";});
                if (res_m == parsres.end()){
                    m_var = "";
                } else m_var = res_m->second;
                auto res_v =std::find_if(parsres.begin(), parsres.end(), [](const std::pair<std::string, std::string>& arr)->bool{return arr.first == "vname";});
                if (res_v == parsres.end()){
                    pos_beg += main_teg.size();
                    continue;
                } v_var = res_v->second;
                auto res_s =std::find_if(parsres.begin(), parsres.end(), [](const std::pair<std::string, std::string>& arr)->bool{return arr.first == "style";});
                if (res_s == parsres.end()){
                    s_var = "";
                } else s_var = res_s->second;
                if (itx == "_set_adapt_var"){
                    var_set.append(std::make_tuple(itx, QString(t_var.c_str()), QString(m_var.c_str()), QString(v_var.c_str())));
                    pos_beg = reg.second;
                    continue;
                } else if (itx == "_ask_obj") {
                    ask_set.append(std::make_tuple(itx, QString(t_var.c_str()), QString(m_var.c_str()), QString(v_var.c_str())));
                    pos_beg = reg.second;
                    continue;
                } else {
                    ins_str = this->use_adapt(std::make_tuple(itx.toStdString(), t_var, m_var, v_var, s_var)).toStdString();
                    if (ins_str != "NULL"){
                        arg.erase(static_cast<size_t>(reg.first), static_cast<size_t>(reg.second - reg.first + 1));
                        arg.insert(static_cast<size_t>(reg.first), ins_str);
                        pos_beg = reg.first + static_cast<int>(ins_str.size()) - 1;
                    } else {
                        ask_set.append(std::make_tuple(itx, QString(t_var.c_str()), QString(m_var.c_str()), QString(v_var.c_str())));
                        pos_beg = reg.second;
                    }
                }
            }
        } while (reg.first != -1);
    }
    argx = std::move(arg.c_str());
}
void protocol_constructor::prepare(QString &argx)
{

}
                                        // тип адаптера, type, message, varname, style
QString protocol_constructor::use_adapt(const std::tuple<std::string, std::string, std::string, std::string , std::string>& arg)
{
    if (std::get<0>(arg) == "_prot_type"){
        return varconst->get_var(QString(std::get<3>(arg).c_str()));
    }
    if (std::get<0>(arg) == "_prot_con"){
        return padapt->get_var(QString(std::get<3>(arg).c_str()), QString(std::get<4>(arg).c_str()));
    }
    if (std::get<0>(arg) == "_parent_var"){
        return varad->get_var(QString(std::get<1>(arg).c_str()), QString(std::get<3>(arg).c_str()), QString(std::get<4>(arg).c_str()));
    }
    if (std::get<0>(arg) == "_const_type"){
        return  vartype->get_var(QString(std::get<1>(arg).c_str()), QString(std::get<3>(arg).c_str()));
    }
    return "NULL";
}
void protocol_constructor::slot_test()
{
    is_tested = true;
    create_varlist();
    QString html_text = get_html().remove('\n');
    prepare(html_text);
    parser_first(html_text);

    QWebEngineView* tmpw = new QWebEngineView(nullptr);
    tmpw->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    tmpw->setMinimumWidth(700);
    tmpw->setWindowTitle("Тестовый вывод протокола");
    tmpw->setHtml(html_text);
    tmpw->show();

  //  QTextDocument tdd;
  //  tdd.setHtml(get_html());
   // int f = tdd.blockCount();

  //  varad;     // Адаптер для получения данных у родителей протокола
  //  varconst;// Адаптер для получения констант зависящих от типа протокола
  //  vartype;  // Адаптер для получения констант зависящих от выбранных коллекций типов
  //
}
void protocol_constructor::create_varlist()
{
    padapt->set_current_data(dat_edit->date());
    padapt->set_worker(select_engineer->currentData().value<worker>());
}
void protocol_constructor::slot_create()
{
    emit accept();
}
