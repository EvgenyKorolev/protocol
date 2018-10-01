#include "my_function.h"

int my_fnc::xml_to_date(QDomElement arg, QDate &dat)
    {
    dat.setDate(arg.firstChildElement("year").text().toInt(),
        arg.firstChildElement("month").text().toInt(),
        arg.firstChildElement("day").text().toInt());
    return 0;
    }
QDomElement my_fnc::date_to_xml(const QDate &arg)
    {
    QDomDocument xml_ret;
    QDomElement xml_date = xml_ret.createElement("date");
    xml_ret.appendChild(xml_date);

    QDomElement xml_day = xml_ret.createElement("day");
        QDomText xml_day_text = xml_ret.createTextNode(QString::number(arg.day()));
            xml_date.appendChild(xml_day);
            xml_day.appendChild(xml_day_text);
    QDomElement xml_month = xml_ret.createElement("month");
        QDomText xml_month_text = xml_ret.createTextNode(QString::number(arg.month()));
            xml_date.appendChild(xml_month);
            xml_month.appendChild(xml_month_text);
    QDomElement xml_year = xml_ret.createElement("year");
        QDomText xml_year_text = xml_ret.createTextNode(QString::number(arg.year()));
            xml_date.appendChild(xml_year);
            xml_year.appendChild(xml_year_text);

    return xml_date;
    }
