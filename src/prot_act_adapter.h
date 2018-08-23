#ifndef PROT_ACT_ADAPTER_H
#define PROT_ACT_ADAPTER_H
#include "worker.h"
#include <QDate>
// Класс для хранения и выдачи данных заполняемых в конструкторе протокола
class prot_act_adapter
{
public:
    prot_act_adapter() = default;
    prot_act_adapter(const prot_act_adapter&) = default;
    prot_act_adapter(prot_act_adapter&&) = default;
    prot_act_adapter& operator=(const prot_act_adapter&) = default;
    prot_act_adapter& operator=(prot_act_adapter&&) = default;
    ~prot_act_adapter() = default;
    QString get_var(const QString& arg, const QString& style);
    void set_current_data(const QDate& arg);
    void set_current_data(QDate&& arg);
    QDate get_current_data() const;
    QString get_engineer() const;
    worker get_engineer_all() const;
    void set_worker(const worker& arg);
    void set_number_prot(const QString& arg);
    QString get_number_prot() const;
private:
    QDate current_data{1, 1, 1};
    worker engineer;
    QString number_prot;
};

#endif // PROT_ACT_ADAPTER_H
