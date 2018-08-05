#ifndef INT_EDITOR_H
#define INT_EDITOR_H

#include <QObject>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QString>
#include <QDialog>
// Виджет для ввода целочисленного значения
class int_editor : public QDialog
{
    Q_OBJECT
public:
    int_editor(unsigned long long int arg, QString *lbl, int mw = 13);
    int_editor(unsigned int arg, QString lbl, int mw = 7);
    int_editor(int arg, QString lbl, int mw = 7);
    ~int_editor();
    unsigned long long int result();
    unsigned int s_result();
    int i_result();
public slots:
    void save_int(); // Слот для сохранения лонг лонг беззнакового целого
    void s_save_int(); // Слот для сохранения беззнакового целого
    void i_save_int(); // Слот для сохранения целого
private:
    unsigned long long int _main_obj;
    unsigned int _s_main_obj;
    int _i_main_obj;
    QLineEdit* _my_line;
};

#endif // INT_EDITOR_H
