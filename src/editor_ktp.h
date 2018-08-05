#ifndef EDITOR_KTP_H
#define EDITOR_KTP_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>
#include <QHeaderView>
#include "editor_address.h"
#include "apparaturs.h"
#include "string_edit.h"
#include "int_editor.h"
#include "my_time_model.h"
#include "my_time_view.h"
#include "app_data_model.h"
#include "app_data_view.h"
#include "app_editor.h"
#include "ktp.h"

// Виджет - редактор КТП
class editor_ktp : public QDialog
{
    Q_OBJECT
public:
    explicit editor_ktp(obj *arg, QWidget *parent = nullptr);
    ~editor_ktp();
    void adr_label_set(QLabel* argl, address* arga);  // Устанвливает или обновляет надпись в разделе физического адреса
    QString get_adr_str(address *arg);                // Возвращает отформатированную строку для установки адреса в виджет
    bool is_edit();
public slots:
    void slot_name_edit();
    void slot_save_cp();
    void slot_volt_edit();
    void slot_address_edit();
    void slot_sh_edit();
private:
    obj *main_data;
    QLabel *name_label;
    QLabel *adr_label;
    QLabel *sh_label;
    QLabel *volt_label;
    QScrollArea *adr_scroll;
    QList<QPair<QTime, QTime>> *max_time_list;
    QList<QPair<QTime, QTime>> *min_time_list;
    QList<apparaturs*> *apprat;
    bool edited;
};

#endif // EDITOR_KTP_H
