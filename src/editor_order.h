#ifndef EDITOR_ORDER_H
#define EDITOR_ORDER_H

#include <QObject>
#include <QDialog>
#include <QWidget>
#include <QDate>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QDateEdit>
#include <QLineEdit>
#include "order.h"
#include "my_date_edit.h"

//Виджет - редактор данных заявки
class editor_order : public QDialog
{
    Q_OBJECT
public:
    explicit editor_order(order *data, QWidget *parent = 0);
    ~editor_order();
    order result();
public slots:
    void date_edit();
    void save_order();
private:
    order *main_data;
    QLabel *name_label;
    QLineEdit *_name_edit;
    QLineEdit *_number_edit;
    QLabel *date_label;
    QLabel *number_label;
};

#endif // EDITOR_ORDER_H
