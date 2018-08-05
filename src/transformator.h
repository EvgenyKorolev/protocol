#ifndef TRANSFORMATOR_H
#define TRANSFORMATOR_H

#include <QString>
#include <QDomElement>

// Базовый класс для трансформаторов
class transformator
{
public:
    transformator();
    transformator(transformator *arg);
    transformator(const transformator &arg);   // Конструтор копировщик
    transformator& operator=(const transformator &arg);
    bool operator==(const transformator &arg);
    bool operator!=(const transformator &arg);
    virtual ~transformator();

    void set_type(QString arg);       // Установливает тип трансфоматора
    QString get_type() const;               // Возвращает тип трансфоматора
    void set_mnom(QString arg);       // Установливает заводской №:
    QString get_mnom() const;               // Возвращает заводской №:
    void set_cls(QString arg);        // Установливает класс точности
    QString get_cls() const;                // Возвращает класс точности
    void set_nom_power(QString arg);  // Установливает номинальная полная мощность нагрузки Sн для указанного класса точности, ВА:
    QString get_nom_power() const;          // Возвращает номинальная полная мощность нагрузки Sн для указанного класса точности, ВА:
    void set_obm(QString arg);        // Установливает схема соединения обмоток (усл. обозначение)
    QString get_obm() const;                // Возвращает схема соединения обмоток (усл. обозначение)
    void set_nom_u_2(QString arg);    // Установливает номинальное напряжение основной вторичной обмотки U2 ном, В
    QString get_nom_u_2() const;            // Возвращает номинальное напряжение основной вторичной обмотки U2 ном, В
    void set_nom_u_1(QString arg);    // Установливает номинальное напряжение первичной обмотки U1 ном, кВ
    QString get_nom_u_1() const;            // Возвращает номинальное напряжение первичной обмотки U1 ном, кВ
    void set_f1();            // Фаз будет 1
    void set_f3();           // Фаз будет 3
    void set_f(uint arg);       // Установливает сколько фаз у нас (1 или 3), но явного ограничения нет
    uint test_f() const;              // Узнаём скольки фазный трансформатор
    QDomElement make_xml();
    int load_xml(QDomNode *arg);

    int load_db();
    int save_db();

protected:
    QString _type;       // Тип трансфоматора
    QString _mnom;       // Заводской №:
    QString _cls;        // Класс точности
    QString _nom_power;  // Номинальная полная мощность нагрузки Sн для указанного класса точности, ВА:
    QString _obm;        // Схема соединения обмоток (усл. обозначение)
    QString _nom_u_2;    // Номинальное напряжение основной вторичной обмотки U2 ном, В
    QString _nom_u_1;    // Номинальное напряжение первичной обмотки U1 ном, кВ
    uint _f;            // Сколько фаз (1 или 3)
};
#endif // TRANSFORMATOR_H
