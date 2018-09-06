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



    QLabel* setdir = new QLabel();
    connect(name_edit, SIGNAL(textChanged(name_edit->text())), this, SLOT(slot_edit_txt()));
    setdir->setText("<HTML>Рабочая папка (При запуске программы атоматически доступны <br> только клиенты сохранённые в папку по умолчанию): <HTML>");

    QBoxLayout* but_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton* but_ok = new QPushButton("Готово");
    QPushButton* but_cancel = new QPushButton("Отмена");
    connect(but_ok, SIGNAL(clicked()), this, SLOT(slot_ok()));
    connect(but_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    but_lay->addWidget(but_ok);
    but_lay->addWidget(but_cancel);
    main_lay->addLayout(name_lay);
    main_lay->addLayout(fname_lay);

    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
std::tuple<QString, QString, QString> create_klent_menu::result() const
{
    return std::make_tuple(name_edit->text(), name_edit->text(), fail_name_edit->text());
}
void create_klent_menu::slot_edit_txt()
{
    if (def_fname){
        fail_name_edit->setText(name_edit->text() + ".ppk");
    }
}
void create_klent_menu::slot_ok()
{
    emit accept();
}

