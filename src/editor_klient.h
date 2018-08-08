#ifndef EDITOR_KLIENT_H
#define EDITOR_KLIENT_H

#include <QObject>
#include <QDialog>
#include <QWidget>
#include <QBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QScrollArea>
#include <QMessageBox>
#include <QListView>
#include "details.h"
#include "klient.h"
#include "editor_address.h"
#include "string_edit.h"
#include "int_editor.h"
#include "pair_editor.h"
#include "my_list_model.h"
#include "my_list_view.h"

// Виджет - редактор данных клиента
class editor_klient : public QDialog
{
    Q_OBJECT
public:
    explicit editor_klient(klient *arg, QWidget *parent = 0);
    ~editor_klient();
    void adr_label_set(QLabel* argl, address* arga);                    // Устанвливает или обновляет надпись в разделе физического адреса
    QString get_adr_str(address *arg);                                  // Возвращает отформатированную строку для установки адреса в виджет
    address address_edit(address *arg);                                // Вызов редактора произвольного адреса
    klient result();                        // Фнкция возвращающая объект клиента
    bool is_edit();                         // Были ли изменения
public slots:
    void f_address_edit();                 // Слот вызывающий редактор фактического адреса
    void p_address_edit();                 // Слот вызывающий редактор почтового адреса
    void u_address_edit();                 // Слот вызывающий редактор юридического адреса
    void inn_edit();                       // Слот вызывающий редактор ИНН
    void name_edit();                      // Слот вызывающий редактор названия
    void dir_edit();                       // Слот вызывающий редактор директора :)
    void save_klient();                    // Слот для кнопки ОК
    void slot_full_name_edit(); // Слот редактирования полного наименования
    void slot_email_edit();     // Слот редактирования 'полного наименования электронной почты
private:
    klient *main_obj;
    QLabel *full_name_label;
    QLabel *email_label;
    QLabel *name_label;
    QLabel *inn_label;
    QLabel *dir_n_label;
    QLabel *dir_p_label;
    QLabel *fadr_label;
    QScrollArea *fadr_scroll;
    details *dets;
    QLabel *padr_label;
    QScrollArea *padr_scroll;
    QLabel *uadr_label;
    QScrollArea *uadr_scroll;
    QList<QString> *tellist;
    QList<QString> *faxlist;
    bool flag_edit;

};

#endif // EDITOR_KLIENT_H
