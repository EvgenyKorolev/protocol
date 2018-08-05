#include "pair_time_editor.h"

pair_time_editor::~pair_time_editor()
{
    delete editor1;
    delete editor2;
}
pair_time_editor::pair_time_editor(QPair<QTime, QTime> arg, QString lbl1, QString lbl2)
{
    this->time = arg;
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Установить время");
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *fields_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *but_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *first_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *second_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    this->editor1 = new QTimeEdit(this);
    this->editor2 = new QTimeEdit(this);
    this->editor1->setTime(this->time.first);
    this->editor2->setTime(this->time.second);
    QLabel *ed1_lbl = new QLabel();
    QLabel *ed2_lbl = new QLabel();
    ed1_lbl->setText(lbl1);
    ed2_lbl->setText(lbl2);

    QPushButton *my_ok = new QPushButton("Готово");
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(save_time()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));

    first_lay->addWidget(ed1_lbl);
    first_lay->addWidget(this->editor1);
    second_lay->addWidget(ed2_lbl);
    second_lay->addWidget(this->editor2);
    fields_lay->addLayout(first_lay);
    fields_lay->addLayout(second_lay);
    main_lay->addLayout(fields_lay);
    but_lay->addWidget(my_ok);
    but_lay->addWidget(my_cancel);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
QPair<QTime, QTime> pair_time_editor::get_result()
{
    return this->time;
}
void pair_time_editor::save_time()
{
    this->time.first = this->editor1->time();
    this->time.second = this->editor2->time();
    emit accept();
}
