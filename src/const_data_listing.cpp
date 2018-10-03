#include "const_data_listing.h"
#include "edit_html.h"
#include "const_data_view.h"
#include "const_loader.h"
#include "pair_editor.h"
#include "yes_no.h"
#include "settings.h"
#include "textedit.h"
#include "my_function.h"
#include "edit_plain_text.h"
#include <QObject>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QComboBox>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QVariant>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QFile>
#include <QEventLoop>
#include <QWebEngineView>
const_data_listing::const_data_listing()
{
    setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    setWindowTitle("Справочник текстов");
    setMinimumWidth(800);
    const_loader& tmp_load = const_loader::getInstance();
    key_list = tmp_load.get_idv_list();
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QLabel* prot_type_label = new QLabel("Тип протокола:");
    prot_type_label->setMaximumWidth(110);
    prot_type_label->setMinimumWidth(110);
    QBoxLayout* type_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    select_type = new QComboBox();
    for (auto it : key_list){
        select_type->addItem(it.first, it.second);
    }
    QSortFilterProxyModel* proxy_mod2 = new QSortFilterProxyModel();
    proxy_mod2->setDynamicSortFilter(true);
    QObject::connect(select_type, SIGNAL(currentTextChanged(QString)), this, SLOT(set_select_lst()));
    QPushButton* button_edit = new QPushButton("Изменить тип...");
    QObject::connect(button_edit, SIGNAL(clicked()), this, SLOT(edit_lst()));
    QPushButton* button_add = new QPushButton("Добавить тип...");
    QObject::connect(button_add, SIGNAL(clicked()), this, SLOT(add_lst()));
    QPushButton* button_copy = new QPushButton("Копировать тип...");
    QObject::connect(button_copy, SIGNAL(clicked()), this, SLOT(slot_copy_list()));
    QPushButton* del_but = new QPushButton("Удалить тип");
    QObject::connect(del_but, SIGNAL(clicked()), this, SLOT(del()));
    button_add->setMinimumWidth(180);
    button_add->setMaximumWidth(180);
    button_edit->setMinimumWidth(180);
    button_edit->setMaximumWidth(180);
    button_copy->setMinimumWidth(180);
    button_copy->setMaximumWidth(180);
    del_but->setMinimumWidth(180);
    del_but->setMaximumWidth(180);
    varname = new QLabel();
    QLabel* varname_lab = new QLabel();
    varname_lab->setText("Имя переменной:");
    const_obj tmp = const_obj();
    const_view = new const_data_view(proxy_mod2);
    const_model = new const_data_model(tmp);
    varname->setText(tmp.get_vname());
    if (key_list.size() > 0) {
        this->set_lst(key_list.at(0).second);
    }
    proxy_mod2->setSourceModel(const_model);
    const_view->setModel(proxy_mod2);
    const_view->setSortingEnabled(true);
    const_view->setColumnWidth(0, 120);
    const_view->setColumnWidth(1, 250);
    const_view->horizontalHeader()->setStretchLastSection(true);
    QBoxLayout* one_col = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* two_col = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* three_col = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* str1_col = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* str2_col = new QBoxLayout(QBoxLayout::LeftToRight);
    str1_col->addWidget(prot_type_label);
    str1_col->addWidget(select_type);
    str2_col->addWidget(varname_lab);
    str2_col->addWidget(varname);
    one_col->addLayout(str1_col);
    one_col->addLayout(str2_col);
    two_col->addWidget(button_edit);
    two_col->addWidget(button_add);
    three_col->addWidget(del_but);
    three_col->addWidget(button_copy);
    type_lay->addLayout(one_col);
    type_lay->addLayout(two_col);
    type_lay->addLayout(three_col);
    QPushButton* ok = new QPushButton("Готово");
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(exit()));
    QPushButton* cancel_but = new QPushButton("Отмена");
    QObject::connect(cancel_but, SIGNAL(clicked()), this, SLOT(reject()));
    QPushButton* add_txt = new QPushButton("Добавить запись");
    QObject::connect(add_txt, SIGNAL(clicked()), const_view, SLOT(slot_add()));
    QObject::connect(const_view, SIGNAL(signal_new()), this, SLOT(slot_new_list()));
    QPushButton* edit_html = new QPushButton("Редактор HTML");
    QObject::connect(edit_html, SIGNAL(clicked()), this, SLOT(slot_ed_html()));
    QPushButton* w_edit_html = new QPushButton("Визуальный редактор");
    QObject::connect(w_edit_html, SIGNAL(clicked()), this, SLOT(slot_w_ed_html()));
    QPushButton* edit_js = new QPushButton("Редактор скриптов");
    QObject::connect(edit_js, SIGNAL(clicked()), this, SLOT(slot_edit_js()));
    QBoxLayout* end_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* end_but_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    end_but_lay->addWidget(ok);
    end_but_lay->addWidget(cancel_but);
    end_lay->addWidget(add_txt);
    end_lay->addWidget(edit_html);
    end_lay->addWidget(w_edit_html);
    end_lay->addWidget(edit_js);
    main_lay->addLayout(type_lay);
    main_lay->addWidget(const_view);
    main_lay->addLayout(end_lay);
    main_lay->addLayout(end_but_lay);
    this->setLayout(main_lay);
    we = new QWebEngineView();
}
const_data_listing::~const_data_listing(){
    delete const_model;
    delete const_view;
    delete select_type;
    delete we;
}
void const_data_listing::set_lst(const QString &key)
{
    const_loader& tmp_load = const_loader::getInstance();
    target_object = const_model->return_data();
    tmp_load.add_obj(target_object);
    current_key = key;
    target_object = tmp_load.get_obj(current_key);
    const_model->set_source_data(target_object);
    const_model->layoutChanged();
    QSortFilterProxyModel* proxy_mod2 = new QSortFilterProxyModel();
    proxy_mod2->setDynamicSortFilter(true);
    proxy_mod2->setSourceModel(const_model);
    const_view->setModel(proxy_mod2);
    varname->setText(target_object.get_vname());
}
void const_data_listing::slot_new_list()
{
    target_object = const_model->return_data();
    QSortFilterProxyModel* proxy_mod2 = new QSortFilterProxyModel();
    proxy_mod2->setSourceModel(const_model);
    proxy_mod2->setDynamicSortFilter(true);
    const_view->setModel(proxy_mod2);
}
void const_data_listing::add_lst()
{
    QString tmp1 = "Новый тип протокола: ";
    QString tmp2 = "Имя типа:       ";
    QString tmp3 = "Имя переменной: ";
    QRegExp rexp;
    rexp.setPattern("[A-Za-z0-9]{1,20}");
    QRegExpValidator* val = new QRegExpValidator();
    val->setRegExp(rexp);
// Пара строк которая будет установлена в полях ввода. титлы окна. подпись первого поля ввода. подпись второго поля ввода. два минимальных размера полей
    pair_editor *stred = new pair_editor(QPair<QString, QString>(), &tmp1, &tmp2, &tmp3, 250, 250);
    stred->set_mask(val, what_line::two);
    stred->setMinimumWidth(400);
    if (stred->exec() == QDialog::Accepted){
        if (std::find_if(key_list.begin(), key_list.end(), [stred](QPair<QString, QString>& arg)->bool{
                         return arg.second == stred->result().second;}) != key_list.end()){
            QMessageBox::information(nullptr, "Ошибка", "Тип протокола с таким именем переменной уже есть");
            delete stred;
            return;
        }
        const_obj tmpo;
        tmpo.set_name(stred->result().first);
        tmpo.set_vname(stred->result().second);
        const_loader& temp_set = const_loader::getInstance();
        temp_set.add_obj(tmpo);
        key_list = temp_set.get_idv_list();
        select_type->addItem(stred->result().first);
        select_type->setCurrentText(stred->result().first);
        set_select_lst();
        target_object = temp_set.get_obj(stred->result().first);
    }
    delete stred;
}
void const_data_listing::slot_copy_list()
{
    QString tmp1 = "Новый тип протокола: ";
    QString tmp2 = "Имя типа:       ";
    QString tmp3 = "Имя переменной: ";
    QRegExp rexp;
    rexp.setPattern("[A-Za-z0-9]{1,20}");
    QRegExpValidator* val = new QRegExpValidator();
    val->setRegExp(rexp);
// Пара строк которая будет установлена в полях ввода. титлы окна. подпись первого поля ввода. подпись второго поля ввода. два минимальных размера полей
    pair_editor *stred = new pair_editor(QPair<QString, QString>(), &tmp1, &tmp2, &tmp3, 250, 250);
    stred->set_mask(val, what_line::two);
    stred->setMinimumWidth(400);
    if (stred->exec() == QDialog::Accepted){
        if (std::find_if(key_list.begin(), key_list.end(), [stred](QPair<QString, QString>& arg)->bool{
                         return arg.second == stred->result().second;}) != key_list.end()){
            QMessageBox::information(nullptr, "Ошибка", "Тип протокола с таким именем переменной уже есть");
            delete stred;
            return;
        }
        const_obj tmpo(target_object);
        settings& tmpss = settings::GetInstance();
        QString tsrc{tmpss.get_data_patch() + tmpss.get_data_dir() + "/prt_" + target_object.get_vname() +".html"};
        QString tdist{tmpss.get_data_patch() + tmpss.get_data_dir() + "/prt_" + stred->result().second +".html"};
        QFile::copy(tsrc, tdist);
        tmpo.set_name(stred->result().first);
        tmpo.set_vname(stred->result().second);
        const_loader& temp_set = const_loader::getInstance();
        temp_set.add_obj(tmpo);
        key_list = temp_set.get_idv_list();
        select_type->clear();
        for (auto it : key_list){
            select_type->addItem(it.first, it.second);
        }
        select_type->setCurrentText(stred->result().first);
        set_select_lst();
        target_object = temp_set.get_obj(stred->result().first);
    }
    delete stred;
}
void const_data_listing::edit_lst()
{
    QString tmp1 = "Изменить тип протокола: ";
    QString tmp2 = "Имя типа:       ";
    QString tmp3 = "Имя переменной: ";
    QString tmp_key = target_object.get_vname();
    QRegExp rexp;
    rexp.setPattern("[A-Za-z]{1,20}");
    QRegExpValidator* val = new QRegExpValidator();
    val->setRegExp(rexp);
    QPair<QString, QString> tmp_pair{target_object.get_name(), target_object.get_vname()};
// Пара строк которая будет установлена в полях ввода. титлы окна. подпись первого поля ввода. подпись второго поля ввода. два минимальных размера полей
    pair_editor *stred = new pair_editor(tmp_pair, &tmp1, &tmp2, &tmp3, 250, 250);
    stred->set_mask(val, what_line::two);
    stred->setMinimumWidth(400);
    if (stred->exec() == QDialog::Accepted){
        auto old_it = std::find_if(key_list.begin(), key_list.end(), [&tmp_key](QPair<QString, QString>& arg)->bool{
                return arg.second == tmp_key;});
        auto new_it = std::find_if(key_list.begin(), key_list.end(), [stred](QPair<QString, QString>& arg)->bool{
                return arg.second == stred->result().second;});
        if (new_it != key_list.end() && new_it != old_it){
            QMessageBox::information(nullptr, "Ошибка", "Тип протокола с таким именем переменной уже есть");
            delete stred;
            return;
        }
        target_object.set_name(stred->result().first);
        target_object.set_vname(stred->result().second);
        const_loader& temp_set = const_loader::getInstance();
        if (temp_set.change_obj(target_object, tmp_key)) {
            const_model->set_source_data(target_object);
            const_model->layoutChanged();
            QSortFilterProxyModel* proxy_mod2 = new QSortFilterProxyModel();
            proxy_mod2->setDynamicSortFilter(true);
            proxy_mod2->setSourceModel(const_model);
            const_view->setModel(proxy_mod2);
            key_list = temp_set.get_idv_list();
            select_type->clear();
            for (auto it : key_list){
                select_type->addItem(it.first, it.second);
            }
            target_object = temp_set.get_obj(stred->result().second);
            this->set_lst(target_object.get_vname());
            select_type->setCurrentText(target_object.get_name());
        } else {
            QMessageBox::information(nullptr, "Ошибка!!!", "Тип протокола с таким именем переменной уже есть. Сообщите об этой ошибке разработчикам");
            delete stred;
            return;}
    }
    delete stred;
}
void const_data_listing::set_select_lst()
{
    this->set_lst(select_type->currentData().toString());
}
void const_data_listing::exit()
{
    const_loader& tmp_load = const_loader::getInstance();
    target_object = const_model->return_data();
    tmp_load.add_obj(target_object);
    tmp_load.save();
    emit accept();
}
void const_data_listing::del()
{
    yes_no* pmbx = new yes_no("<b>Вы точно хотите удалить этот тип протокола?</b>");
    if (pmbx->exec() == QDialog::Accepted)
    {
        const_loader& temp_set = const_loader::getInstance();
        temp_set.del_obj(target_object.get_vname());
        key_list = temp_set.get_idv_list();
        if (key_list.size() > 0) {
            current_key = key_list.at(0).second;
            target_object = temp_set.get_obj(current_key);
            /* установка всяких даных в модели (обновление данных в модели)
             * должна быть до select_type->clear();
             * потому что select_type отправляет сигнал по которому
             * в data_list вставляются данные из модели */
            const_model->set_source_data(target_object);
            const_model->layoutChanged();
            QSortFilterProxyModel* proxy_mod2 = new QSortFilterProxyModel();
            proxy_mod2->setSourceModel(const_model);
            proxy_mod2->setDynamicSortFilter(true);
            const_view->setModel(proxy_mod2);
            select_type->clear();
            for (auto it : key_list){
                select_type->addItem(it.first, it.second);
            }
            select_type->setCurrentText(key_list.at(0).first);
        } else {
            const_obj tmp = const_obj();
            target_object = tmp;
            /* установка всяких даных в модели (обновление данных в модели)
             * должна быть до select_type->clear();
             * потому что select_type отправляет сигнал по которому
             * в data_list вставляются данные из модели */
            const_model->set_source_data(target_object);
            const_model->layoutChanged();
            QSortFilterProxyModel* proxy_mod2 = new QSortFilterProxyModel();
            proxy_mod2->setDynamicSortFilter(true);
            proxy_mod2->setSourceModel(const_model);
            const_view->setModel(proxy_mod2);
            select_type->clear();
            for (auto it : key_list){
                select_type->addItem(it.first, it.second);
            }
        }
    }
    delete pmbx;
}
void const_data_listing::slot_ed_html()
{
    yes_no* exiter = new yes_no("Внимание, редактирование шаблонов - дело сложное. <br>"
                                "Если вы не знаете что делаете, лучше не делайте этого. <br> "
                                "Продолжить редактирование?", this);
    if (exiter->exec() != QDialog::Accepted) return;
    edit_html* hedit = new edit_html(target_object.get_vname(), target_object.get_name(), nullptr);
    if (hedit->exec() == QDialog::Accepted){}
    delete hedit;
}
void const_data_listing::slot_w_ed_html()
{
    yes_no* exiter = new yes_no("Внимание, редактирование шаблонов - дело сложное. <br>"
                                "Если вы не знаете что делаете, лучше не делайте этого. <br> "
                                "Продолжить редактирование?", this);
    if (exiter->exec() != QDialog::Accepted) return;
    settings& tmpss = settings::GetInstance();
    QString fname = tmpss.get_data_patch() + tmpss.get_data_dir() + "/prt_" + target_object.get_vname() +".html";
    QFile con_f(fname);
    if (!con_f.exists()){
        con_f.open(QIODevice::WriteOnly);
        con_f.close();
    }
    QString open_html;
    if (con_f.open(QIODevice::ReadOnly  | QIODevice::Text)){
        open_html = con_f.readAll();
        con_f.close();
    } else {
        QMessageBox::information(nullptr, "Отладка", "Не открывается файл с основным текстом протокола в HTML для чтения");
    }
    QPair<QString, QList<QString>> open_tmp = my_fnc::parse_js(open_html);
    QList<QString> open_js = open_tmp.second;
    open_html = open_tmp.first;
// ========================================
    open_html = open_html.remove('\n');
    my_fnc::hide_tag_text(open_html);
        delete we;
        we = new QWebEngineView();
        we->setHtml(open_html);
        QEventLoop loop0;
            connect(we, SIGNAL(loadFinished(bool)), &loop0, SLOT(quit()));
        loop0.exec();
        connect(this, SIGNAL(html(QString)), this, SLOT(handleHtml(QString)));
        we->page()->toHtml([this](const QString& result) mutable {emit html(result);});
        QEventLoop loopX;
        connect(this, SIGNAL(html(QString)), &loopX, SLOT(quit()));
        loopX.exec();
// ========================================
    ret_str ret;
    TextEdit *prtedit = new TextEdit(&ret, this, TextEdit_opt::pattern);
    open_html = end_html_tmp;
    prtedit->load_html(open_html);
    prtedit->show();
    QEventLoop loop;
    connect(prtedit, SIGNAL(svexit()), &loop, SLOT(quit()));
    loop.exec();
    delete prtedit;
    if (ret.is_save()){
        open_html = ret.result();
        my_fnc::show_tag_text(open_html);
        for (auto itj : open_js){
            open_html.insert(open_html.indexOf("</body>"), "<script type='text/javascript'>" + itj + "</script>");
        }
        QFile con_end(fname);
        con_end.copy(fname + ".bak");
        if (con_end.open(QIODevice::WriteOnly)){
            QTextStream stream(&con_end);
            stream << open_html;
            con_end.close();
        } else {
            QMessageBox::information(nullptr, "Отладка", "Не открывается файл с основным текстом протокола в HTML для записи");
        }
        con_end.close();
    }
}
void const_data_listing::slot_edit_js()
{
    yes_no* exiter = new yes_no("Внимание, редактирование шаблонов - дело сложное. <br>"
                                "Если вы не знаете что делаете, лучше не делайте этого. <br> "
                                "Продолжить редактирование?", this);
    if (exiter->exec() != QDialog::Accepted) return;
    settings& tmpss = settings::GetInstance();
    QString fname = tmpss.get_data_patch() + tmpss.get_data_dir() + "/prt_" + target_object.get_vname() +".html";
    QFile con_f(fname);
    if (!con_f.exists()){
        con_f.open(QIODevice::WriteOnly);
        con_f.close();
    }
    QString open_html;
    if (con_f.open(QIODevice::ReadOnly  | QIODevice::Text)){
        open_html = con_f.readAll();
        con_f.close();
    } else {
        QMessageBox::information(nullptr, "Отладка", "Не открывается файл с основным текстом протокола в HTML для чтения");
    }
    QPair<QString, QList<QString>> open_tmp = my_fnc::parse_js(open_html);
    QList<QString> open_js = open_tmp.second;
    open_html = open_tmp.first;
    QString edit_txt{""};
    for (auto itj : open_js){
        edit_txt += "<script type='text/javascript'>" + itj + "</script>";
    }
    edit_plain_text* hedit = new edit_plain_text(edit_txt, target_object.get_name(), nullptr);
    if (hedit->exec() == QDialog::Accepted){
        open_html.insert(open_html.indexOf("</body>"), hedit->result());
        QFile con_end(fname);
        con_end.copy(fname + ".bak");
        if (con_end.open(QIODevice::WriteOnly)){
            QTextStream stream(&con_end);
            stream << open_html;
            con_end.close();
        } else {
            QMessageBox::information(nullptr, "Отладка", "Не открывается файл с основным текстом протокола в HTML для записи");
        }
        con_end.close();
    }
    delete hedit;
}
void const_data_listing::handleHtml(QString sHtml)
{
    end_html_tmp = sHtml;
}
