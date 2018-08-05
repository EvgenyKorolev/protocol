#ifndef VER_EDITOR_H
#define VER_EDITOR_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QDateEdit>
#include <QLineEdit>
#include <QString>
#include <QBoxLayout>
#include <QDate>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
// Виджет для ввода информации о номере свидетельства и даты поверок.
class ver_editor : public QDialog
{
    Q_OBJECT
public:
    ver_editor(QPair<QPair<QString, QDate>, QDate> *arg, QString lbl0, QString lbl1, QString lbl2, QString lbl3);
    ~ver_editor();
    QPair<QPair<QString, QDate>, QDate> result();
public slots:
    void save_ver();
private:
    QPair<QPair<QString, QDate>, QDate> *main_obj;
    QLineEdit *my_nom;
    QDateEdit *my_dat1;
    QDateEdit *my_dat2;
};

#endif // VER_EDITOR_H
