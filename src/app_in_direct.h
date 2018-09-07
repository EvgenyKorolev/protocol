#ifndef APP_IN_DIRECT_H
#define APP_IN_DIRECT_H

#include "direct_app_model.h"
#include "app_in_view.h"
#include "filter_maker.h"
#include <QObject>
#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QComboBox>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QVariant>

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
