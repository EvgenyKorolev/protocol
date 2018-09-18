#ifndef APP_IN_DIRECT_H
#define APP_IN_DIRECT_H

#include "apparaturs.h"
#include <QObject>
#include <QDialog>
class direct_app_model;
class QComboBox;
class QLineEdit;
class app_in_view;
class app_in_direct : public QDialog
{
    Q_OBJECT
public:
    app_in_direct();
    ~app_in_direct();
    void result();
    apparaturs get_result();
public slots:
    void slot_reset_list();
    void slot_filtr();
private:
    direct_app_model* _apdm;
    app_in_view* _apdv;
    QComboBox* _find_str;
    QComboBox* _find_status;
    QLineEdit* _find_ar;
    apparaturs _result;
};

#endif // APP_IN_DIRECT_H
