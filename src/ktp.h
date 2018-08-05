#ifndef KTP_H
#define KTP_H

#include "order.h"
#include "obj.h"

class order;
class obj;

// Класс представляющий КТП
class ktp : public obj
{
public:
    ktp();
    ktp(obj *arg);
    ~ktp();
    QString type() const override;           // Возвращает тип записи
    void init(ktp *arg);            // Инициализирует объект другим объектом
    void init(obj *arg);            // Инициализирует объект другим объектом
    void init(obj arg) override;             // Инициализирует объект другим объектом
    void set_up(order *arg) override;        // Устанавливает ссылку на родителя (заказ)
    void set_up(obj *arg) override;          // Инициализирует родителя ЦП
    obj* get_ups() const override;           // Возвращает родителя (ЦП)
    QDomElement make_xml() override;         // Создать xml из объекта
    int load_xml(QDomNode *arg) override;    // Создать объект из xml
private:
    obj *ups;
};
Q_DECLARE_METATYPE(ktp*)
#endif // KTP_H
