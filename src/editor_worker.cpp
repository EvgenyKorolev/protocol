#include "editor_worker.h"

editor_worker::~editor_worker()
{
    delete name_label;
    delete surname_label;
    delete fname_label;
    delete position_label;
    delete tel_label;
    delete post_label;
    delete login_label;
    delete pass_label;
    delete adr_label;
}
editor_worker::editor_worker(worker *data, QWidget *parent) : QDialog(parent)
{
    main_data = data;
    flag_edit = false;
    this->setWindowTitle("Сотрудник");
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
//    QString name;
    name_label = new QLabel();
    name_label->setText(main_data->get_name());
    QLabel *name_ord = new QLabel();
    name_ord->setText("Имя: ");
    QPushButton *name_ed = new QPushButton("Изменить...");
    name_ed->setMaximumWidth(100);
    name_ed->setMinimumWidth(100);
    QObject::connect(name_ed, SIGNAL(clicked()), this, SLOT(name_edit()));
    QBoxLayout *name_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    name_lay->addWidget(name_ord);
    name_lay->addWidget(name_label);
    name_lay->addWidget(name_ed);
//    QString surname;
    surname_label = new QLabel();
    surname_label->setText(main_data->get_surname());
    QLabel *surname_ord = new QLabel();
    surname_ord->setText("Фамилия: ");
    QPushButton *surname_ed = new QPushButton("Изменить...");
    surname_ed->setMaximumWidth(100);
    surname_ed->setMinimumWidth(100);
    QObject::connect(surname_ed, SIGNAL(clicked()), this, SLOT(surname_edit()));
    QBoxLayout *surname_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    surname_lay->addWidget(surname_ord);
    surname_lay->addWidget(surname_label);
    surname_lay->addWidget(surname_ed);
//    QString fname;
    fname_label = new QLabel();
    fname_label->setText(main_data->get_fname());
    QLabel *fname_ord = new QLabel();
    fname_ord->setText("Отчество: ");
    QPushButton *fname_ed = new QPushButton("Изменить...");
    fname_ed->setMaximumWidth(100);
    fname_ed->setMinimumWidth(100);
    QObject::connect(fname_ed, SIGNAL(clicked()), this, SLOT(fname_edit()));
    QBoxLayout *fname_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    fname_lay->addWidget(fname_ord);
    fname_lay->addWidget(fname_label);
    fname_lay->addWidget(fname_ed);
//    QString position;
    position_label = new QLabel();
    position_label->setText(main_data->get_position());
    QLabel *position_ord = new QLabel();
    position_ord->setText("Должность: ");
    QPushButton *position_ed = new QPushButton("Изменить...");
    position_ed->setMaximumWidth(100);
    position_ed->setMinimumWidth(100);
    QObject::connect(position_ed, SIGNAL(clicked()), this, SLOT(position_edit()));
    QBoxLayout *position_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    position_lay->addWidget(position_ord);
    position_lay->addWidget(position_label);
    position_lay->addWidget(position_ed);
//    QString tel;
    tel_label = new QLabel();
    tel_label->setText(main_data->get_tel());
    QLabel *tel_ord = new QLabel();
    tel_ord->setText("Телефон: ");
    QPushButton *tel_ed = new QPushButton("Изменить...");
    tel_ed->setMaximumWidth(100);
    tel_ed->setMinimumWidth(100);
    QObject::connect(tel_ed, SIGNAL(clicked()), this, SLOT(tel_edit()));
    QBoxLayout *tel_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    tel_lay->addWidget(tel_ord);
    tel_lay->addWidget(tel_label);
    tel_lay->addWidget(tel_ed);
//    QString post;
    post_label = new QLabel();
    post_label->setText(main_data->get_post());
    QLabel *post_ord = new QLabel();
    post_ord->setText("Email: ");
    QPushButton *post_ed = new QPushButton("Изменить...");
    post_ed->setMaximumWidth(100);
    post_ed->setMinimumWidth(100);
    QObject::connect(post_ed, SIGNAL(clicked()), this, SLOT(post_edit()));
    QBoxLayout *post_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    post_lay->addWidget(post_ord);
    post_lay->addWidget(post_label);
    post_lay->addWidget(post_ed);
// Это начальник лаборатории?
    QLabel *men_label = new QLabel();
    men_label->setText("Начальник лаборатории: ");
    menege_box = new QCheckBox();
    menege_box->setChecked(data->tets_meneger());
    QBoxLayout *men_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    men_lay->addWidget(men_label);
    men_lay->addWidget(menege_box);
//    QString login;
//    QString pass;
//    address adr;
// Финальные кнопки
    QBoxLayout *push_list = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton *push_ok = new QPushButton("Сохранить");
    QPushButton *push_cancel = new QPushButton("Не сохранять");
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(save_worker()));
    push_list->addWidget(push_ok);
    push_list->addWidget(push_cancel);
