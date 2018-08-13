#ifndef PROT_ACT_ADAPTER_H
#define PROT_ACT_ADAPTER_H
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
    void set_current_data(const QDate& arg);
    void set_current_data(QDate&& arg);
    QDate get_current_data() const;
private:
    QDate current_data{1, 1, 1};
};

#endif // PROT_ACT_ADAPTER_H
