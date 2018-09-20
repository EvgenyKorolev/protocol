#ifndef KTP_H
#define KTP_H

#include "obj.h"

class order;
class obj;
// Класс представляющий КТП
class ktp : public obj
{
public:
    ktp();
    ktp(obj *arg);
    ~ktp() override;
    QString type() const override;           // Возвращает тип записи
    void init(const ktp &arg);            // Инициализирует объект другим объектом
    void init_new(const obj& arg) override;  // Перегруженная функция инициализирует объект другим объектом заменяя уникальные номера протоколов и копируя их данные
    void init(const obj& arg) override;             // Инициализирует объект другим объектом
    void set_up(order *arg) override;        // Устанавливает ссылку на родителя (заказ)
    void set_up(obj *arg) override;          // Инициализирует родителя ЦП
    obj* get_ups() const override;           // Возвращает родителя (ЦП)
    QDomElement make_xml() override;         // Создать xml из объекта
    int load_xml(QDomNode *arg) override;    // Создать объект из xml
    QString get_bd_name() const override;     // Сообщает имя файла БД клиента
    QList<QString> ret_uids() const override;       // Возвращает список существующих протоколов
};
Q_DECLARE_METATYPE(ktp*)
#endif // KTP_H
