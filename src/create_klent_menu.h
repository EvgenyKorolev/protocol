#ifndef CREATE_KLENT_MENU_H
#define CREATE_KLENT_MENU_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
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
private:
    QLineEdit* name_edit;
    QLineEdit* fail_name_edit;
    bool def_fname{true};
};

#endif // CREATE_KLENT_MENU_H
