#ifndef CONST_DATA_LISTING_H
#define CONST_DATA_LISTING_H

#include "edit_html.h"
#include "const_data_model.h"
#include "const_data_view.h"
#include "const_loader.h"
#include "pair_editor.h"
#include "yes_no.h"
#include "settings.h"
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
#include <QRegExp>
#include <QRegExpValidator>
#include <QFile>
class const_data_listing : public QDialog
{
    Q_OBJECT
public:
    const_data_listing();
    ~const_data_listing();
public slots:
    void set_lst(const QString &key);
    void set_select_lst();
    void add_lst();
    void edit_lst();
    void exit();
    void del();
    void slot_ed_html();
    void slot_copy_list();
private:
    const_data_model *const_model;
    const_data_view *const_view;
    QComboBox* select_type;
    QList<QPair<QString, QString> > key_list;
    const_obj target_object;
    QLabel* varname;
    QString current_key;
    QSortFilterProxyModel* proxy_mod;
};

#endif // CONST_DATA_LISTING_H
