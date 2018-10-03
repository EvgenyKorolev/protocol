#include "settings_dialog.h"
#include "settings.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QLabel>

settings_dialog::settings_dialog(QWidget *par) : QDialog(par)
{
    this->setWindowTitle("Настройки программы");
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    this->setMinimumWidth(700);
    QPushButton* push_editor = new QPushButton("Изменить");
    connect(push_editor, SIGNAL(clicked()), this, SLOT(slot_editor_edit()));
    QBoxLayout* editor_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    editor = new QLineEdit();
    editor->setModified(false);
    editor->setText(settings::GetInstance().get_ext_editor());
    QLabel* edl = new QLabel();
    edl->setText("Внешний редактор: ");
    edl->setMinimumWidth(200);
    edl->setMaximumWidth(200);
    editor_lay->addWidget(edl);
    editor_lay->addWidget(editor);
    editor_lay->addWidget(push_editor);
    QPushButton* push_path = new QPushButton("Изменить");
    connect(push_path, SIGNAL(clicked()), this, SLOT(slot_path_edit()));
    QBoxLayout* path_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    path = new QLineEdit();
    path->setText(settings::GetInstance().get_data_patch());
    path->setModified(false);
    QLabel* pdl = new QLabel();
    pdl->setText("Директория данных: ");
    pdl->setMinimumWidth(200);
    pdl->setMaximumWidth(200);
    path_lay->addWidget(pdl);
    path_lay->addWidget(path);
    path_lay->addWidget(push_path);
    QBoxLayout* main_lay = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout* push_lay = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton* push_ok = new QPushButton("Сохранить");
    QPushButton* push_cancel = new QPushButton("Отменить");
    QObject::connect(push_ok, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(push_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    push_lay->addWidget(push_ok);
    push_lay->addWidget(push_cancel);
    main_lay->addLayout(editor_lay);
    main_lay->addLayout(path_lay);
    main_lay->addLayout(push_lay);
    this->setLayout(main_lay);
}
settings_dialog::~settings_dialog()
{
    delete editor;
    delete path;
}
void settings_dialog::slot_save()
{
    settings::GetInstance().set_data_patch(path->text());
    settings::GetInstance().set_ext_editor(editor->text());
    settings::GetInstance().save_ini();
}
void settings_dialog::slot_editor_edit()
{
    QString fn = QFileDialog::getOpenFileName();
    if (fn == "") return;
    editor->setText(fn);
    editor->adjustSize();
}
void settings_dialog::slot_path_edit()
{
    QString fn = QFileDialog::getExistingDirectory();
    if (fn == "") return;
    path->setText(fn);
    path->adjustSize();
}
