#ifndef APP_EDITOR_H
#define APP_EDITOR_H

#include "ver_data_model.h"
#include "ver_data_view.h"
#include "apparaturs.h"
#include <QObject>
#include <QDialog>
//Виджет - редактор данных прибора
class app_editor : public QDialog
{
    Q_OBJECT
public:
    app_editor(apparaturs *data, bool direct = false, QWidget *parent = nullptr);
    ~app_editor();
    // Если передать direct = true, то кнопки в справочник и из справочника будут скрыты
    bool is_edit();
    apparaturs result();
public slots:
    void name_edit();       // Название прибора
    void mdata_edit();        // Дата... чего-то там, пока непонятно
    void cls_edit();        // Класс прибора (Тип СИ)
    void mnom_edit();       // Заводской номер
    void clas_edit();        // Класс точности
    void save_app();    // Сохранить прибор
    void slot_add_list(); // Добавить прибор в справочник приборов или обновить его если он уже есть в справочнике
    void refresh_lst();  // Обновить прибор из справочника, сели там уже есть такой. Если нет - вызвать меню выбора.
    void refresh();  // Перерисовать надписи
private:
    apparaturs *main_data;
    bool flag_edit;
    QLabel* name_label;       // Название прибора
    QLabel* mdata_label;        // Дата... чего-то там, пока непонятно
    QLabel* cls_label;        // Класс прибора (Тип СИ)
    QLabel* mnom_label;       // Заводской номер
    QLabel* _clas_label;    // Класс точности
    ver_data_view* ver_view;
    ver_data_model *ver_model;
    QList<QPair<QPair<QString, QDate>, QDate>> *ver_list; // Номер свидетельства о поверке, дата поверки, дата очередной поверки
};

#endif // APP_EDITOR_H
