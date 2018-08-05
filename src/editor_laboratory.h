#ifndef EDITOR_LABORATORY_H
#define EDITOR_LABORATORY_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QScrollArea>
#include <QString>
#include <QList>
#include <QHeaderView>
#include <QDateEdit>
#include <QScrollArea>
#include "my_date_edit.h"
#include "laboratory.h"
#include "address.h"
#include "worker.h"
#include "details.h"
#include "int_editor.h"
#include "pair_editor.h"
#include "editor_address.h"
#include "workers_data.h"
#include "workers_view.h"

// Виджет - редактор данных лаборатории
class editor_laboratory : public QDialog
{
    Q_OBJECT
public:
    explicit editor_laboratory(QWidget *parent = nullptr);
    ~editor_laboratory();
    void adr_label_set(QLabel* argl, address* arga);     // Устанвливает или обновляет надпись в разделе физического адреса
    QString get_adr_str(address *arg);                   // Возвращает отформатированную строку для установки адреса в виджет
    address address_edit(address *arg);                  // Вызов редактора произвольного адреса
    laboratory *result();                        // Фнкция возвращающая объект лаборатории
    bool is_edit();
public slots:
    void slot_att_edit();        // Слот вызывающий редактор аттестата акредитации
    void slot_name_edit();       // Слот вызывающий редактор названия
    void f_address_edit();       // Слот вызывающий редактор фактического адреса
    void p_address_edit();       // Слот вызывающий редактор почтового адреса
    void u_address_edit();       // Слот вызывающий редактор юридического адреса
    void inn_edit();             // Слот вызывающий редактор ИНН
    void dir_edit();             // Слот вызывающий редактор директора :)
    void save_lab();             // Слот для кнопки ОК
    void att_data_edit();        // Дата

private:
    laboratory *main_obj;
    bool edited;
    QLabel *name_label;
    QLabel *att_label;
    QLabel *adr_lab;
    details *det;
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
    QList<worker> workers_list;
    QLabel* att_data_label;
};

#endif // EDITOR_LABORATORY_H
