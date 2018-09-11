#ifndef CREATE_KLENT_MENU_H
#define CREATE_KLENT_MENU_H

#include "settings.h"
#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <tuple>

class create_klent_menu : public QDialog
{
    Q_OBJECT
public:
    create_klent_menu();
    // Название клиента Путь к файлу Имя файла
    std::tuple<QString, QString, QString> result() const;
public slots:
    void slot_ok();
    void slot_edit_txt();
    void slot_dir_change();
    void slot_dir_edit();
private:
    QLineEdit* name_edit;
    QLineEdit* fail_name_edit;
    QLabel* dirp_lab;
    bool def_fname{true};
};

#endif // CREATE_KLENT_MENU_H
