#ifndef PAIR_PLUS_EDITOR_H
#define PAIR_PLUS_EDITOR_H

#include <QObject>
#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QRegExpValidator>
#include <tuple>
enum class w_line{one, two};
// Виджет для ввода пары строк и одного текстового поля

class pair_plus_editor : public QDialog
{
    Q_OBJECT
public:
    pair_plus_editor(std::tuple<QString, QString, QString> arg, QString& lbl, QString& lbl1, QString& lbl2, QString& lbl3, int mw = 200, int mw2 = 200, int mw3 = 200);
    ~pair_plus_editor();
    std::tuple<QString, QString, QString> result();
    void set_mask(QRegExpValidator *arg_val, w_line arg_l = w_line::one);
public slots:
    void slot_save();
private:
    std::tuple<QString, QString, QString> main_obj;
    QLineEdit *my_line1;
    QLineEdit *my_line2;
    QTextEdit *my_txt;
};

#endif // PAIR_PLUS_EDITOR_H
