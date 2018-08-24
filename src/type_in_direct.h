#ifndef TYPE_IN_DIRECT_H
#define TYPE_IN_DIRECT_H

#include <QObject>
#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QComboBox>
#include <QLineEdit>
#include <QString>
#include <QLabel>
#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QVariant>
#include <tuple>
#include "filter_maker.h"
#include "type_in_view.h"
#include "p_types_model.h"
#include "type_const_loader.h"

class type_in_view;
class type_in_direct : public QDialog
{
    Q_OBJECT
public:
    type_in_direct();
  //  ~type_in_direct();
    void result();
    std::tuple<QString, QString, QString, QString> get_result();
public slots:
    void slot_reset_list();
    void slot_filtr();
private:
    p_types_model* apdm;
    type_in_view* apdv;
    QComboBox* find_str;
    QComboBox* find_status;
    QLineEdit* find_ar;
    std::tuple<QString, QString, QString, QString> ret;
};

#endif // TYPE_IN_DIRECT_H
