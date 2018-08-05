#include "close_class.h"

close_class::close_class()
{
    focus = "cancel";
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setWindowTitle("Внимание");
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* push_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* main_lab = new QLabel();
    main_lab->setText("<p align='center'><b>Сохранить изменеия перед входом?</b></p>");
    QPushButton* save = new QPushButton("Сохранить и выйти");
    save->setMaximumWidth(180);
    save->setMinimumWidth(180);
    QPushButton* nosave = new QPushButton("Выйти без сохранения");
    nosave->setMaximumWidth(180);
    nosave->setMinimumWidth(180);
    QPushButton* cancel = new QPushButton("Отмена");
    cancel->setMaximumWidth(180);
    cancel->setMinimumWidth(180);
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(slot_save()));
    QObject::connect(nosave, SIGNAL(clicked()), this, SLOT(slot_nosave()));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(slot_cancel()));
    push_lay->addWidget(save);
    push_lay->addWidget(nosave);
    push_lay->addWidget(cancel);
    main_lay->addWidget(main_lab);
    main_lay->addLayout(push_lay);
    this->setLayout(main_lay);
}
QString close_class::result()
{
    return focus;
}
void close_class::slot_save()
{
    focus = "save";
    emit accept();
}
void close_class::slot_nosave()
{
    focus = "nosave";
    emit accept();
}
void close_class::slot_cancel()
{
    focus = "cancel";
    emit reject();
}
