#ifndef EDIT_HTML_H
#define EDIT_HTML_H
#include <QTextEdit>
#include <QObject>
#include <QDialog>
class edit_html : public QDialog
{
    Q_OBJECT
public:
    edit_html(const QString& set_var, const QString& set_name, QWidget* par = nullptr);
    ~edit_html();
public slots:
    void slot_save();
    void slot_load();
private:
    QTextEdit* main_doc;
    QString fname;
};

#endif // EDIT_HTML_H
