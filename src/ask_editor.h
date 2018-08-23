#ifndef ASK_EDITOR_H
#define ASK_EDITOR_H

#include <QObject>
#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
// Класс запрашивает для ввода список значений
class ask_editor : public QDialog
{
    Q_OBJECT
public:
    ask_editor();
public slots:
    void slot_ok();
};

#endif // ASK_EDITOR_H
