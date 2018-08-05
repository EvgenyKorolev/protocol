#ifndef EDITOR_WORKER_H
#define EDITOR_WORKER_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QDialog>
#include <QBoxLayout>
#include <QMessageBox>
#include "string_edit.h"
#include "worker.h"
#include "address.h"

//Виджет - редактор данных работника
class editor_worker : public QDialog
{
    Q_OBJECT
public:
    explicit editor_worker(worker *data, QWidget *parent = 0);
    ~editor_worker();
    bool is_edit();
    worker result();
public slots:
    void name_edit();
    void surname_edit();
    void fname_edit();
    void position_edit();
    void tel_edit();
    void post_edit();
    void login_edit();
    void pass_edit();
    void adr_edit();
    void save_worker();
private:
    worker *main_data;
    QLabel *name_label;
    QLabel *surname_label;
    QLabel *fname_label;
    QLabel *position_label;
    QLabel *tel_label;
    QLabel *post_label;
    QLabel *login_label;
    QLabel *pass_label;
    QLabel *adr_label;
    bool flag_edit;
};

#endif // EDITOR_WORKER_H
