#include "protocol_editor.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QLineEdit>
#include <QDateEdit>
#include "textedit.h"

protocol_editor::protocol_editor(protocol* prt, QWidget *par) : QDialog(par)
{
    this->setWindowTitle("Протокол " + prt->get_type() + " № " + prt->get_number() + " от " + prt->get_date().toString());
    this->setWindowIcon(QIcon(":/pic/images/KlogoS.png"));
    end_txt = prt->get_endtxt();
    src_txt = prt->get_prttxt();
    tmp_dat = prt->get_date();
    tmp_num = prt->get_number();
    prot = prt;
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* info_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* l1 = new QLabel();
    l1->setText("Протокол " + prt->get_type() + " № ");
    number = new QLabel();
    number->setText(prt->get_number());
    QLabel* l2 = new QLabel();
    l2->setText(" от ");
    date = new QLabel();
    date->setText(prt->get_date().toString("dd.MMMM.yyyy"));
    QPushButton* edit_var_push = new QPushButton("Изменить...");
    connect(edit_var_push, SIGNAL(clicked()), this, SLOT(edit_var()));
    info_lay->addWidget(l1);
    info_lay->addWidget(number);
    info_lay->addWidget(l2);
    info_lay->addWidget(date);
    info_lay->addWidget(edit_var_push);
    QPushButton* txt_edit = new QPushButton("Редактировать текст протокола");
    connect(txt_edit, SIGNAL(clicked()), this, SLOT(edit_text()));
    QBoxLayout *push_list = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton *push_ok = new QPushButton("Сохранить");
    QPushButton *push_cancel = new QPushButton("Отмена");
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(save_protocol()));
    push_list->addWidget(push_ok);
    push_list->addWidget(push_cancel);
    main_lay->addLayout(info_lay);
    main_lay->addWidget(txt_edit);
    main_lay->addLayout(push_list);
    this->setLayout(main_lay);
}
protocol_editor::~protocol_editor()
{
    delete number;
    delete date;
}
void protocol_editor::save_protocol()
{
    prot->set_date(tmp_dat);
    prot->set_number(tmp_num);
    emit accept();
}
void protocol_editor::edit_var()
{
    edit_prt_xml* edt = new edit_prt_xml(tmp_num, tmp_dat);
    if (edt->exec() == QDialog::Accepted){
        QPair<QString, QDate> ret = edt->result();
        tmp_dat = ret.second;
        tmp_num = ret.first;
        number->setText(tmp_num);
        date->setText(tmp_dat.toString("dd.MMMM.yyyy"));
        number->adjustSize();
        date->adjustSize();
    }
    delete edt;
}
void protocol_editor::edit_text()
{
    TextEdit *prtedit = new TextEdit(this);
    prtedit->load_html(end_txt);
    prtedit->show();
}
// ---------=============== Функции класса редактора =====================----------------
edit_prt_xml::edit_prt_xml(const QString& num, const QDate& dt, QWidget *par) : QDialog(par)
{
    this->setWindowTitle("Номер и дата протокола");
    this->setWindowIcon(QIcon(":/pic/images/KlogoS.png"));
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    numb = new QLineEdit();
    numb->setText(num);
    dat = new QDateEdit();
    dat->setDate(dt);
    QLabel* l1 = new QLabel();
    QLabel* l2 = new QLabel();
    l1->setText("Номер: ");
    l2->setText("Дата: ");
    l2->setMaximumWidth(100);
    l2->setMinimumWidth(100);
    l1->setMaximumWidth(100);
    l1->setMinimumWidth(100);
    QBoxLayout* line1 = new QBoxLayout(QBoxLayout::LeftToRight);
    line1->addWidget(l1);
    line1->addWidget(numb);
    QBoxLayout* line2 = new QBoxLayout(QBoxLayout::LeftToRight);
    line2->addWidget(l2);
    line2->addWidget(dat);
    QBoxLayout *push_list = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton *push_ok = new QPushButton("Сохранить");
    QPushButton *push_cancel = new QPushButton("Отмена");
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(slot_ok()));
    push_list->addWidget(push_ok);
    push_list->addWidget(push_cancel);
    main_lay->addLayout(line1);
    main_lay->addLayout(line2);
    main_lay->addLayout(push_list);
    this->setLayout(main_lay);
}
edit_prt_xml::~edit_prt_xml()
{
    delete numb;
    delete dat;
}
QPair<QString, QDate> edit_prt_xml::result()
{
    return QPair<QString, QDate>(numb->text(), dat->date());
}
void edit_prt_xml::slot_ok()
{
    emit accept();
}
