#include "create_klent_menu.h"

create_klent_menu::create_klent_menu()
{
    this->setWindowTitle("Сздать клиента: ");
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QLabel* annatation = new QLabel();
    annatation->setText("Название организации: ");
    annatation->setMinimumWidth(200);
    annatation->setMaximumWidth(200);
    name_edit = new QLineEdit();
    name_edit->setMinimumWidth(400);
    QBoxLayout* name_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    name_lay->addWidget(annatation);
    name_lay->addWidget(name_edit);
    QLabel* setfname = new QLabel();
    setfname->setText("Имя файла:");
    fail_name_edit = new QLineEdit();
    setfname->setMinimumWidth(200);
    setfname->setMaximumWidth(200);
    fail_name_edit->setMinimumWidth(400);
    QBoxLayout* fname_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    fname_lay->addWidget(setfname);
    fname_lay->addWidget(fail_name_edit);
    connect(name_edit, SIGNAL(textChanged(const QString&)), this, SLOT(slot_edit_txt()));
    connect(fail_name_edit, SIGNAL(textEdited(const QString&)), this, SLOT(slot_dir_edit()));
// Наша директория по умолчанияю
    settings& tmps = settings::GetInstance();
    QDir tmp_dir(tmps.get_data_patch() + tmps.get_customers_dir());
    QString abs_path = tmp_dir.path();
// блок выбора директории
    QLabel* setdir = new QLabel();
    setdir->setText("<HTML>Рабочая папка (При запуске программы атоматически доступны только клиенты сохранённые в папку по умолчанию): <HTML>");
    dirp_lab = new QLabel();
    dirp_lab->setText(abs_path);
    QPushButton* change_path = new QPushButton("Изменить");
    connect(change_path, SIGNAL(clicked()), this, SLOT(slot_dir_change()));
    QBoxLayout* dir_path_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    dir_path_lay->addWidget(dirp_lab);
    dir_path_lay->addWidget(change_path);
    QBoxLayout* dir_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    dir_lay->addWidget(setdir);
    dir_lay->addLayout(dir_path_lay);
    QBoxLayout* but_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton* but_ok = new QPushButton("Готово");
    QPushButton* but_cancel = new QPushButton("Отмена");
    connect(but_ok, SIGNAL(clicked()), this, SLOT(slot_ok()));
    connect(but_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    but_lay->addWidget(but_ok);
    but_lay->addWidget(but_cancel);
    main_lay->addLayout(name_lay);
    main_lay->addLayout(fname_lay);
    main_lay->addLayout(dir_lay);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
void create_klent_menu::slot_dir_change()
{
    dirp_lab->setText(QFileDialog::getExistingDirectory());
    dirp_lab->adjustSize();
}
std::tuple<QString, QString, QString> create_klent_menu::result() const
{
    return std::make_tuple(name_edit->text(), dirp_lab->text(), fail_name_edit->text());
}
void create_klent_menu::slot_edit_txt()
{
    if (def_fname){
        fail_name_edit->setText(name_edit->text() + ".ppk");
    }
}
void create_klent_menu::slot_dir_edit()
{
    def_fname = false;
}
void create_klent_menu::slot_ok()
{
    settings& tmps = settings::GetInstance();
    if (dirp_lab->text() == ""){
        QDir tmp_dir(tmps.get_data_patch() + tmps.get_customers_dir());
        dirp_lab->setText(tmp_dir.path());
    }
    if (name_edit->text() == ""){
        QMessageBox *tmoer = new QMessageBox();
        tmoer->setWindowTitle("Внимание!");
        tmoer->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
        tmoer->setText("Нельзя оставить клиента без названия");
        tmoer->exec();
        delete tmoer;
        return;
    }
    if (fail_name_edit->text() == ""){
        QMessageBox *tmoer = new QMessageBox();
        tmoer->setWindowTitle("Внимание!");
        tmoer->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
        tmoer->setText("Нельзя оставить файл клиента без названия");
        tmoer->exec();
        delete tmoer;
        return;
    }
    emit accept();
}

