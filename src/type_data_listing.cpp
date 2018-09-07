#include "type_data_listing.h"

type_data_listing::type_data_listing()
{
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Справочник констант");
    this->setMinimumWidth(700);
    type_const_loader& tmp_load = type_const_loader::getInstance();
    key_list = tmp_load.get_id_list();
    var_list = tmp_load.get_var_list();
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QLabel* prot_type_label = new QLabel("Набор констант:");
    prot_type_label->setMaximumWidth(120);
    prot_type_label->setMinimumWidth(120);
    QBoxLayout* type_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    description = new QTextEdit();
    description->setReadOnly(true);
    description->setMaximumHeight(70);
    cls_lb = new QLabel();
    QLabel* cls_lab = new QLabel();
    cls_lab->setText("Класс набора констант: ");
    cls_lab->setMinimumWidth(180);
    QBoxLayout* des_cls_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* cls_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    des_cls_lay->addWidget(description);
    des_cls_lay->addLayout(cls_lay);
    cls_lay->addWidget(cls_lab);
    cls_lay->addWidget(cls_lb);
    select_type = new QComboBox();
    select_type->addItems(key_list);
    QSortFilterProxyModel* proxy_mod = new QSortFilterProxyModel();
    proxy_mod->setDynamicSortFilter(true);
    QObject::connect(select_type, SIGNAL(currentTextChanged(QString)), this, SLOT(set_select_lst()));
    QPushButton* button_edit = new QPushButton("Изменить набор...");
    QObject::connect(button_edit, SIGNAL(clicked()), this, SLOT(edit_lst()));
    QPushButton* button_add = new QPushButton("Добавить набор...");
    QObject::connect(button_add, SIGNAL(clicked()), this, SLOT(add_lst()));
    QPushButton* button_copy = new QPushButton("Копировать набор...");
    QObject::connect(button_copy, SIGNAL(clicked()), this, SLOT(copy_list()));
    QPushButton* del_but = new QPushButton("Удалить набор");
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
    type_obj tmp = type_obj();
    type_view = new type_data_view(proxy_mod);
    type_model = new type_data_model(tmp);
    if (key_list.size() > 0) {
        this->set_lst(key_list.at(0));
    }
    proxy_mod->setSourceModel(type_model);
    type_view->setModel(proxy_mod);
    type_view->setSortingEnabled(true);
    type_view->setColumnWidth(0, 150);
    type_view->setColumnWidth(1, 150);
    type_view->setColumnWidth(2, 150);
    type_view->horizontalHeader()->setStretchLastSection(true);
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
    QPushButton* add_txt = new QPushButton("Добавить константу");
    QObject::connect(add_txt, SIGNAL(clicked()), type_view, SLOT(slot_add()));
    QObject::connect(type_view, SIGNAL(signal_new()), this, SLOT(slot_new_list()));
    QBoxLayout* end_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    end_lay->addWidget(ok);
    end_lay->addWidget(cancel_but);
    end_lay->addWidget(add_txt);
    main_lay->addLayout(type_lay);
    main_lay->addLayout(des_cls_lay);
    main_lay->addWidget(type_view);
    main_lay->addLayout(end_lay);
    this->setLayout(main_lay);
}
type_data_listing::~type_data_listing()
{
    delete type_model;
    delete type_view;
    delete select_type;
    delete description;
    delete cls_lb;
}
void type_data_listing::set_lst(const QString &key)
{
    type_const_loader& tmp_load = type_const_loader::getInstance();
    target_object = type_model->return_data();
    tmp_load.add_obj(target_object);
    current_key = key;
    target_object = tmp_load.get_obj(current_key);
    type_model->set_source_data(target_object);
    type_model->layoutChanged();
    QSortFilterProxyModel* proxy_mod = new QSortFilterProxyModel();
    proxy_mod->setDynamicSortFilter(true);
    proxy_mod->setSourceModel(type_model);
    type_view->setModel(proxy_mod);
    varname->setText(target_object.get_vname());
    description->setText(target_object.get_description());
    cls_lb->setText(target_object.get_cls());
}
void type_data_listing::slot_new_list()
{
    target_object = type_model->return_data();
    QSortFilterProxyModel* proxy_mod2 = new QSortFilterProxyModel();
    proxy_mod2->setSourceModel(type_model);
    proxy_mod2->setDynamicSortFilter(true);
    type_view->setModel(proxy_mod2);
}
void type_data_listing::set_select_lst()
{
    this->set_lst(select_type->currentText());
}
void type_data_listing::add_lst()
{
    QString tmp1 = "Новый набор констант: ";
    QString tmp2 = "Имя набора:       ";
    QString tmp3 = "Имя переменной: ";
    QString tmp4 = "Класс: ";
    QString tmp5 = "Описание: ";
    QRegExp rexp;
    rexp.setPattern("[A-Za-z0-9]{1,20}");
    QRegExpValidator* val = new QRegExpValidator();
    val->setRegExp(rexp);
    // Пара строк которая будет установлена в полях ввода. титлы окна. подпись первого поля ввода. подпись второго поля ввода. два минимальных размера полей
    pair_plus_editor *stred = new pair_plus_editor(std::make_tuple(QString(), QString(), QString(), QString()), tmp1, tmp2, tmp3, tmp4, tmp5, 250, 250, 250, 250);
    stred->set_mask(val, w_line::two);
    stred->setMinimumWidth(400);
    if (stred->exec() == QDialog::Accepted){
        if (std::find(var_list.begin(), var_list.end(), std::get<1>(stred->result())) != var_list.end()){
            QMessageBox::information(nullptr, "Ошибка", "Список переменных с таким именем уже есть");
            delete stred;
            return;
        }
        type_obj tmpo;
        tmpo.set_name(std::get<0>(stred->result()));
        tmpo.set_vname(std::get<1>(stred->result()));
        tmpo.set_cls(std::get<2>(stred->result()));
        tmpo.set_description(std::get<3>(stred->result()));
        type_const_loader& temp_set = type_const_loader::getInstance();
        temp_set.add_obj(tmpo);
        key_list = temp_set.get_id_list();
        var_list = temp_set.get_var_list();
        select_type->addItem(std::get<0>(stred->result()));
        select_type->setCurrentText(std::get<0>(stred->result()));
        set_select_lst();
        target_object = temp_set.get_obj(std::get<0>(stred->result()));
    }
    delete stred;
}
void type_data_listing::copy_list()
{
    QString tmp1 = "Новый набор констант: ";
    QString tmp2 = "Имя набора:       ";
    QString tmp3 = "Имя переменной: ";
    QString tmp4 = "Класс: ";
    QString tmp5 = "Описание: ";
    QRegExp rexp;
    rexp.setPattern("[A-Za-z0-9]{1,20}");
    QRegExpValidator* val = new QRegExpValidator();
    val->setRegExp(rexp);
    // Пара строк которая будет установлена в полях ввода. титлы окна. подпись первого поля ввода. подпись второго поля ввода. два минимальных размера полей
    pair_plus_editor *stred = new pair_plus_editor(std::make_tuple(QString(), QString(), QString(), QString()), tmp1, tmp2, tmp3, tmp4, tmp5, 250, 250, 250, 250);
    stred->set_mask(val, w_line::two);
    stred->setMinimumWidth(400);
    if (stred->exec() == QDialog::Accepted){
        if (std::find(var_list.begin(), var_list.end(), std::get<1>(stred->result())) != var_list.end()){
            QMessageBox::information(nullptr, "Ошибка", "Список переменных с таким именем уже есть");
            delete stred;
            return;
        }
        type_const_loader& temp_set = type_const_loader::getInstance();
        type_obj tmpo(target_object);
        tmpo.set_name(std::get<0>(stred->result()));
        tmpo.set_vname(std::get<1>(stred->result()));
        tmpo.set_cls(std::get<2>(stred->result()));
        tmpo.set_description(std::get<3>(stred->result()));
        temp_set.add_obj(tmpo);
        key_list = temp_set.get_id_list();
        var_list = temp_set.get_var_list();
        select_type->addItem(std::get<0>(stred->result()));
        select_type->setCurrentText(std::get<0>(stred->result()));
        set_select_lst();
        target_object = temp_set.get_obj(std::get<0>(stred->result()));
    }
    delete stred;
}
void type_data_listing::edit_lst()
{
    QString tmp1 = "Изменить набор констант: ";
    QString tmp2 = "Имя набора:     ";
    QString tmp3 = "Имя переменной: ";
    QString tmp4 = "Класс: ";
    QString tmp5 = "Описание: ";
    QString tmp_key = target_object.get_vname();
    QRegExp rexp;
    rexp.setPattern("[A-Za-z]{1,20}");
    QRegExpValidator* val = new QRegExpValidator();
    val->setRegExp(rexp);
    std::tuple<QString, QString, QString, QString> tmp_tup{target_object.get_name(), target_object.get_vname(), target_object.get_cls(), target_object.get_description()};
// Пара строк которая будет установлена в полях ввода. титлы окна. подпись первого поля ввода. подпись второго поля ввода. два минимальных размера полей
    pair_plus_editor *stred = new pair_plus_editor(tmp_tup, tmp1, tmp2, tmp3, tmp4, tmp5, 250, 250, 250, 250);
    stred->set_mask(val, w_line::two);
    stred->setMinimumWidth(400);
    if (stred->exec() == QDialog::Accepted){
        auto old_it = std::find(var_list.begin(), var_list.end(), tmp_key);
        auto new_it = std::find(var_list.begin(), var_list.end(), std::get<1>(stred->result()));
        if (new_it != var_list.end() && new_it != old_it){
            QMessageBox::information(nullptr, "Ошибка", "Тип протокола с таким именем переменной уже есть");
            delete stred;
            return;
        }
        target_object.set_name(std::get<0>(stred->result()));
        target_object.set_vname(std::get<1>(stred->result()));
        target_object.set_cls(std::get<2>(stred->result()));
        target_object.set_description(std::get<3>(stred->result()));
        type_const_loader& temp_set = type_const_loader::getInstance();
        if (temp_set.change_obj(target_object, tmp_key)) {
            type_model->set_source_data(target_object);
            type_model->layoutChanged();
            QSortFilterProxyModel* proxy_mod = new QSortFilterProxyModel();
            proxy_mod->setDynamicSortFilter(true);
            proxy_mod->setSourceModel(type_model);
            type_view->setModel(proxy_mod);
            key_list = temp_set.get_id_list();
            var_list = temp_set.get_var_list();
            select_type->clear();
            select_type->addItems(key_list);
            target_object = temp_set.get_obj(std::get<0>(stred->result()));
            this->set_lst(target_object.get_name());
            select_type->setCurrentText(target_object.get_name());
        } else {
            QMessageBox::information(nullptr, "Ошибка!!!", "Тип протокола с таким именем переменной уже есть. Сообщите об этой ошибке разработчикам");
            delete stred;
            return;}
    }
    delete stred;
}
void type_data_listing::exit()
{
    type_const_loader& tmp_load = type_const_loader::getInstance();
    target_object = type_model->return_data();
    tmp_load.add_obj(target_object);
    tmp_load.save();
    emit accept();
}
void type_data_listing::del()
{
    yes_no* pmbx = new yes_no("<b>Вы точно хотите удалить этот набор констант?</b>");
    if (pmbx->exec() == QDialog::Accepted)
    {
        type_const_loader& temp_set = type_const_loader::getInstance();
        temp_set.del_type(select_type->currentText());
        key_list = temp_set.get_id_list();
        if (key_list.size() > 0) {
            current_key = key_list.at(0);
            target_object = temp_set.get_obj(current_key);
            /* установка всяких даных в модели (обновление данных в модели)
             * должна быть до select_type->clear();
             * потому что select_type отправляет сигнал по которому
             * в data_list вставляются данные из модели */
            type_model->set_source_data(target_object);
            type_model->layoutChanged();
            QSortFilterProxyModel* proxy_mod = new QSortFilterProxyModel();
            proxy_mod->setSourceModel(type_model);
            proxy_mod->setDynamicSortFilter(true);
            type_view->setModel(proxy_mod);
            select_type->clear();
            select_type->addItems(key_list);
            select_type->setCurrentText(key_list.at(0));
        } else {
            type_obj tmp = type_obj();
            target_object = tmp;
            /* установка всяких даных в модели (обновление данных в модели)
             * должна быть до select_type->clear();
             * потому что select_type отправляет сигнал по которому
             * в data_list вставляются данные из модели */
            type_model->set_source_data(target_object);
            type_model->layoutChanged();
            QSortFilterProxyModel* proxy_mod = new QSortFilterProxyModel();
            proxy_mod->setDynamicSortFilter(true);
            proxy_mod->setSourceModel(type_model);
            type_view->setModel(proxy_mod);
            select_type->clear();
            select_type->addItems(key_list);
        }
    }
    delete pmbx;
}
