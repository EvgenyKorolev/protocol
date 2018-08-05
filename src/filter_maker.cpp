#include "filter_maker.h"

filter_maker::filter_maker(QString arg, bool eq)
{
     QString focus_str = arg;
     QString res;
     QRegExp tmp_reg;
         for (int i =0; i < focus_str.size(); ++i){
             res.append("[");
             tmp_reg.setPattern("[a-z]");
             bool flag = true;
             if (tmp_reg.exactMatch(focus_str.at(i))) {
                 res.append(focus_str.at(i));
                 res.append(focus_str.at(i).toUpper());
                 flag = false;
             }
             tmp_reg.setPattern("[а-я]");
             if (tmp_reg.exactMatch(focus_str.at(i))) {
                 res.append(focus_str.at(i));
                 res.append(focus_str.at(i).toUpper());
                 flag = false;
             }
             tmp_reg.setPattern("[A-Z]");
             if (tmp_reg.exactMatch(focus_str.at(i))) {
                 res.append(focus_str.at(i));
                 res.append(focus_str.at(i).toLower());
                 flag = false;
             }
             tmp_reg.setPattern("[А-Я]");
             if (tmp_reg.exactMatch(focus_str.at(i))) {
                 res.append(focus_str.at(i));
                 res.append(focus_str.at(i).toLower());
                 flag = false;
             }
             if (flag){
                 res.append(focus_str.at(i));
             }
             res.append("]");
         }

         if (eq) {
             _res_reg.setPattern(res);
         } else {
             res.push_front(".*");
             res.push_back(".*");
             _res_reg.setPattern(res);
         }
}
QRegExp filter_maker::result()
{
    return _res_reg;
}
