#include "pair_editor.h"
pair_editor::pair_editor(QPair<QString, QString> arg, QString *lbl, QString *lbl1, QString *lbl2, int mw, int mw2, int tw, int tw2)
{
    this->main_obj = arg;
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle(*lbl);
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *txt_lay1 = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *txt_lay2 = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel *my_lbl1 = new QLabel();
    QLabel *my_lbl2 = new QLabel();
    my_lbl1->setText(*lbl1);
    my_lbl2->setText(*lbl2);
    my_lbl1->setMinimumWidth(tw);
    my_lbl2->setMinimumWidth(tw2);
    QBoxLayout *but_lay =new QBoxLayout(QBoxLayout::LeftToRight);
    my_line1 = new QLineEdit();
    my_line2 = new QLineEdit();
    my_line1->setMinimumWidth(mw);
    my_line2->setMinimumWidth(mw2);
    my_line1->setText(this->main_obj.first);
    my_line2->setText(this->main_obj.second);
    QPushButton *my_ok = new QPushButton("Готово");
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(save_pair()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));

    txt_lay1->addWidget(my_lbl1);
    txt_lay1->addWidget(my_line1);
    txt_lay2->addWidget(my_lbl2);
    txt_lay2->addWidget(my_line2);
    but_lay->addWidget(my_ok);
    but_lay->addWidget(my_cancel);
    main_lay->addLayout(txt_lay1);
    main_lay->addLayout(txt_lay2);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
pair_editor::~pair_editor()
{
    delete my_line1;
    delete my_line2;
}
QPair<QString, QString> pair_editor::result()
{
    return this->main_obj;
}
void pair_editor::save_pair()
{
    this->main_obj.first = this->my_line1->text();
    this->main_obj.second = this->my_line2->text();
    emit accept();
}
void pair_editor::set_mask(QRegExpValidator* arg_val, what_line arg_l)
{
    if (arg_l == what_line::one){
        my_line1->setValidator(arg_val);
    } else if (arg_l == what_line::two){
        my_line2->setValidator(arg_val);
    }
}
