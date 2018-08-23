#include "ask_editor.h"

ask_editor::ask_editor()
{
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);

    QPushButton* ok_but = new QPushButton("Готово");
    QPushButton* cancel_but = new QPushButton("Отмена");
    connect(ok_but, SIGNAL(clicked()), this, SLOT(slot_ok()));
    connect(cancel_but, SIGNAL(clicked()), this, SLOT(reject()));
    QBoxLayout* but_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    but_lay->addWidget(ok_but);
    but_lay->addWidget(cancel_but);

    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
void ask_editor::slot_ok()
{
    emit accept();
}
