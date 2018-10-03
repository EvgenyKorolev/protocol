#include "edit_plain_text.h"
#include <QTextEdit>
#include <QString>
#include <QPushButton>
#include <QBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

edit_plain_text::edit_plain_text(const QString& txt, const QString &p_name, QWidget *par) : QDialog (par)
{
    this->setWindowTitle("Скрипты протокола " + p_name);
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    main_doc = new QTextEdit();
    main_doc->setMinimumWidth(800);
    main_doc->setMinimumHeight(500);
    main_doc->setPlainText(txt);
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* push_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton* push_ok = new QPushButton("Сохранить");
    QPushButton* push_cancel = new QPushButton("Отменить");
    QPushButton* push_load = new QPushButton("Зарузить из файла");
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(push_load, SIGNAL(clicked()), this, SLOT(slot_load()));
    push_lay->addWidget(push_ok);
    push_lay->addWidget(push_cancel);
    push_lay->addWidget(push_load);
    main_lay->addWidget(main_doc);
    main_lay->addLayout(push_lay);
    this->setLayout(main_lay);
}
edit_plain_text::~edit_plain_text()
{
    delete main_doc;
}
QString edit_plain_text::result()
{
     return main_doc->toPlainText();
}
void edit_plain_text::slot_load()
{
    QString my_file = QFileDialog::getOpenFileName(this, tr("Выбрать файл c текстом скрипта"));
    if (my_file != ""){
        QFile fl(my_file);
        if (fl.open(QIODevice::ReadOnly)){
            QString tmp_html = fl.readAll();
            main_doc->setPlainText(tmp_html);
        }
    }
}
