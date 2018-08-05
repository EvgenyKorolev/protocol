#include "string_edit.h"

string_edit::~string_edit()
{
    delete my_line;
}
string_edit::string_edit(QString *arg, QString *lbl, int mw)
{
    this->main_obj = *arg;
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle(*lbl);
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *but_lay =new QBoxLayout(QBoxLayout::LeftToRight);
    this->my_line = new QLineEdit();
    this->my_line->setMinimumWidth(mw);
    this->my_line->setText(this->main_obj);
    QPushButton *my_ok = new QPushButton("Готово");
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(save_string()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));

    but_lay->addWidget(my_ok);
    but_lay->addWidget(my_cancel);
    main_lay->addWidget(my_line);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
void string_edit::save_string()
{
    this->main_obj = this->my_line->text();
    emit accept();
}
QString string_edit::result() {return this->main_obj;}

