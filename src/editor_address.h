#ifndef EDITOR_ADDRESS_H
#define EDITOR_ADDRESS_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QDialog>
#include "address.h"
#include "editor_klient.h"
// Виджет - редактор адреса

class editor_address: public QDialog
{
    Q_OBJECT
public:
    explicit editor_address(address *arg, QWidget *par = 0);
    address close_ret();
    ~editor_address();
public slots:
    void adr_save();
private:
    address* _obj_adr;
    QLineEdit* _country_edit;
    QLineEdit* _state_edit;
    QLineEdit* _state_class_edit;
    QLineEdit* _state_distr_edit;
    QLineEdit* _city_edit;
    QLineEdit* _city_class_edit;
    QLineEdit* _district_edit;
    QLineEdit* _street_edit;
    QLineEdit* _street_class_edit;
    QLineEdit* _building_n_edit;
    QLineEdit* _building_l_edit;
    QLineEdit* _office_n_edit;
    QLineEdit* _office_l_edit;
    QLineEdit* _post_index_edit;
};

#endif // EDITOR_ADDRESS_H
