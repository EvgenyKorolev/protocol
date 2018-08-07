#include "edit_html.h"

edit_html::edit_html(QString& set_var, QString &set_name, QWidget *par) : QDialog (par)
{
    this->setWindowTitle("Текст протокола " + set_name);
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    fname = "./data/prt_" + set_var +".html";
    QFile con_f(fname);
    if (!con_f.exists()){
        con_f.open(QIODevice::WriteOnly);
        con_f.close();
    }
    QByteArray open_html;
    if (con_f.open(QIODevice::ReadOnly  | QIODevice::Text)){
        open_html = con_f.readAll();
        con_f.close();
    } else {
        QMessageBox::information(nullptr, "Отладка", "Не открывается файл с основным текстом протокола в HTML для чтения");
    }
    main_doc = new QTextEdit();
    main_doc->setMinimumWidth(800);
    main_doc->setMinimumHeight(500);
    main_doc->setPlainText(QString(open_html));
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* push_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton* push_ok = new QPushButton("Сохранить");
    QPushButton* push_cancel = new QPushButton("Отменить");
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(slot_save()));
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    push_lay->addWidget(push_ok);
    push_lay->addWidget(push_cancel);
    main_lay->addWidget(main_doc);
    main_lay->addLayout(push_lay);
    this->setLayout(main_lay);
}
edit_html::~edit_html()
{
    delete main_doc;
}
void edit_html::slot_save()
{
    QFile con_f(fname);
    con_f.copy(fname + ".bak");
    if (con_f.open(QIODevice::WriteOnly)){
        QTextStream stream(&con_f);
        stream << main_doc->toPlainText();
        con_f.close();
    } else {
        QMessageBox::information(nullptr, "Отладка", "Не открывается файл с основным текстом протокола в HTML для записи");
    }
    con_f.close();
    emit accept();
}
