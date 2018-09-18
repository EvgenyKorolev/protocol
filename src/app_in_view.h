#ifndef APP_IN_VIEW_H
#define APP_IN_VIEW_H

#include "apparaturs.h"
#include <QTableView>
#include <QObject>
#include <QMouseEvent>
// Класс представления для выбора прибора из справочника
class app_in_direct;
class app_in_view : public QTableView
{
    Q_OBJECT
public:
    app_in_view(QWidget *par = nullptr);
    void mousePressEvent(QMouseEvent * arg);
    void mouseDoubleClickEvent(QMouseEvent* arg);
    void set_pather(app_in_direct* arg);
    apparaturs result();
public slots:
    void slot_edit();  // Редактировать
    void slot_delete();// Удалить
    void slot_add();   // Создать и добавить
    void slot_return(); // Возвращает выбранный прибор и закрывается
private:
    QPoint _curs;   // Позиция курора
    app_in_direct* _pather; // Ссылка для возврату родителю результата
    apparaturs _ret;
};

#endif // APP_IN_VIEW_H
