#ifndef APP_DATA_VIEW_H
#define APP_DATA_VIEW_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QMouseEvent>
#include <QMenu>
#include "app_in_direct.h"
#include "app_editor.h"
//Вид для отображения списка приборов
class app_data_view : public QTableView
{
    Q_OBJECT
public:
    app_data_view(bool *arg, QWidget *par = nullptr);
    void mousePressEvent(QMouseEvent * arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
public slots:
    void slot_edit();  // Редактировать
    void slot_delete();// Удалить
    void slot_add();   // Создать и добавить
    void slot_insert();// Длбавить из справочника
private:
    QPoint _curs;   // Позиция курора
    bool *flag_edit; // Флаг редактирования
};

#endif // APP_DATA_VIEW_H
