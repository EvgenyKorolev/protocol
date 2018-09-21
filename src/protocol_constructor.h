#ifndef PROTOCOL_CONSTRUCTOR_H
#define PROTOCOL_CONSTRUCTOR_H
#include "type_adapter.h"
#include "prot_act_adapter.h"
#include <QDialog>
#include <tuple>
#include <memory>
class QDateEdit;
class app_data_view;
class apparaturs;
class obj;
class var_adapter;
class const_adapter;
class protocol;
class QComboBox;
class QLineEdit;
class p_types_model;
class p_types_view;
enum class ask_p{parse, ask}; // указывает парсеру из каких адаптеров брать значения для замены
class protocol_constructor : public QDialog
{
    Q_OBJECT
public:
    protocol_constructor(protocol* act_prot, QWidget* par = nullptr);
    ~protocol_constructor();
public slots:
    void slot_create();
    void slot_change_type();
    void slot_test();

private:
    void closeEvent(QCloseEvent *event);
    QDateEdit* dat_edit;
    app_data_view* app_view;
    QList<apparaturs*>* apprat;
    obj* parent;            // Ссылка на родительский объект
    var_adapter* varad;     // Адаптер для получения данных у родителей протокола
    const_adapter* varconst;// Адаптер для получения констант зависящих от типа протокола
    std::unique_ptr<type_adapter> vartype{new type_adapter()};  // Адаптер для получения констант зависящих от выбранных коллекций типов
    protocol* actual_prot;  // Формируемый объект протокола
    std::unique_ptr<prot_act_adapter> padapt{new prot_act_adapter()}; // Адаптер для объектов настриваемых в конструкторе
    QList<QPair<QString, QString> > types;
    p_types_model* model_type;
    p_types_view* model_view;
    QComboBox* select_type;  // выбор типа протокола
    QComboBox* select_engineer; // Выбор инженера подписавшегося под протоколом
    QLineEdit* enter_number; // Номер протокола
    bool is_tested{false}; // флаг того, окончательное ли формирование протокола.
                    // тип адаптера, type, message, varname
    QString use_adapt(const std::tuple<std::string, std::string, std::string, std::string, std::string> &arg);    // Возвращает значения переменной из различных адаптеров
    QString use_ask_adapt(const std::tuple<std::string, std::string, std::string, std::string, std::string> &arg); // Возвращает значения переменной из заполненного ask_set
    QList<std::tuple<QString, QString, QString, QString, QString>> ask_set;  // переменные значение которых надо спросить у пользователя
// Методы обработки текста
    void prepare(QString& argx);
    void replace_tags(std::string &arg, ask_p arg2 = ask_p::parse);
    void create_varlist();
    QString get_html();
};
#endif // PROTOCOL_CONSTRUCTOR_H
