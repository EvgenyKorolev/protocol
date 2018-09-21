#include "protocol_constructor.h"
#include "p_types_model.h"
#include "p_types_view.h"
#include "const_loader.h"
#include "var_adapter.h"
#include "const_adapter.h"
#include "protocol.h"
#include "type_in_direct.h"
#include "my_function.h"
#include "app_data_model.h"
#include "app_data_view.h"
#include "protocol_list_load.h"
#include "ask_editor.h"
#include "textedit.h"
#include <QObject>
#include <QString>
#include <QIcon>
#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QHeaderView>
#include <QPair>
#include <QTextDocument>
#include <QRegExp>
#include <QDateEdit>
#include <QGridLayout>
#include <QLineEdit>
#include <QEventLoop>
#include <algorithm>
#include <utility>

#include <QWebEngineScriptCollection>
#include <QQuickWebEngineScript>
#include <QWebEngineView>
#include <QWebEnginePage>
protocol_constructor::protocol_constructor(protocol* act_prot, QWidget* par) : QDialog(par)
{
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Мастер подготовки протокола");
    this->setMinimumWidth(900);
    laboratory& tmplab = laboratory::getInstance();
   // padapt(new prot_act_adapter());
    actual_prot = act_prot;
    varad = new var_adapter(actual_prot->get_parent());

    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QGridLayout* combo_type_lay = new QGridLayout();
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
// Номер
   QLabel* ent_num_lab = new QLabel();
   ent_num_lab->setText("Номер протокола: ");
   enter_number = new QLineEdit();
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

    combo_type_lay->setColumnMinimumWidth(1, 150);
    combo_type_lay->setColumnMinimumWidth(2, 150);
    combo_type_lay->setColumnMinimumWidth(3, 150);
    combo_type_lay->setColumnMinimumWidth(4, 150);
    combo_type_lay->setColumnMinimumWidth(5, 150);
    combo_type_lay->setColumnMinimumWidth(6, 150);
    combo_type_lay->addWidget(type_lab, 1, 1);
    combo_type_lay->addWidget(select_type, 1, 2);
    combo_type_lay->addWidget(dat_lab, 1, 3);
    combo_type_lay->addWidget(dat_edit, 1, 4);
    combo_type_lay->addWidget(ing_lab, 1, 5);
    combo_type_lay->addWidget(select_engineer, 1, 6);
    combo_type_lay->addWidget(ent_num_lab, 2, 1);
    combo_type_lay->addWidget(enter_number, 2, 2);
    QBoxLayout* buttons_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton* but_test = new QPushButton("Сформировать протокол");
    QObject::connect(but_test, SIGNAL(clicked()), this, SLOT(slot_test()));
    QPushButton* but_create = new QPushButton("Сохранить");
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
void protocol_constructor::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    emit rejected();
}
protocol_constructor::~protocol_constructor()
{
    delete varconst;
    delete dat_edit;
    actual_prot = nullptr;
    delete actual_prot;
}
void protocol_constructor::slot_change_type()
{
    create_varlist();
    if (is_tested) slot_test();
}
QString protocol_constructor::get_html()
{
    const_loader& tmpcl = const_loader::getInstance();
    const_obj tmpco = tmpcl.get_obj(select_type->currentData().toString());
    settings& tmps = settings::GetInstance();
     QString fname = tmps.get_data_patch() + tmps.get_data_dir() + "/prt_" + tmpco.get_vname() +".html";
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
void protocol_constructor::prepare(QString &argx)
{
    std::string arg{argx.toStdString()};
    replace_tags(arg, ask_p::parse);
    if (ask_set.size() != 0){
        ask_editor* ask = new ask_editor(ask_set);
        if (ask->exec() == QDialog::Accepted){
            ask_set = *ask->result().release();
            replace_tags(arg, ask_p::ask);
        }
    }
    argx = std::move(arg.c_str());
}
void protocol_constructor::replace_tags(std::string& arg, ask_p arg2)
{
    int pos_beg{0};
    std::string main_teg;
    std::vector<std::pair<std::string, std::string> > parsres;
    std::string t_var, m_var, v_var, s_var;
    std::string ins_str;
    std::pair<int, int> reg{std::make_pair(0, 0)};
    std::vector<std::string> tegs{"type", "message", "vname", "style"};
    std::vector<QString> type_teg{"_prot_type", "_parent_var", "_const_type", "_prot_con", "_set_adapt_var", "_ask_obj"};
    for (auto itx : type_teg){
        pos_beg = 0;
        do{
            reg = my_fnc::serch_teg(arg, itx.toStdString(), pos_beg);
            if (reg.second != -1 && reg.first != -1){
                main_teg = arg.substr(static_cast<size_t>(reg.first), static_cast<size_t>(reg.second - reg.first + 1));
                parsres = my_fnc::parse_teg(main_teg, tegs);
                auto res_t = std::find_if(parsres.begin(), parsres.end(), [](const std::pair<std::string, std::string>& arr)->bool{
                    return arr.first == "type";});
                if (res_t == parsres.end()){
                    pos_beg += main_teg.size();
                    continue;
                }
                t_var = res_t->second;
                auto res_m =std::find_if(parsres.begin(), parsres.end(), [](const std::pair<std::string, std::string>& arr)->bool{
                    return arr.first == "message";});
                if (res_m == parsres.end()){
                    m_var = "";
                } else m_var = res_m->second;
                auto res_v =std::find_if(parsres.begin(), parsres.end(), [](const std::pair<std::string, std::string>& arr)->bool{
                    return arr.first == "vname";});
                if (res_v == parsres.end()){
                    pos_beg += main_teg.size();
                    continue;
                } v_var = res_v->second;
                auto res_s =std::find_if(parsres.begin(), parsres.end(), [](const std::pair<std::string, std::string>& arr)->bool{
                    return arr.first == "style";});
                if (res_s == parsres.end()){
                    s_var = "";
                } else s_var = res_s->second;
                if (arg2 == ask_p::parse){
                    ins_str = this->use_adapt(std::make_tuple(itx.toStdString(), t_var, m_var, v_var, s_var)).toStdString();
                    if (ins_str != "NULL"){
                        arg.erase(static_cast<size_t>(reg.first), static_cast<size_t>(reg.second - reg.first + 1));
                        arg.insert(static_cast<size_t>(reg.first), ins_str);
                        pos_beg = reg.first + static_cast<int>(ins_str.size()) - 1;
                    } else {
                        if (ask_set.end() == std::find_if(ask_set.begin(), ask_set.end(), [&itx, &t_var, &v_var](const std::tuple<QString, QString, QString, QString, QString>& pred)->bool{
                                                          return ((std::get<1>(pred) == QString(t_var.c_str())) &&
                                                                  (std::get<3>(pred) == QString(v_var.c_str())) &&
                                                                  ((std::get<0>(pred) == itx)));})){
                            ask_set.append(std::make_tuple(itx, QString(t_var.c_str()), QString(m_var.c_str()), QString(v_var.c_str()), ""));
                        }
                        pos_beg = reg.second;
                    }
                } else {
                    ins_str = this->use_ask_adapt(std::make_tuple(itx.toStdString(), t_var, m_var, v_var, s_var)).toStdString();
                    arg.erase(static_cast<size_t>(reg.first), static_cast<size_t>(reg.second - reg.first + 1));
                    arg.insert(static_cast<size_t>(reg.first), ins_str);
                    pos_beg = reg.first + static_cast<int>(ins_str.size()) - 1;
                }
              } else ++pos_beg;
        } while (reg.first != -1);
       }
}
                                        //             тип адаптера,   type,       message,      varname,      style
QString protocol_constructor::use_adapt(const std::tuple<std::string, std::string, std::string, std::string , std::string>& arg)
{
    if (std::get<0>(arg) == "_ask_obj"){
        return  vartype->get_var(QString(std::get<1>(arg).c_str()), QString(std::get<3>(arg).c_str()));
    }
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
QString protocol_constructor::use_ask_adapt(const std::tuple<std::string, std::string, std::string, std::string, std::string>& arg)
{
    auto it = std::find_if(ask_set.begin(), ask_set.end(), [&arg](const std::tuple<QString, QString, QString, QString, QString>& pred)->bool{
        return (std::get<0>(arg) == std::get<0>(pred).toStdString() &&
                std::get<1>(arg) == std::get<1>(pred).toStdString() &&
                std::get<2>(arg) == std::get<2>(pred).toStdString() &&
                std::get<3>(arg) == std::get<3>(pred).toStdString());});
    if (ask_set.end() != it){
        return  std::get<4>(*it);
    }
    return "";
}
void protocol_constructor::slot_test()
{
    QString html_text = get_html().remove('\n');
    QString html_text2{""};
    create_varlist();
    prepare(html_text);
    is_tested = true;
//    QQuickWebEngineScript wjs;
//    wjs.setSourceCode(html_text);
//    html_text2 = wjs.toString();
//    QWebEngineView* ww = new QWebEngineView();
//    ww->setHtml(html_text);
    QWebEnginePage* pg = new QWebEnginePage();
    pg->setHtml(html_text);
    QEventLoop loop0;
    connect(pg, SIGNAL(loadFinished(bool)), &loop0, SLOT(quit()));
    loop0.exec();
    QList<QWebEngineScript> jvs(pg->scripts().toList());
    for (auto its : jvs){
        pg->runJavaScript(its.sourceCode());
    }


    //pg->save("result/tt.html");
    //QWebEngineCallback<const QString&> cb(html_text2);
    //pg->toHtml(cb);
    //ww->show();
    //delete ww;


    actual_prot->set_date(dat_edit->date());
    actual_prot->set_type(select_type->currentData().toString());
    actual_prot->set_number(enter_number->text());
    prt_fun::add_prt(actual_prot->get_dr(), actual_prot, html_text, html_text2);
    ret_str ret;
    TextEdit *prtedit = new TextEdit(&ret, this);
    prtedit->load_html(html_text2);
    prtedit->show();
    QEventLoop loop;
    connect(prtedit, SIGNAL(svexit()), &loop, SLOT(quit()));
    loop.exec();
    delete prtedit;
    html_text2 = ret.result();
    actual_prot->set_endtxt(html_text2);
}
void protocol_constructor::create_varlist()
{
    varconst->change_type(select_type->currentData().toString());
    auto dlist = model_type->ret_all_data();
    vartype->clear();
    for (auto it : dlist){
        vartype->add_type(std::get<2>(it));
    }
    padapt->set_current_data(dat_edit->date());
    padapt->set_worker(select_engineer->currentData().value<worker>());
    padapt->set_number_prot(enter_number->text());
}
void protocol_constructor::slot_create()
{
    emit accept();
}
