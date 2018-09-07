#include "app_editor.h"

app_editor::~app_editor()
{
    delete name_label;       // Название прибора
    delete mdata_label;        // Дата... чего-то там, пока непонятно
    delete cls_label;        // Класс прибора (Тип СИ)
    delete mnom_label;       // Заводской номер
    delete _clas_label;    // Класс точности
    delete ver_view;
    delete ver_model;
    delete ver_list;
}
app_editor::app_editor(apparaturs *data, bool direct, QWidget *parent)
{
    this->flag_edit = false;
    this->main_data = data;
    this->setWindowTitle("Редактор прибора");
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setMinimumWidth(586);
//    QString name;       // Название прибора
    this->name_label = new QLabel();
    name_label->setText(main_data->get_name());
    QLabel *name_app = new QLabel();
    name_app->setText("Наименование прибора:");
    QPushButton *name_ed = new QPushButton("Изменить...");
    name_ed->setMaximumWidth(100);
    name_ed->setMinimumWidth(100);
    QObject::connect(name_ed, SIGNAL(clicked()), this, SLOT(name_edit()));
    QBoxLayout *name_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    name_lay->addWidget(name_app);
    name_lay->addWidget(name_label);
    name_lay->addWidget(name_ed);
//    QDate mdata;        // Дата... чего-то там, пока непонятно
    this->mdata_label = new QLabel();
    mdata_label->setText(main_data->get_mdata().toString("dd.MM.yy"));
    QLabel *mdata_app = new QLabel();
    mdata_app->setText("Дата:");
    QPushButton *mdata_ed = new QPushButton("Изменить...");
    mdata_ed->setMaximumWidth(100);
    mdata_ed->setMinimumWidth(100);
    QObject::connect(mdata_ed, SIGNAL(clicked()), this, SLOT(mdata_edit()));
    QBoxLayout *mdata_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    mdata_lay->addWidget(mdata_app);
    mdata_lay->addWidget(mdata_label);
    mdata_lay->addWidget(mdata_ed);
//    QList<QPair<QPair<QString, QDate>, QDate>> verification;   // Номер свидетельства о поверке, дата поверки, дата очередной поверки
    QBoxLayout *ver_main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    this->ver_list = new QList<QPair<QPair<QString, QDate>, QDate>>(this->main_data->get_verification_list());
    ver_model = new ver_data_model(this->ver_list);
    ver_view = new ver_data_view(&this->flag_edit, this);
    ver_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ver_main_lay->addWidget(ver_view);
    ver_view->setModel(ver_model);
    ver_view->setColumnWidth(0, 210);
    ver_view->setColumnWidth(1, 150);
    ver_view->horizontalHeader()->setStretchLastSection(true);
//    QString cls;        // Класс прибора (Тип СИ)
    this->cls_label = new QLabel();
    cls_label->setText(main_data->get_type());
    QLabel *cls_app = new QLabel();
    cls_app->setText("Тип СИ:");
    QPushButton *cls_ed = new QPushButton("Изменить...");
    cls_ed->setMaximumWidth(100);
    cls_ed->setMinimumWidth(100);
    QObject::connect(cls_ed, SIGNAL(clicked()), this, SLOT(cls_edit()));
    QBoxLayout *cls_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    cls_lay->addWidget(cls_app);
    cls_lay->addWidget(cls_label);
    cls_lay->addWidget(cls_ed);
//    QString mnom;       // Заводской номер
    this->mnom_label = new QLabel();
    mnom_label->setText(main_data->get_mnom());
    QLabel *mnom_app = new QLabel();
    mnom_app->setText("Заводской номер:");
    QPushButton *mnom_ed = new QPushButton("Изменить...");
    mnom_ed->setMaximumWidth(100);
    mnom_ed->setMinimumWidth(100);
    QObject::connect(mnom_ed, SIGNAL(clicked()), this, SLOT(mnom_edit()));
    QBoxLayout *mnom_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    mnom_lay->addWidget(mnom_app);
    mnom_lay->addWidget(mnom_label);
    mnom_lay->addWidget(mnom_ed);
// Класс точности
    _clas_label = new QLabel();
    _clas_label->setText(main_data->get_clas());
    QLabel *clas_app = new QLabel();
    clas_app->setText("Класс точности:");
    QPushButton *clas_ed = new QPushButton("Изменить...");
    clas_ed->setMaximumWidth(100);
    clas_ed->setMinimumWidth(100);
    QObject::connect(clas_ed, SIGNAL(clicked()), this, SLOT(clas_edit()));
    QBoxLayout *clas_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    clas_lay->addWidget(clas_app);
    clas_lay->addWidget(_clas_label);
    clas_lay->addWidget(clas_ed);
// Финальные кнопки
    QBoxLayout *push_list = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton *push_ok = new QPushButton("Сохранить");
    QPushButton *push_cancel = new QPushButton("Не сохранять");
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(save_app()));
    push_list->addWidget(push_ok);
    push_list->addWidget(push_cancel);
    if (!direct){
        QPushButton *push_in = new QPushButton("В справочник");
        QPushButton *push_out = new QPushButton("Из справочника");
        QObject::connect(push_in, SIGNAL(clicked()), this, SLOT(slot_add_list()));
        QObject::connect(push_out, SIGNAL(clicked()), this, SLOT(refresh_lst()));
        push_list->addWidget(push_in);
        push_list->addWidget(push_out);
    }
