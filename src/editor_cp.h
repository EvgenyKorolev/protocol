#ifndef EDITOR_CP_H
#define EDITOR_CP_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>
#include <QHeaderView>
#include "transformator.h"
#include "editor_address.h"
#include "apparaturs.h"
#include "string_edit.h"
#include "int_editor.h"
#include "my_time_model.h"
#include "my_time_view.h"
#include "app_data_model.h"
#include "app_data_view.h"
#include "app_editor.h"
#include "editor_trans.h"
#include "cp.h"

// Виджет - редактор центра питания
class cp;
class editor_cp : public QDialog
{
    Q_OBJECT
public:
    editor_cp(obj *arg, QWidget *parent = nullptr);
    ~editor_cp();
    void adr_label_set(QLabel* argl, address* arga);  // Устанвливает или обновляет надпись в разделе физического адреса
    QString get_adr_str(address *arg);                // Возвращает отформатированную строку для установки адреса в виджет
    void tr_label_set(QLabel* argl, transformator* arga);  // Устанвливает или обновляет надпись в разделе трансформатора
    QString get_tr_str(transformator *arg);           // Возвращает отформатированную строку для установки трансформатора в виджет
    bool is_edit();
public slots:
    void slot_name_edit();
    void slot_save_cp();
    void slot_volt_edit();
    void slot_address_edit();
    void slot_sh_edit();
    void slot_tr_edit();
private:
    obj* main_data;
    QLabel* name_label;
    QLabel* adr_label;
    QLabel* sh_label;
    QLabel* volt_label;
    QLabel* _tr_label;
    QScrollArea* _tr_scroll;
    QScrollArea* adr_scroll;
    QList<QPair<QTime, QTime>>* max_time_list;
    QList<QPair<QTime, QTime>>* min_time_list;
    QList<apparaturs*>* apprat;
    bool edited;
};

#endif // EDITOR_CP_H
