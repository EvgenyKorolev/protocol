#include "ask_editor.h"

ask_editor::ask_editor(const QList<tuple_qss5> &arg)
{
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    this->setWindowTitle("Редактор значений в протоколе");
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setMinimumWidth(650);
    this->setMinimumHeight(400);
    QLabel* main_lbl = new QLabel();
    main_lbl->setText("Введитие значения необходимые для корректного заполнения протокола:");
    QPushButton* ok_but = new QPushButton("Готово");
    QPushButton* cancel_but = new QPushButton("Отмена");
    connect(ok_but, SIGNAL(clicked()), this, SLOT(slot_ok()));
    connect(cancel_but, SIGNAL(clicked()), this, SLOT(reject()));
    QBoxLayout* but_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    but_lay->addWidget(ok_but);
    but_lay->addWidget(cancel_but);
    data_model = new ask_model(arg);
    proxy_mod = new QSortFilterProxyModel();
    proxy_mod->setSourceModel(data_model);
    data_view = new ask_view();
    data_view->setModel(proxy_mod);
    data_view->setColumnWidth(0, 500);
    data_view->horizontalHeader()->setStretchLastSection(true);
    data_view->scrollToBottom();
    data_view->setSortingEnabled(true);
    ask_delegat* delegat = new ask_delegat();
    data_view->setItemDelegateForColumn(1, delegat);
    main_lay->addWidget(main_lbl);
    main_lay->addWidget(data_view);
    main_lay->addLayout(but_lay);
    this->setLayout(main_lay);
}
void ask_editor::slot_ok()
{
    emit accept();
}
ask_editor::~ask_editor()
{
    delete data_model;
    delete data_view;
    delete proxy_mod;
}
