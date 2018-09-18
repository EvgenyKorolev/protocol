#include "protocol_editor.h"

protocol_editor::protocol_editor(protocol* prt)
{
    this->setWindowTitle("Протокол " + prt->get_type() + " № " + prt->get_number() + " от " + prt->get_date().toString());
    this->setWindowIcon(QIcon(":/pic/images/KlogoS.png"));
    end_txt = prt->get_endtxt();
    src_txt = prt->get_prttxt();


    QBoxLayout *push_list = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton *push_ok = new QPushButton("Сохранить");
    QPushButton *push_cancel = new QPushButton("Отмена");
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(save_protocol()));
    push_list->addWidget(push_ok);
    push_list->addWidget(push_cancel);
}
void protocol_editor::save_protocol()
{

}



//QString prt_number{""};  // Номер протокола
//QDate prt_date{0, 0, 0};  // Дата протокола