int my_fnc::xml_to_time(QDomElement arg, QTime &tim)
{
    tim.setHMS(arg.firstChildElement("hour").text().toInt(), arg.firstChildElement("minut").text().toInt(), arg.firstChildElement("second").text().toInt(), 0);
    return 0;
}
QDomElement my_fnc::time_to_xml(QTime &arg)
{
    QDomDocument xml_ret;
    QDomElement xml_time = xml_ret.createElement("time");
        xml_ret.appendChild(xml_time);

    QDomElement xml_hour = xml_ret.createElement("hour");
        QDomText xml_hour_text = xml_ret.createTextNode(QString::number(arg.hour()));
        xml_time.appendChild(xml_hour);
        xml_hour.appendChild(xml_hour_text);

    QDomElement xml_minut = xml_ret.createElement("minut");
        QDomText xml_minut_text = xml_ret.createTextNode(QString::number(arg.minute()));
        xml_time.appendChild(xml_minut);
        xml_minut.appendChild(xml_minut_text);

    QDomElement xml_second = xml_ret.createElement("second");
        QDomText xml_second_text = xml_ret.createTextNode(QString::number(arg.second()));
        xml_time.appendChild(xml_second);
        xml_second.appendChild(xml_second_text);

        return xml_time;
}
std::pair<int, int> my_fnc::serch_teg(const QString& arg, const QString& substr, int pos)
{
    if (pos < 0 || pos > arg.size()) return std::make_pair(-1, -1);
    if (arg == "") return std::make_pair(-1, -1);
    int pos_t{-1};
    int pos_end{-1};
    int pos_beg{-1};
    pos_beg = arg.indexOf("<" + substr, pos);
    if (pos_beg != -1){
        pos_end = arg.indexOf(">", pos_beg + 1);
        pos_t = arg.indexOf("<", pos_beg + 1);
        if (pos_end == -1){
            return std::make_pair(pos_beg, -1);
        } else if (pos_t != -1 && pos_t < pos_end) {
            return std::make_pair(pos_beg, -1);
        } else if (pos_t == -1 || pos_t > pos_end) {
            return std::make_pair(pos_beg, pos_end);
        }
    }
    return std::make_pair(-1, -1);
}
std::pair<int, int> my_fnc::serch_teg(const std::string& arg, const std::string& substr,
                                      int pos, const std::string &start_delimiter, const std::string &end_delimiter)
{
    if (pos >= (static_cast<int>(arg.size()) - static_cast<int>(substr.size()) + 1)) return std::make_pair(-1, -1);
    std::locale::global(std::locale(""));
    std::string tmps{start_delimiter + "\\s*" + substr + "[^" + end_delimiter +"^" + start_delimiter + "]*" + end_delimiter};
    std::regex reg(tmps.c_str(), std::regex::ECMAScript);
    std::cmatch sr;
    std::string rrt{""};
    auto tmp_str = arg.substr(static_cast<std::size_t>(pos), std::string::npos);
    if (std::regex_search(tmp_str.c_str(), sr, reg)){
        rrt = sr.str(0);
        int m = static_cast<int>(arg.substr(static_cast<std::size_t>(pos), std::string::npos).find(rrt));
        return std::make_pair(m + pos, m + pos + static_cast<int>(rrt.size()) - 1);
    }
    return std::make_pair(-1, -1);
}
std::tuple<int, int, int, int> my_fnc::serch_js(const std::string &arg, int pos)
{
    // <script type='text/javascript'> ..... </script>
    if (pos >= (static_cast<int>(arg.size()) - static_cast<int>(31))) return std::make_tuple(-1, -1, -1, -1);
    std::locale::global(std::locale(""));
    std::string tmps{"\<{1}\\s*script{1}\\s*type{1}\\s*=\\s*[\"\']{1}text\/javascript{1}[\"\']{1}\\s*\>{1}\\s*(.|\\n|\\f)*?\\s*\<{1}\\s*\/script{1}\\s*\>{1}"};
    std::regex reg(tmps.c_str(), std::regex::ECMAScript);
    std::cmatch sr;
    std::string rrt{""};
    std::string tmp_str = arg.substr(static_cast<std::size_t>(pos), std::string::npos);
    if (std::regex_search(tmp_str.c_str(), sr, reg)){
        rrt = sr.str(0);
        int fpos = static_cast<int>(rrt.find('>'));
        int nxpos = static_cast<int>(rrt.rfind('<'));
        int m = static_cast<int>(arg.substr(static_cast<std::size_t>(pos), std::string::npos).find(rrt));
        return std::make_tuple(m + pos, m + pos + fpos, m + pos + nxpos, m + pos + static_cast<int>(rrt.size()) - 1);
    }
    return std::make_tuple(-1, -1, -1, -1);
}
std::vector<std::pair<std::string, std::string>> my_fnc::parse_teg(const std::string& arg, const std::vector<std::string> &lst)
{
    std::vector<std::pair<std::string, std::string>> ret;
    std::string tmps;
    for (auto it : lst){
        std::locale::global(std::locale(""));
        tmps = "\\s*" + it + "\\s*=+\\s*\"[^\"]*\"";
        std::regex reg(tmps.c_str(), std::regex::ECMAScript);
        std::cmatch sr;
        std::string rrt;
        if (std::regex_search(arg.c_str(), sr, reg)){
            rrt = sr.str(0);
            tmps = "\"[^\"]*\"";
            std::cmatch sr2;
            std::regex reg2(tmps.c_str(), std::regex::ECMAScript);
            if (std::regex_search(rrt.c_str(), sr2, reg2)){
                    rrt = sr2.str(0);
                    rrt.erase(rrt.size() - 1, 1);
                    rrt.erase(0, 1);
                    if (it != "message"){
                        while(rrt.find(" ") != std::string::npos){
                            rrt.erase(rrt.find(" "), 1);
                        }
                    }
                    ret.push_back(std::make_pair(it, rrt));
            }
        }

    }
    return  ret;
}
float my_fnc::stof(const QString& arg){
    std::string objstr{arg.toStdString()}, tmps{"-?\\d{1,}[,.]{0,1}\\d{0,}"}; // Сначала храним тут регулярное выражение, а потом результат поиска
    std::regex reg(tmps.c_str(), std::regex::ECMAScript);
    std::cmatch sr;
    if (!(std::regex_search(objstr.c_str(), sr, reg))){
        throw "bad_data";
    }
    std::string ret = sr.str(0);
    std::replace_if(ret.begin(), ret.end(), [](const char& pred)->bool{ return pred == '.';}, ',');
    if (ret == ""){
        throw "bad_data";
    }
    return std::stof(ret);
}
QString my_fnc::del_null(const QString& arg)
{
    QString ret = arg;
    while (ret.size() > 0){
        if (ret.front() == ' ') {
            ret = ret.right(ret.size() - 1);
        } else break;
    }
    while (ret.size() > 0){
        if (ret.back() == ' ') {
            ret = ret.left(ret.size() - 1);
        } else break;
    }
    return ret;
}
QPair<QString, QList<QString>> my_fnc::parse_js(const QString& htm)
{
    QPair<QString, QList<QString>> ret{"", QList<QString>()};
    int pos_beg{0};
    std::tuple<int, int, int, int> reg{std::make_tuple(-1, -1, -1, -1)};
    std::string ret_str = htm.toStdString();
    std::string tmp_js{""};
    do{
        reg = my_fnc::serch_js(ret_str, pos_beg);
        if (std::get<0>(reg) == -1 || std::get<1>(reg) == -1 || std::get<2>(reg) == -1 || std::get<3>(reg) == -1) break;
        tmp_js = ret_str.substr(static_cast<std::size_t>(std::get<1>(reg)) + 1, static_cast<std::size_t>(std::get<2>(reg) - std::get<1>(reg) - 1));
        ret_str.erase(static_cast<std::size_t>(std::get<0>(reg)), static_cast<std::size_t>(std::get<3>(reg) - std::get<0>(reg) + 1));
        ret.second.append(my_fnc::del_null(QString(tmp_js.c_str())));
        pos_beg = std::get<0>(reg);
    } while (pos_beg < static_cast<int>(ret_str.size()));
    ret.first = QString(ret_str.c_str());
    return ret;
}
