#ifndef PAIR_EDITOR_H
#define PAIR_EDITOR_H

#include <QObject>
#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QLabel>
#include <QPair>
#include <QRegExpValidator>
enum class what_line{one, two};
// Виджет для ввода пары строк
class pair_editor : public QDialog
{
    Q_OBJECT
public:
    // Пара строк которая будет установлена в полях ввода. титлы окна. подпись первого поля ввода. подпись второго поля ввода. два минимальных размера полей
    pair_editor(QPair<QString, QString> arg, QString *lbl, QString *lbl1, QString *lbl2, int mw = 100, int mw2 = 100);
    ~pair_editor();
    QPair<QString, QString> result();
    void set_mask(QRegExpValidator *arg_val, what_line arg_l = what_line::one);
public slots:
    void save_pair();
private:
    QPair<QString, QString> main_obj;
    QLineEdit *my_line1;
    QLineEdit *my_line2;
};

#endif // PAIR_EDITOR_H
