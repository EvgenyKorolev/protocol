#ifndef CONST_DATA_EDITOR_H
#define CONST_DATA_EDITOR_H

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
#include <QRegExp>
#include <QRegExpValidator>
/* Редактор значений текстовых констант в типе протокола.
 * Конструтору требуется tuple со значениями 1.Имя переменной 2. Описание 3. Текстовое поле
 */
class const_data_editor : public QDialog
{
    Q_OBJECT
public:
    const_data_editor(const std::tuple<QString, QString, QString> &arg);
public slots:
    void slot_ok();
    std::tuple<QString, QString, QString> result();
private:
    QLineEdit* variation;
    QLineEdit* remark;
    QTextEdit* text_area;
    std::tuple<QString, QString, QString> ret;
};

#endif // CONST_DATA_EDITOR_H
