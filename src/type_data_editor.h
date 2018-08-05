#ifndef TYPE_DATA_EDITOR_H
#define TYPE_DATA_EDITOR_H

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QBoxLayout>
#include <QPushButton>
#include <tuple>
#include <QString>
#include <QLabel>
#include <QMessageBox>
#include <QComboBox>
/* Редактор значений констант.*/

class type_data_editor : public QDialog
{
    Q_OBJECT
public:
    type_data_editor(const std::tuple<QString, QString, QString, QString> &arg);
    ~type_data_editor();
    std::tuple<QString, QString, QString, QString> result();
public slots:
    void slot_ok();
    void change_type();
private:
    QLineEdit* variation;
    QComboBox* id_type;
    QLineEdit* remark;
    QLineEdit* text_area;
    QRegExpValidator* val2;
    QRegExpValidator* val;
    QDoubleValidator* dval;
    std::tuple<QString, QString, QString, QString> ret;
};

#endif // TYPE_DATA_EDITOR_H
