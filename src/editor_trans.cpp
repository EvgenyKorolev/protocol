#include "editor_trans.h"

editor_trans::editor_trans(transformator *arg, QWidget *par) : QDialog(par)
{
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Трансформатор");
    _data = new transformator();
    _type = new QLineEdit();
    _mnom = new QLineEdit();
    _cls = new QLineEdit();
    _nom_power = new QLineEdit();
    _obm = new QLineEdit();
    _nom_u_2 = new QLineEdit();
    _nom_u_1 = new QLineEdit();
    _f = new QComboBox();
    if (3 == arg->test_f()){
        _f->addItem("3", QVariant(3));
        _f->addItem("1", QVariant(1));
    } else {
        _f->addItem("1", QVariant(1));
        _f->addItem("3", QVariant(3));
    }

    _type->setMaxLength(100);
    _mnom->setMaxLength(100);
    _cls->setMaxLength(100);
    _nom_power->setMaxLength(100);
    _obm->setMaxLength(100);
    _nom_u_2->setMaxLength(100);
    _nom_u_1->setMaxLength(100);

    _type->setInputMask("");
    _mnom->setInputMask("");
    _cls->setInputMask("");
    _nom_power->setInputMask("");
    _obm->setInputMask("");
    _nom_u_2->setInputMask("");
    _nom_u_1->setInputMask("");

    _type->setText(arg->get_type());
    _mnom->setText(arg->get_mnom());
    _cls->setText(arg->get_cls());
    _nom_power->setText(arg->get_nom_power());
    _obm->setText(arg->get_obm());
    _nom_u_2->setText(arg->get_nom_u_2());
    _nom_u_1->setText(arg->get_nom_u_1());

    QLabel* lab_type = new QLabel("Тип трансфоматора: ");
    QLabel* lab_mnom = new QLabel("Заводской №: ");
    QLabel* lab_cls = new QLabel("Класс точности: ");
    QLabel* lab_nom_power = new QLabel("Номинальная полная мощность нагрузки <br> Sн для указанного класса точности, ВА: ");
    QLabel* lab_obm = new QLabel("Схема соединения обмоток <br> (усл. обозначение): ");
    QLabel* lab_nom_u_2 = new QLabel("Номинальное напряжение <br> основной вторичной обмотки U2 ном, В: ");
    QLabel* lab_nom_u_1 = new QLabel("Номинальное напряжение <br> первичной обмотки U1 ном, кВ: ");
    QLabel* lab_f = new QLabel("Сколько фаз: ");

    _type->setMinimumWidth(400);
    _mnom->setMinimumWidth(400);
    _cls->setMinimumWidth(400);
    _nom_power->setMinimumWidth(400);
    _obm->setMinimumWidth(400);
    _nom_u_2->setMinimumWidth(400);
    _nom_u_1->setMinimumWidth(400);

    lab_type->setMinimumWidth(200);
    lab_mnom->setMinimumWidth(200);
    lab_cls->setMinimumWidth(200);
    lab_nom_power->setMinimumWidth(200);
    lab_obm->setMinimumWidth(300);
    lab_nom_u_2->setMinimumWidth(300);
    lab_nom_u_1->setMinimumWidth(300);
    lab_f->setMinimumWidth(300);

    QPushButton *f_ok = new QPushButton("Готово");
    QPushButton *f_cancel = new QPushButton("Отмена");
    QObject::connect(f_ok, SIGNAL(clicked()), this, SLOT(tr_save()));
    QObject::connect(f_cancel, SIGNAL(clicked()), this, SLOT(reject()));

    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* lay_type = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* lay_mnom = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* lay_cls = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* lay_nom_power = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* lay_obm = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* lay_nom_u_2 = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* lay_nom_u_1 = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* lay_f = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *lay_end = new QBoxLayout(QBoxLayout::LeftToRight);

    lay_type->addWidget(lab_type);
    lay_type->addWidget(_type);
    lay_mnom->addWidget(lab_mnom);
    lay_mnom->addWidget(_mnom);
    lay_cls->addWidget(lab_cls);
    lay_cls->addWidget(_cls);
    lay_nom_power->addWidget(lab_nom_power);
    lay_nom_power->addWidget(_nom_power);
    lay_obm->addWidget(lab_obm);
    lay_obm->addWidget(_obm);
    lay_nom_u_2->addWidget(lab_nom_u_2);
    lay_nom_u_2->addWidget(_nom_u_2);
    lay_nom_u_1->addWidget(lab_nom_u_1);
    lay_nom_u_1->addWidget(_nom_u_1);
    lay_f->addWidget(lab_f);
    lay_f->addWidget(_f);
    lay_end->addWidget(f_ok);
    lay_end->addWidget(f_cancel);

    main_lay->addLayout(lay_type);
    main_lay->addLayout(lay_mnom);
    main_lay->addLayout(lay_cls);
    main_lay->addLayout(lay_nom_power);
    main_lay->addLayout(lay_obm);
    main_lay->addLayout(lay_nom_u_2);
    main_lay->addLayout(lay_nom_u_1);
    main_lay->addLayout(lay_f);
    main_lay->addLayout(lay_end);

    this->setLayout(main_lay);
}
transformator editor_trans::close_ret()
{
    return *_data;
}
void editor_trans::tr_save()
{
    _data->set_type(_type->text());
    _data->set_mnom(_mnom->text());
    _data->set_cls(_cls->text());
    _data->set_nom_power(_nom_power->text());
    _data->set_obm(_obm->text());
    _data->set_nom_u_2(_nom_u_2->text());
    _data->set_nom_u_1(_nom_u_1->text());
    _data->set_f(_f->currentText().toUInt());
    emit accept();
}
editor_trans::~editor_trans()
{
    delete _data;
    delete _type;
    delete _mnom;
    delete _cls;
    delete _nom_power;
    delete _obm;
    delete _nom_u_2;
    delete _nom_u_1;
    delete _f;
}

