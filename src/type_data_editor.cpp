#include "type_data_editor.h"

type_data_editor::type_data_editor(const std::tuple<QString, QString, QString, QString> &arg)
{
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Переменная:");
    this->setMinimumWidth(800);
    QPushButton* ok_button = new QPushButton("Готово");
    QObject::connect(ok_button, SIGNAL(clicked()), this, SLOT(slot_ok()));
    QPushButton* cancel_button = new QPushButton("Отмена");
    QObject::connect(cancel_button, SIGNAL(clicked()), this, SLOT(reject()));
    QBoxLayout* end_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    end_lay->addWidget(ok_button);
    end_lay->addWidget(cancel_button);
// "Имя:""Тип:""Описание:""Значение:"
    ret = arg;
    variation = new QLineEdit();
    remark = new QLineEdit();
    text_area = new QLineEdit();
    id_type = new QComboBox();
    id_type->addItem("число");
    id_type->addItem("строка");
    QObject::connect(id_type, SIGNAL(currentTextChanged(QString)), this, SLOT(change_type()));
    val = new QRegExpValidator();
    val2 = new QRegExpValidator();
    dval = new QDoubleValidator();
    QRegExp rexp;
    rexp.setPattern("[A-Za-z0-9]{1,30}");
    val->setRegExp(rexp);
    if (std::get<1>(ret) == "" && std::get<3>(ret) == ""){
        std::get<1>(ret) = "dig";
    }
    if (std::get<1>(ret) == "dig"){
        id_type->setCurrentText("число");
        text_area->setValidator(dval);
        text_area->setText(std::get<3>(ret));
    } else if (std::get<1>(ret) == "str"){
        id_type->setCurrentText("строка");
        rexp.setPattern("*");
        val2->setRegExp(rexp);
        text_area->setValidator(val2);
        text_area->setText(std::get<3>(ret));
    } else {
        text_area->setText("Что то не так, собщите об этом разработчику");
    }
    variation->setText(std::get<0>(arg));
    variation->setMinimumWidth(200);
    variation->setMaximumWidth(200);
    variation->setValidator(val);
    remark->setText(std::get<2>(arg));
 //Где то тут надо дописывать !
    QLabel* id_lab = new QLabel();
    id_lab->setText("Тип переменной:");
    id_lab->setMinimumWidth(120);
    id_lab->setMaximumWidth(120);
    QBoxLayout* id_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    id_lay->addWidget(id_lab);
    id_lay->addWidget(id_type);
    QLabel* var_lab = new QLabel();
    var_lab->setText("Имя переменной:");
    var_lab->setMinimumWidth(120);
    var_lab->setMaximumWidth(120);
    QBoxLayout* var_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* rem_lab = new QLabel();
    rem_lab->setText("Описание:");
    rem_lab->setMinimumWidth(80);
    rem_lab->setMaximumWidth(80);
    QLabel* txt_lab = new QLabel();
    txt_lab->setText("Значение:");
    var_lay->addWidget(var_lab);
    var_lay->addWidget(variation);
    var_lay->addWidget(rem_lab);
    var_lay->addWidget(remark);
    id_lay->addWidget(txt_lab);
    id_lay->addWidget(text_area);
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    main_lay->addLayout(var_lay);
    main_lay->addLayout(id_lay);
    main_lay->addLayout(end_lay);
    this->setLayout(main_lay);
}
type_data_editor::~type_data_editor()
{
    delete variation;
    delete id_type;
    delete remark;
    delete text_area;
}
void type_data_editor::slot_ok()
{
    if (variation->text() == "") {
        QMessageBox *tmoer = new QMessageBox();
        tmoer->setWindowTitle("Внимание!");
        tmoer->setText("Необходимо задать не пустое имя переменной");
        tmoer->exec();
        delete tmoer;
        return;
    }
// "Имя:""Тип:""Описание:""Значение:"
    QString type_id;
    if (id_type->currentText() == "число"){
        type_id = "dig";
    } else if (id_type->currentText() == "строка") {
        type_id = "str";
    }
    ret = std::make_tuple(variation->text(), type_id, remark->text(), text_area->text());
    emit accept();
}
std::tuple<QString, QString, QString, QString> type_data_editor::result()
{
    return ret;
}
void type_data_editor::change_type()
{
    if (id_type->currentText() == "число"){
        text_area->setText("");
        text_area->setValidator(dval);
    } else if (id_type->currentText() == "строка") {
        text_area->setText("");
        text_area->setValidator(val2);
    }
}
