#include "time_editor.h"

time_editor::~time_editor()
{
    delete my_time;
}
time_editor::time_editor(QTime arg, QString lbl)
{
    this->time_obj = arg;
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle(lbl);
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *but_lay =new QBoxLayout(QBoxLayout::LeftToRight);
    this->my_time = new QTimeEdit();

    QPushButton *my_ok = new QPushButton("Готово");
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(save_date()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));

    but_lay->addWidget(my_ok);
    but_lay->addWidget(my_cancel);
    main_lay->addWidget(my_time);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
void time_editor::save_time()
{
    this->time_obj = this->my_time->time();
    emit accept();
}
QTime time_editor::get_result() {return this->time_obj;}
