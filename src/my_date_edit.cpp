#include "my_date_edit.h"
my_date_edit::~my_date_edit()
{
    delete my_date;
}
my_date_edit::my_date_edit(QDate data, QString lbl)
{
    this->main_obj = data;
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle(lbl);
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *but_lay =new QBoxLayout(QBoxLayout::LeftToRight);
    this->my_date = new QDateEdit();

    QPushButton *my_ok = new QPushButton("Готово");
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(save_date()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));

    but_lay->addWidget(my_ok);
    but_lay->addWidget(my_cancel);
    main_lay->addWidget(my_date);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
void my_date_edit::save_date()
{
    this->main_obj = this->my_date->date();
    emit accept();
}
QDate my_date_edit::result() {return this->main_obj;}
