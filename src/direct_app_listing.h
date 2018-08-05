#ifndef DIRECT_APP_LISTING_H
#define DIRECT_APP_LISTING_H

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
#include "direct_app_model.h"
#include "direct_app_view.h"
#include "filter_maker.h"

class direct_app_view;
class direct_app_listing : public QDialog
{
    Q_OBJECT
public:
    direct_app_listing();
public slots:
    void slot_reset_list();
    void slot_filtr();
private:
    direct_app_model* _apdm;
    direct_app_view* _apdv;
    QComboBox* _find_str;
    QComboBox* _find_status;
    QLineEdit* _find_ar;
};

#endif // DIRECT_APP_LISTING_H
