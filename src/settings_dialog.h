#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QObject>
#include <QDialog>
class QLineEdit;
class settings_dialog : public QDialog
{
    Q_OBJECT
public:
    settings_dialog(QWidget *par = nullptr);
    ~settings_dialog();
public slots:
    void slot_save();
    void slot_editor_edit();
    void slot_path_edit();
private:
    QLineEdit* path;
    QLineEdit* editor;
};

#endif // SETTINGS_DIALOG_H
