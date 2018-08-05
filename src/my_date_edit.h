#ifndef MY_DATE_EDIT_H
#define MY_DATE_EDIT_H
#include <QObject>
#include <QLabel>
#include <QDialog>
#include <QString>
#include <QBoxLayout>
#include <QPushButton>
#include <QDate>
#include <QDateEdit>
// Виджет для редактирования даты
class my_date_edit : public QDialog
{
    Q_OBJECT
public:
    my_date_edit(QDate data, QString lbl);
    ~my_date_edit();
    QDate result();
public slots:
        void save_date();
private:
        QDate main_obj;
        QDateEdit *my_date;
};

#endif // MY_DATE_EDIT_H