// Расставляем виджеты
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    main_lay->addLayout(name_lay);
    main_lay->addLayout(surname_lay);
    main_lay->addLayout(fname_lay);
    main_lay->addLayout(position_lay);
    main_lay->addLayout(post_lay);
    main_lay->addLayout(men_lay);
    main_lay->addLayout(push_list);
    this->setLayout(main_lay);
    this->setParent(parent);
}
bool editor_worker::is_edit()
{
    return flag_edit;
}
worker editor_worker::result()
{
    return *(this->main_data);
}
void editor_worker::name_edit()
{
    QString tmp1 = "Имя: ";
    QString tmp2 = this->main_data->get_name();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_data->set_name(stred->result());
        this->name_label->setText(main_data->get_name());
        this->name_label->adjustSize();
      flag_edit = true;
    }
    delete stred;
}
void editor_worker::surname_edit()
{
    QString tmp1 = "Фамилия: ";
    QString tmp2 = this->main_data->get_surname();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_data->set_surname(stred->result());
        this->surname_label->setText(main_data->get_surname());
        this->surname_label->adjustSize();
      flag_edit = true;
    }
    delete stred;
}
void editor_worker::fname_edit()
{
    QString tmp1 = "Отчество: ";
    QString tmp2 = this->main_data->get_fname();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_data->set_fname(stred->result());
        this->fname_label->setText(main_data->get_fname());
        this->fname_label->adjustSize();
      flag_edit = true;
    }
    delete stred;
}
void editor_worker::position_edit()
{
    QString tmp1 = "Должность: ";
    QString tmp2 = this->main_data->get_position();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_data->set_position(stred->result());
        this->position_label->setText(main_data->get_position());
        this->position_label->adjustSize();
      flag_edit = true;
    }
    delete stred;
}
void editor_worker::tel_edit()
{
    QString tmp1 = "Телефон: ";
    QString tmp2 = this->main_data->get_tel();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_data->set_tel(stred->result());
        this->tel_label->setText(main_data->get_tel());
        this->tel_label->adjustSize();
      flag_edit = true;
    }
    delete stred;
}
void editor_worker::post_edit()
{
    QString tmp1 = "Email: ";
    QString tmp2 = this->main_data->get_post();
    string_edit *stred = new string_edit(&tmp2, &tmp1, 300);
    if (stred->exec() == QDialog::Accepted){
        this->main_data->set_post(stred->result());
        this->post_label->setText(main_data->get_post());
        this->post_label->adjustSize();
      flag_edit = true;
    }
    delete stred;
}
void editor_worker::login_edit()
{}
void editor_worker::pass_edit()
{}
void editor_worker::adr_edit()
{}
void editor_worker::save_worker()
{
    if (main_data->get_name() != ""){
        if (main_data->get_surname() != ""){
            if (main_data->get_position() != ""){
                if (menege_box->isChecked()){
                    if (!main_data->tets_meneger()){
                        main_data->inv_meneger();
                    }
                } else {
                    if (main_data->tets_meneger()){
                        main_data->inv_meneger();
                    }
                }
                emit accept();
            } else {
                QMessageBox *trem = new QMessageBox();
                trem->setWindowTitle("Внимание!");
                trem->setText("Нельзя создать сотрудника без должности");
                trem->exec();
                delete trem;
            }
        } else {
            QMessageBox *trem = new QMessageBox();
            trem->setWindowTitle("Внимание!");
            trem->setText("Нельзя создать сотрудника без фамилии");
            trem->exec();
            delete trem;
        }
    } else {
        QMessageBox *trem = new QMessageBox();
        trem->setWindowTitle("Внимание!");
        trem->setText("Нельзя создать сотрудника без имени");
        trem->exec();
        delete trem;
    }
}
