#include "editor_order.h"
editor_order::~editor_order()
{
    delete name_label;
    delete date_label;
    delete number_label;
    delete _name_edit;
    delete _number_edit;
}
editor_order::editor_order(order *data, QWidget *parent) : QDialog(parent)
{
    this->main_data = data;
    this->setWindowTitle("Редактор заявки");
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
//QString uniq;               // Уникальная строка
    this->name_label = new QLabel();
    QLabel *name_ord = new QLabel();
    name_ord->setText("<b>Название зявки: </b>");
    name_ord->setMinimumWidth(140);
    name_ord->setMaximumWidth(140);
    QBoxLayout *name_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    _name_edit = new QLineEdit();
    _name_edit->setText(main_data->get_uniq());
    _name_edit->setMinimumWidth(500);
    name_lay->addWidget(name_ord);
    name_lay->addWidget(_name_edit);
//unsigned int number;        // Уникальный номер
    this->number_label = new QLabel();
    _number_edit = new QLineEdit();
    _number_edit->setInputMask("000000000");
    _number_edit->setText(QString::number(main_data->get_num()));
    _number_edit->setMinimumWidth(200);
    _number_edit->setMaximumWidth(200);
    QLabel *number_ord = new QLabel();
    number_ord->setText("<b>Номер зявки: </b>");
    number_ord->setMinimumWidth(140);
    number_ord->setMaximumWidth(140);
    QBoxLayout *number_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    number_lay->addWidget(number_ord);
    number_lay->addWidget(_number_edit);
//QDate date;                 // Дата создания заявки (можно менять)
    this->date_label = new QLabel;
    date_label->setText(main_data->get_date().toString("dd.MMMM.yyyy"));
    QLabel *date_ord = new QLabel();
    date_ord->setText("<b>Дата: </b>");
    QPushButton *date_ed = new QPushButton("Изменить...");
    date_ed->setMaximumWidth(100);
    date_ed->setMinimumWidth(100);
    QObject::connect(date_ed, SIGNAL(clicked()), this, SLOT(date_edit()));
    QBoxLayout *date_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    date_lay->addWidget(date_ord);
    date_lay->addWidget(date_label);
    date_lay->addWidget(date_ed);
// Строка с номером и датой
    QBoxLayout *nm_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    nm_lay->addLayout(number_lay);
    nm_lay->addLayout(date_lay);
// Финальные кнопки
    QBoxLayout *push_list = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton *push_ok = new QPushButton("Сохранить");
    QPushButton *push_cancel = new QPushButton("Не сохранять");
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(save_order()));
    push_list->addWidget(push_ok);
    push_list->addWidget(push_cancel);
// Расставляем виджеты
    QBoxLayout * edit_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    edit_layout->addLayout(name_lay);
    edit_layout->addLayout(nm_lay);
    edit_layout->addLayout(push_list);
    this->setLayout(edit_layout);
    this->setParent(parent);
}
void editor_order::save_order()
{
    main_data->set_uniq(_name_edit->text());
    main_data->set_num(_number_edit->text().toUInt());
    if (main_data->get_uniq() != ""){
    emit accept();
    }
    else {
        QMessageBox *tmoer = new QMessageBox();
        tmoer->setWindowTitle("Внимание!");
        tmoer->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
        tmoer->setText("Нельзя создавать заявку совсем без имени");
        tmoer->exec();
        delete tmoer;
    }
}
void editor_order::date_edit()
{
 QString tmp1 = "Дата: ";
 QDate tmp2 = this->main_data->get_date();
 my_date_edit *ded = new my_date_edit(tmp2, tmp1);
 if (ded->exec() == QDialog::Accepted){
     this->main_data->set_date(ded->result());
     this->date_label->setText(main_data->get_date().toString("dd.MMMM.yyyy"));
     this->date_label->adjustSize();
 }
 delete ded;
}
order editor_order::result()
{
    return *(this->main_data);
}

