#ifndef PROTOCOL_CONSTRUCTOR_H
#define PROTOCOL_CONSTRUCTOR_H

#include "p_types_model.h"
#include "p_types_view.h"
#include "const_loader.h"
#include "var_adapter.h"
#include "const_adapter.h"
#include "type_adapter.h"
#include "protocol.h"
#include "type_in_direct.h"
#include "my_function.h"
#include "app_data_model.h"
#include "app_data_view.h"
#include "prot_act_adapter.h"
#include <QObject>
#include <QDialog>
#include <QString>
#include <QIcon>
#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QHeaderView>
#include <QPair>
#include <QTextDocument>
#include <QRegExp>
#include <QWebEngineView>
#include <QDateEdit>
#include <tuple>
#include <algorithm>
#include <utility>
#include <memory>

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
    QDateEdit* dat_edit;
    app_data_view* app_view;
    QList<apparaturs*>* apprat;
    obj* parent;            // Ссылка на родительский объект
    var_adapter* varad;     // Адаптер для получения данных у родителей протокола
    const_adapter* varconst;// Адаптер для получения констант зависящих от типа протокола
    type_adapter* vartype;  // Адаптер для получения констант зависящих от выбранных коллекций типов
    protocol* actual_prot;  // Формируемый объект протокола
    std::unique_ptr<prot_act_adapter> padapt{new prot_act_adapter()}; // Адаптер для объектов настриваемых в конструкторе
    QList<QPair<QString, QString> > types;
    p_types_model* model_type;
    p_types_view* model_view;
    QComboBox* select_type;
    bool is_tested{false};
                    // тип адаптера, type, message, varname
    QString use_adapt(const std::tuple<std::string, std::string, std::string, std::string, std::string> &arg);    // Возвращает значения переменной из различных адаптеров
    QList<std::tuple<QString, QString, QString, QString>> ask_set;  // переменные значение которых надо спросить у пользователя
    QList<std::tuple<QString, QString, QString, QString>> var_set; // переменные значение которых должно быть доступно скриптам
// Методы обработки текста
    void prepare(QString& argx);
    void parser_first(QString &argx);
    QString get_html();

};
/*
<_parent_var parent_type="Тип родиельского объекта", message="Введите вот это: ", vname="varname">
Задаёт переменную которую надо подставить из родительских объектов (Клиент, заявка, ЦП, КТП Лаборатории)

<_parent_var parent_type="lab", message="Введите вот это: ", vname="varname">
Задаёт переменную которую надо подставить из родительских объектов (Лаборатории)

<_prot_type type="Тип протокола", message="Введите вот это: ", vname="varname">
Задаёт переменную которую надо подставить из адаптера типа протокола

<_const_type type="Имя набора констант", message="Введите вот это: ", vname="varname">
Задаёт переменную которую надо подставить из адаптера наборов констант

-------------------------------------------------------------------------------------------------

<_set_adapt_var type="Имя переменной", message="Введите вот это: ", vname="varname">
Задаёт переменную которую надо поместить в список переменных для скриптов

<_ask_obj type="число или строка" message="Введите вот это: ", vname="varname">
Задаёт переменную которую должен ввести пользователь
*/
#endif // PROTOCOL_CONSTRUCTOR_H
