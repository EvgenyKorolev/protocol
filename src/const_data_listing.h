#ifndef CONST_DATA_LISTING_H
#define CONST_DATA_LISTING_H

#include "const_data_model.h"
#include <QDialog>
class const_data_view;
class QComboBox;
class QLabel;
class QWebEngineView;
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
    void slot_w_ed_html();
    void slot_copy_list();
    void slot_new_list();
    void slot_edit_js();
    void handleHtml(QString sHtml);
signals:
    void html(QString sHtml);
private:
    const_data_model *const_model;
    const_data_view *const_view;
    QComboBox* select_type;
    QList<QPair<QString, QString> > key_list;
    const_obj target_object;
    QLabel* varname;
    QString current_key;
    QString end_html_tmp{""};
    QWebEngineView* we;
};

#endif // CONST_DATA_LISTING_H
