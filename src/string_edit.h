#ifndef STRING_EDIT_H
#define STRING_EDIT_H

#include <QObject>
#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QLabel>
// Виджет для ввода строки
class string_edit : public QDialog
{
    Q_OBJECT
public:
    string_edit(QString *arg, QString *lbl, int mw = 100);
    ~string_edit();
    QString result();
public slots:
    void save_string();
private:
    QString main_obj;
    QLineEdit * my_line;
};

#endif // STRING_EDIT_H
