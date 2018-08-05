#ifndef CLOSE_CLASS_H
#define CLOSE_CLASS_H

#include <QObject>
#include <QDialog>
#include <QBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>

class close_class : public QDialog
{
    Q_OBJECT
public:
    close_class();
    QString result();
public slots:
    void slot_save();
    void slot_nosave();
    void slot_cancel();
private:
    QString focus;
};

#endif // CLOSE_CLASS_H
