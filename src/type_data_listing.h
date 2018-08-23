#ifndef TYPE_DATA_LISTING_H
#define TYPE_DATA_LISTING_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QComboBox>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QVariant>
#include <QMessageBox>
#include <QTextEdit>
#include <tuple>
#include "type_data_model.h"
#include "type_data_view.h"
#include "type_obj.h"
#include "type_const_loader.h"
#include "pair_plus_editor.h"
#include "yes_no.h"

#include "pair_editor.h"

class type_data_listing : public QDialog
{
    Q_OBJECT
public:
    type_data_listing();
    ~type_data_listing();
public slots:
    void set_lst(const QString &key);
    void set_select_lst();
    void edit_lst();
    void add_lst();
    void exit();
    void del();
    void copy_list();
private:
    type_data_model *type_model;
    type_data_view *type_view;
    QComboBox* select_type;
    QList<QString> key_list;
    QList<QString> var_list;
    type_obj target_object;
    QLabel* varname;
    QLabel* cls_lb;
    QString current_key;
    QSortFilterProxyModel* proxy_mod;
    QTextEdit* description;
};

#endif // TYPE_DATA_LISTING_H
