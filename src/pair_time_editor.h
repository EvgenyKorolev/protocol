#ifndef PAIR_TIME_EDITOR_H
#define PAIR_TIME_EDITOR_H

#include <QObject>
#include <QLabel>
#include <QDialog>
#include <QString>
#include <QBoxLayout>
#include <QPushButton>
#include <QTime>
#include <QDateEdit>
#include <QPair>
#include <QTimeEdit>
// Виджет для ввода пары дат
class pair_time_editor : public QDialog
{
    Q_OBJECT
public:
    pair_time_editor(QPair<QTime, QTime> arg, QString lbl1, QString lbl2);
    ~pair_time_editor();
    QPair<QTime, QTime> get_result();
public slots:
    void save_time();
private:
    QPair<QTime, QTime> time;
    QTimeEdit *editor1;
    QTimeEdit *editor2;
};

#endif // PAIR_TIME_EDITOR_H
