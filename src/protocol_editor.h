#ifndef PROTOCOL_EDITOR_H
#define PROTOCOL_EDITOR_H

#include "protocol.h"
#include <QObject>
#include <QDialog>
#include <QLabel>

// Класс - редактор уже сформированного протокола
class protocol_editor : public QDialog
{
    Q_OBJECT
public:
    protocol_editor(protocol *prt, QWidget *par = nullptr);
    ~protocol_editor();
    bool set_t(const QString& arg);
public slots:
    void save_protocol();
    void edit_var();
    void edit_text();
private:
    QString end_txt;
    QString src_txt;
    QString tmp_num;
    QDate tmp_dat;
    protocol *prot;
    QLabel* number;
    QLabel* date;
};
class QLineEdit;
class QDateEdit;
class edit_prt_xml : public QDialog
{
    Q_OBJECT
public:
    edit_prt_xml(const QString& num, const QDate& dt, QWidget *par = nullptr);
    ~edit_prt_xml();
    QPair<QString, QDate> result();
public slots:
    void slot_ok();
private:
    QLineEdit* numb;
    QDateEdit* dat;
};
#endif // PROTOCOL_EDITOR_H
