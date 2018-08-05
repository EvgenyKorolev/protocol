#include "fstring_edit.h"

fstring_edit::~fstring_edit()
{
    delete _my_line;
}
fstring_edit::fstring_edit(QString *arg, QString *lbl, int mw)
{
    _main_obj = *arg;
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle(*lbl);
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *but_lay =new QBoxLayout(QBoxLayout::LeftToRight);
    QDoubleValidator* valid = new QDoubleValidator();
    _my_line = new QLineEdit();
    _my_line->setMaximumWidth(mw);
    _my_line->setValidator(valid);
    _my_line->setText(_main_obj);
    QPushButton *my_ok = new QPushButton("Готово");
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(save_string()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    but_lay->addWidget(my_ok);
    but_lay->addWidget(my_cancel);
    main_lay->addWidget(_my_line);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
void fstring_edit::save_string()
{
    _main_obj = _my_line->text();
    emit accept();
}
QString fstring_edit::result() {return _main_obj;}

