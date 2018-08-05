#ifndef FSTRING_EDIT_H
#define FSTRING_EDIT_H

#include <QObject>
#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QLabel>
#include <QDoubleValidator>
// Виджет для ввода строки
class fstring_edit : public QDialog
{
    Q_OBJECT
public:
    fstring_edit(QString *arg, QString *lbl, int mw = 100);
    ~fstring_edit();
    QString result();
public slots:
    void save_string();
private:
    QString _main_obj;
    QLineEdit* _my_line;
};

#endif // FSTRING_EDIT_H