// Расставляем виджеты
    QBoxLayout * edit_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    edit_layout->addLayout(name_lay);
    edit_layout->addLayout(mdata_lay);
    edit_layout->addLayout(ver_main_lay);
    edit_layout->addLayout(cls_lay);
    edit_layout->addLayout(mnom_lay);
    edit_layout->addLayout(clas_lay);
    edit_layout->addLayout(push_list);
    this->setLayout(edit_layout);
    this->setParent(parent);
}
bool app_editor::is_edit()
{
    return this->flag_edit;
}
apparaturs app_editor::result()
{
    return *(this->main_data);
}
void app_editor::name_edit()
{
    QString tmp1 = "Наименование прибора:";
    QString tmp2 = this->main_data->get_name();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_data->set_name(stred->result());
        this->name_label->setText(this->main_data->get_name());
        this->name_label->adjustSize();
        flag_edit = true;
    }
    delete stred;
}
void app_editor::mdata_edit()
{
    QString tmp1 = "Дата выпуска: ";
    QDate tmp2 = this->main_data->get_mdata();
    my_date_edit *ded = new my_date_edit(tmp2, tmp1);
    if (ded->exec() == QDialog::Accepted){
        this->main_data->set_mdata(ded->result());
        this->mdata_label->setText(this->main_data->get_mdata().toString("dd.MMMM.yyyy"));
        this->mdata_label->adjustSize();
        flag_edit = true;
    }
    delete ded;
}
void app_editor::cls_edit()
{
    QString tmp1 = "Тип СИ:";
    QString tmp2 = this->main_data->get_type();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_data->set_type(stred->result());
        this->cls_label->setText(this->main_data->get_type());
        this->cls_label->adjustSize();
        flag_edit = true;
    }
    delete stred;
}
void app_editor::mnom_edit()
{
    QString tmp1 = "Заводской номер:";
    QString tmp2 = this->main_data->get_mnom();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_data->set_mnom(stred->result());
        this->mnom_label->setText(this->main_data->get_mnom());
        this->mnom_label->adjustSize();
        flag_edit = true;
    }
    delete stred;
}
void app_editor::clas_edit()
{
    QString tmp1 = "Класс точности:";
    QString tmp2 = this->main_data->get_clas();
    fstring_edit *fled = new fstring_edit(&tmp2, &tmp1, 200);
    if (fled->exec() == QDialog::Accepted){
        this->main_data->set_clas(fled->result());
        _clas_label->setText(this->main_data->get_clas());
        _clas_label->adjustSize();
        flag_edit = true;
    }
    delete fled;
}
void app_editor::save_app()
{
    if (main_data->get_name() != ""){
        if (main_data->get_mnom() != ""){
            this->main_data->set_verification_list(this->ver_list);
        emit accept();
        }
        else {
            QMessageBox *tmoer = new QMessageBox();
            tmoer->setWindowTitle("Внимание!");
            tmoer->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
            tmoer->setText("Нельзя создавать прибор совсем без заводского номера");
            tmoer->exec();
            delete tmoer;
        }
    }
    else {
        QMessageBox *tmoer = new QMessageBox();
        tmoer->setWindowTitle("Внимание!");
        tmoer->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
        tmoer->setText("Нельзя создавать прибор совсем без названия");
        tmoer->exec();
        delete tmoer;
    }
}
void app_editor::slot_add_list()
{
    if (main_data->get_name() != ""){
        if (main_data->get_mnom() != ""){
            this->main_data->set_verification_list(this->ver_list);
            // Теперь попробуем добавить прибор в справочник
            directory_app& tmp_dir = directory_app::getInstance();
            if (tmp_dir.is_made_num(main_data->get_mnom())){
                int i{tmp_dir.is_row(main_data->get_mnom())};
                tmp_dir.replace(i, *main_data);
            } else {tmp_dir.append(*main_data);}
        }
        else {
            QMessageBox *tmoer = new QMessageBox();
            tmoer->setWindowTitle("Внимание!");
            tmoer->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
            tmoer->setText("Нельзя добавить в справочник прибор совсем без заводского номера");
            tmoer->exec();
            delete tmoer;
        }
    }
    else {
        QMessageBox *tmoer = new QMessageBox();
        tmoer->setWindowTitle("Внимание!");
        tmoer->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
        tmoer->setText("Нельзя добавить в справочник прибор совсем без названия");
        tmoer->exec();
        delete tmoer;
    }
}
void app_editor::refresh_lst()
{
    directory_app& tmp_dir = directory_app::getInstance();
    if (tmp_dir.is_made_num(main_data->get_mnom())){
        int i{tmp_dir.is_row(main_data->get_mnom())};
        *main_data = tmp_dir.at(i);
        this->refresh();
    } else {
        app_in_direct* instr = new app_in_direct();
        if (instr->exec() == QDialog::Accepted){
            *main_data = instr->get_result();
            flag_edit = true;
        }
        delete instr;
        this->refresh();
    }
}
void app_editor::refresh()
{
    name_label->setText(main_data->get_name());       // Название прибора
    mdata_label->setText(main_data->get_mdata().toString("dd.MM.yy"));        // Дата... чего-то там, пока непонятно
    ver_model->layoutChanged();   // Номер свидетельства о поверке, дата поверки, дата очередной поверки
    cls_label->setText(main_data->get_type());        // Класс прибора (Тип СИ)
    mnom_label->setText(main_data->get_mnom());       // Заводской номер
    _clas_label->setText(main_data->get_clas());    // Класс точности
}

