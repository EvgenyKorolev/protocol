#include "pair_plus_editor.h"

pair_plus_editor::pair_plus_editor(std::tuple<QString, QString, QString> arg, QString &lbl, QString &lbl1, QString &lbl2, QString &lbl3, int mw, int mw2, int mw3)
{
    this->main_obj = arg;
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle(lbl);
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *txt_lay1 = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *txt_lay2 = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel *my_lbl1 = new QLabel();
    QLabel *my_lbl2 = new QLabel();
    QLabel *my_lbl3 = new QLabel();
    my_lbl1->setText(lbl1);
    my_lbl2->setText(lbl2);
    my_lbl3->setText(lbl3);
    int n{0};
    lbl1.size() > lbl2.size() ? n = my_lbl1->width()/5 : n = my_lbl2->width()/5;
    my_lbl1->setMinimumWidth(n);
    my_lbl2->setMinimumWidth(n);
    QBoxLayout *but_lay =new QBoxLayout(QBoxLayout::LeftToRight);
    my_line1 = new QLineEdit();
    my_line2 = new QLineEdit();
    my_txt = new QTextEdit();
    my_line1->setMinimumWidth(mw);
    my_line2->setMinimumWidth(mw2);
    my_txt->setMinimumWidth(mw3);
    my_line1->setText(std::get<0>(arg));
    my_line2->setText(std::get<1>(arg));
    my_txt->setText(std::get<2>(arg));
    QPushButton *my_ok = new QPushButton("Готово");
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(slot_save()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    txt_lay1->addWidget(my_lbl1);
    txt_lay1->addWidget(my_line1);
    txt_lay2->addWidget(my_lbl2);
    txt_lay2->addWidget(my_line2);
    but_lay->addWidget(my_ok);
    but_lay->addWidget(my_cancel);
    main_lay->addLayout(txt_lay1);
    main_lay->addLayout(txt_lay2);
    main_lay->addWidget(my_lbl3);
    main_lay->addWidget(my_txt);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
pair_plus_editor::~pair_plus_editor()
{
    delete my_line1;
    delete my_line2;
    delete my_txt;
}
std::tuple<QString, QString, QString> pair_plus_editor::result()
{
    return main_obj;
}
void pair_plus_editor::slot_save()
{
    main_obj = std::make_tuple(my_line1->text(), my_line2->text(), my_txt->toPlainText());
    emit accept();
}
void pair_plus_editor::set_mask(QRegExpValidator* arg_val, w_line arg_l)
{
    if (arg_l == w_line::one){
        my_line1->setValidator(arg_val);
    } else if (arg_l == w_line::two){
        my_line2->setValidator(arg_val);
    }
}
