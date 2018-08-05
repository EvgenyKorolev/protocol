#ifndef CP_H
#define CP_H
#include <QVariant>
#include <QList>
#include "obj.h"
#include "order.h"
#include "transformator.h"
#include "ktp.h"

// Этот класс - Центр питания
class obj;
class cp : public obj
{
public:
    cp();                               // Конструтор
    cp(order *arg);                     // Конструктор со ссылкой на родителя (заказ)
    cp(const cp &arg);                  // Конструтор копировщик
    cp(obj *arg);                       // Конструтор перегруженный
    ~cp();                              // Деструктор
    cp null_cp();                       // Очищает объект от данных и возвращает пустой объект

    int add_ktp(obj *arg);              // Добавить КТП
    QList<obj*> get_ktp_list() const;   // Возвращает список содержащий КТП
    int clear_ktp_list();               // Очищает список КТП
    int del_top_ktp();                  // Удаляет последний КТП в списке
    int remove_n_ktp(int arg);          // Удаляет КТП с номером arg из списка

    int set_tr(transformator arg);     // Задаёт тип и параметры трансформатора
    transformator get_tr() const;      // Возвращает ссылку на объект установленного в ЦП трансформатора
    virtual void time_ktp();            // Устанавливает у все ктп интервалы соотвествующие ЦП

    QDomElement make_xml() override;             // Создать xml из объекта
    int load_xml(QDomNode *arg) override;    // Создать объект из xml
    QString type() const override;               // Возвращает тип записи
    void init(const cp *arg);           // Инициализирует объект другим объектом
    void init(const obj arg);           // Перегруженная функция инициализирует объект другим объектом
    void init(const obj *arg) override;           // Перегруженная функция инициализирует объект другим объектом

private:
    QList<obj*> ktp_list;                // Относящиеся к центру питания КТП
    transformator _tr;                   // Установленный в центре питания трансформатор

};
Q_DECLARE_METATYPE(cp*)
#endif // CP_H
