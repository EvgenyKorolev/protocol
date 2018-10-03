#include "settings.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
settings::settings(){
    bool parse{true};
    QString ini{""};
    if (QFile(".pr_set.conf").exists()){
        main_ini = ".pr_set.conf";
    } else if (QFile(QDir::homePath() + "/.protocol/.pr_set.conf").exists()){
        main_ini = QDir::homePath() + "/.protocol/.pr_set.conf";
    } else if (QFile(QDir::homePath() + "/.pr_set.conf").exists()){
        main_ini = QDir::homePath() + "/.pr_set.conf";
    } else {
        data_patch = QDir::homePath() + "/.protocol/";
        ext_editor = "";
        main_ini = QDir::homePath() + "/.pr_set.conf";
        parse = false;
        save_ini();
    }
    if (parse){
        QFile ini_f(main_ini);
        if (ini_f.open(QIODevice::ReadOnly)){
            QTextStream stream(&ini_f);
            ini = stream.readAll();
            ini_f.close();
            int st = ini.indexOf("patch = ") + 8;
            int sst = ini.indexOf('\n', st);
            data_patch = ini.mid(st, sst - st);
            st = ini.indexOf("editor = ") + 9;
            sst = ini.indexOf('\n', st);
            ext_editor = ini.mid(st, sst - st);

        } else {
            QMessageBox::information(nullptr, "Отладка", "Не открывается файл с настройками");
        }
    }
    QDir tmpd;
    if (!tmpd.exists(data_patch)){
        QMessageBox::information(nullptr, "Внимание", "Невозможно найти или сохранить путь к директории с данными");
    }
}
void settings::save_ini() const
{
    QFile f_ini(main_ini);
    f_ini.open(QIODevice::WriteOnly);
        QString ini = "patch = " + data_patch + "\n" + "editor = " + ext_editor + "\n";
        QTextStream stream(&f_ini);
        stream << ini;
    f_ini.close();
}
