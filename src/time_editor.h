#ifndef TIME_EDITOR_H
#define TIME_EDITOR_H

#include <QObject>
#include <QLabel>
#include <QDialog>
#include <QString>
#include <QBoxLayout>
#include <QPushButton>
#include <QTime>
#include <QTimeEdit>
// Виджет для ввода или редактирования времени
class time_editor : public QDialog
{
    Q_OBJECT
public:
    time_editor(QTime arg, QString lbl);
    ~time_editor();
    QTime get_result();
public slots:
        void save_time();
private:
        QTime time_obj;
        QTimeEdit *my_time;
};

#endif // TIME_EDITOR_H
