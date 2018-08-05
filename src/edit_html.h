#ifndef EDIT_HTML_H
#define EDIT_HTML_H

#include <QObject>
#include <QDialog>
#include <QString>
#include <QTextEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QFile>
#include <QMessageBox>
#include <QTextDocumentWriter>
#include <QByteArray>
#include <QTextStream>

class edit_html : public QDialog
{
    Q_OBJECT
public:
    edit_html(QString& set_var, QString& set_name, QWidget* par = nullptr);
    ~edit_html();
public slots:
    void slot_save();
private:
    QTextEdit* main_doc;
    QString fname;
};

#endif // EDIT_HTML_H
