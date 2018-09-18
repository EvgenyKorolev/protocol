#ifndef PROTOCOL_EDITOR_H
#define PROTOCOL_EDITOR_H

#include "protocol.h"
#include <QObject>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>

// Класс - редактор уже сформированного протокола
class protocol_editor : public QDialog
{
public:
    protocol_editor(protocol *prt);
public slots:
    void save_protocol();
private:
    QString end_txt;
    QString src_txt;
};

#endif // PROTOCOL_EDITOR_H
