#ifndef EDIT_PLAIN_TEXT_H
#define EDIT_PLAIN_TEXT_H

#include <QObject>
#include <QDialog>
class QTextEdit;
class edit_plain_text : public QDialog
{
    Q_OBJECT
public:
    edit_plain_text(const QString& txt, const QString &p_name, QWidget* par = nullptr);
    ~edit_plain_text();
    QString result();
public slots:
    void slot_load();
private:
    QTextEdit* main_doc;
};
#endif // EDIT_PLAIN_TEXT_H
