#ifndef MY_FUNCTION_H
#define MY_FUNCTION_H
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>
#include <QDate>
#include <QTime>
#include <QString>
#include <regex>
#include <string>
#include <vector>
#include <utility>
#include <tuple>

// просто несколько функция для повторного использования. Они преобразуют дату в xml и обратно
namespace my_fnc
{
   int xml_to_date(QDomElement arg, QDate &dat);  // Превращает дату в формате xml в дату в формате QDate
   QDomElement date_to_xml(const QDate &arg);           // Превращает дату в формате QDate в дату в формате xml
   int xml_to_time(QDomElement arg, QTime &tim);  // Превращает время в формате xml во время в формате QDate
   QDomElement time_to_xml(QTime &arg);           // Превращает время в формате QDate во время в формате xml
   std::pair<int, int> serch_teg(const QString& arg, const QString& substr, int pos = 0);           // Возврещет первую и последнюю позицию тега <substr......> поиск начинается с позиции pos
   std::pair<int, int> serch_teg(const std::string& arg, const std::string& substr, int pos = 0,
                                 const std::string &start_delimiter = "<", const std::string &end_delimiter = ">");   // Возврещет первую и последнюю позицию тега <substr......> поиск начинается с позиции pos
   std::vector<std::pair<std::string, std::string> > parse_teg(const std::string& arg, const std::vector<std::string>& lst); //Превращает тэг вида <... a = "b", c = "d"....> в список пар a:b c:d
   float stof(const QString& arg); // Превращает строку в число флоат (удяляя буквы и прочие ненужные символы. Превращает первую найденную последовательность
   // вида [цифры(. или ,)цифры если есть] в число. Остальные символы отбрасываются)
   std::tuple<int, int, int, int> serch_js(const std::string& arg, int pos = 0); // Функция ищет тэги <script type='text/javascript'> ..... </script> и возвращает
   // Первый символ, первый символ поле открывающего тэга script первый символ закрывающего тэга, последний сивол закрывающего тэга для первого найденного тэга
   // Поиск начинается с позиции pos
   QString del_null(const QString& arg); // Удфляет пробелы в начале и конце строки
   QPair<QString, QList<QString>> parse_js(const QString& htm); // Отделяет JavaScript от остального текста
   // Функция parse_js(const QString& htm) должна принимать документ и возвращать пару <документ с вырезанными js, список содержащий js>
}

#endif // MY_FUNCTION_H
