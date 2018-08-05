#include "ver_editor.h"
ver_editor::~ver_editor()
{
    delete my_nom;
    delete my_dat1;
    delete my_dat2;
}
ver_editor::ver_editor(QPair<QPair<QString, QDate>, QDate> *arg, QString lbl0, QString lbl1, QString lbl2, QString lbl3) : QDialog()
{
    this->main_obj = arg;
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle(lbl0);
    QBoxLayout *main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QLabel *lbl_1 = new QLabel();
    QLabel *lbl_2 = new QLabel();
    QLabel *lbl_3 = new QLabel();
    lbl_1->setText(lbl1);
    lbl_2->setText(lbl2);
    lbl_3->setText(lbl3);
    this->my_nom = new QLineEdit();
    this->my_dat1 = new QDateEdit();
    this->my_dat2 = new QDateEdit();
    this->my_nom->setText(this->main_obj->first.first);
    this->my_dat1->setDate(this->main_obj->first.second);
    this->my_dat2->setDate(this->main_obj->second);
    QPushButton *my_ok = new QPushButton("Готово");
    QPushButton *my_cancel = new QPushButton("Отмена");
    QObject::connect(my_ok, SIGNAL(clicked()), this, SLOT(save_ver()));
    QObject::connect(my_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QBoxLayout *but_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    but_lay->addWidget(my_ok);
    but_lay->addWidget(my_cancel);
    main_lay->addWidget(lbl_1);
    main_lay->addWidget(my_nom);
    main_lay->addWidget(lbl_2);
    main_lay->addWidget(my_dat1);
    main_lay->addWidget(lbl_3);
    main_lay->addWidget(my_dat2);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
QPair<QPair<QString, QDate>, QDate> ver_editor::result()
{
    return *main_obj;
}
void ver_editor::save_ver()
{
    this->main_obj->first.first = this->my_nom->text();
    this->main_obj->first.second = this->my_dat1->date();
    this->main_obj->second = this->my_dat2->date();
    if (this->main_obj->first.first == ""){
        QMessageBox *tmoer = new QMessageBox();
        tmoer->setWindowTitle("Внимание!");
        tmoer->setText("Нельзя создавать запись о поверке без номера свидетельства");
        tmoer->exec();
        delete tmoer;
    } else {
            emit accept();
    }
}
