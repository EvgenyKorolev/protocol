#include "int_editor.h"

int_editor::~int_editor()
{
    delete _my_line;
}
int_editor::int_editor(unsigned long long arg, QString *lbl, int mw)
{
    _s_main_obj = 0;
    _main_obj = arg;
    _i_main_obj = 0;
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle(*lbl);
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *but_lay =new QBoxLayout(QBoxLayout::LeftToRight);
    _my_line = new QLineEdit();
    QString tmp = "";
    for (int i = 1; i <= mw; i++) {tmp.append("0");}
    _my_line->setInputMask(tmp);
    _my_line->setText(QString::number(_main_obj));
    QPushButton *my_ok = new QPushButton("Готово");
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(save_int()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    but_lay->addWidget(my_ok);
    but_lay->addWidget(my_cancel);
    main_lay->addWidget(_my_line);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
int_editor::int_editor(unsigned int arg, QString lbl, int mw)
{
    _main_obj = 0;
    _s_main_obj = arg;
    _i_main_obj = 0;
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle(lbl);
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *but_lay =new QBoxLayout(QBoxLayout::LeftToRight);
    _my_line = new QLineEdit();
    QString tmp = "";
    for (int i = 1; i <= mw; i++) {tmp.append("0");}
    _my_line->setInputMask(tmp);
    _my_line->setText(QString::number(_s_main_obj));
    QPushButton *my_ok = new QPushButton("Готово");
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(s_save_int()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    but_lay->addWidget(my_ok);
    but_lay->addWidget(my_cancel);
    main_lay->addWidget(_my_line);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
int_editor::int_editor(int arg, QString lbl, int mw)
{
    _main_obj = 0;
    _s_main_obj = 0;
    _i_main_obj = arg;
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle(lbl);
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *but_lay =new QBoxLayout(QBoxLayout::LeftToRight);
    _my_line = new QLineEdit();
    QString tmp = "";
    for (int i = 1; i <= mw; i++) {tmp.append("0");}
    _my_line->setInputMask(tmp);
    _my_line->setText(QString::number(_i_main_obj));
    QPushButton *my_ok = new QPushButton("Готово");
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(s_save_int()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    but_lay->addWidget(my_ok);
    but_lay->addWidget(my_cancel);
    main_lay->addWidget(_my_line);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
void int_editor::save_int()
{
    _main_obj = _my_line->text().toULongLong();
    emit accept();
}
void int_editor::s_save_int()
{
    _s_main_obj = _my_line->text().toUInt();
    emit accept();
}
void int_editor::i_save_int()
{
    _i_main_obj = _my_line->text().toInt();
    emit accept();
}
unsigned long long int int_editor::result() {return _main_obj;}
unsigned int int_editor::s_result() {return _s_main_obj;}
int int_editor::i_result() {return _i_main_obj;}
