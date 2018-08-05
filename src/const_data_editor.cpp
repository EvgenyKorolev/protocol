#include "const_data_editor.h"

const_data_editor::const_data_editor(const std::tuple<QString, QString, QString> &arg)
{
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Справочник Констант");
    this->setMinimumWidth(800);
    QPushButton* ok_button = new QPushButton("Готово");
    QObject::connect(ok_button, SIGNAL(clicked()), this, SLOT(slot_ok()));
    QPushButton* cancel_button = new QPushButton("Отмена");
    QObject::connect(cancel_button, SIGNAL(clicked()), this, SLOT(reject()));
    QBoxLayout* end_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    end_lay->addWidget(ok_button);
    end_lay->addWidget(cancel_button);
// tuple со значениями 1.Имяпеременной 2. Описание 3. Текстовое поле
    ret = arg;
    variation = new QLineEdit();
    remark = new QLineEdit();
    text_area = new QTextEdit();
    QRegExp rexp;
    rexp.setPattern("[A-Za-z0-9]{1,20}");
    QRegExpValidator* val = new QRegExpValidator();
    val->setRegExp(rexp);
    variation->setValidator(val);
    variation->setText(std::get<0>(arg));
    variation->setMinimumWidth(200);
    variation->setMaximumWidth(200);
    remark->setText(std::get<1>(arg));
    text_area->setText(std::get<2>(arg));
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
    txt_lab->setText("Содержание:");
    var_lay->addWidget(var_lab);
    var_lay->addWidget(variation);
    var_lay->addWidget(rem_lab);
    var_lay->addWidget(remark);
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    main_lay->addLayout(var_lay);
    main_lay->addWidget(txt_lab);
    main_lay->addWidget(text_area);
    main_lay->addLayout(end_lay);
    this->setLayout(main_lay);
}
void const_data_editor::slot_ok()
{
    if (variation->text() == "") {
        QMessageBox *tmoer = new QMessageBox();
        tmoer->setWindowTitle("Внимание!");
        tmoer->setText("Необходимо задать не пустое имя переменной");
        tmoer->exec();
        delete tmoer;
        return;
    }
    ret = std::make_tuple(variation->text(), remark->text(), text_area->toPlainText());
    emit accept();
}
std::tuple<QString, QString, QString> const_data_editor::result()
{
    return ret;
}
