#ifndef SETTINGS_H
#define SETTINGS_H
#include <QMessageBox>
#include <QDir>
#include <QString>
class settings
{
    settings(){
        QDir us_dir;
        us_dir.mkdir(QDir::homePath() + "/.protocol/");
        data_patch = QDir::homePath() + "/.protocol/";
        QFile tester_ini(data_patch);
        if (!tester_ini.open(QIODevice::ReadWrite | QIODevice::Text)){
            QMessageBox::information(nullptr, "Внимание", "Невозможно найти или сохранить путь к директориис данными");
        }
    }
    settings(const settings&) = default;
    settings& operator=(const settings&) = default;

    QString data_patch{"/home/admin/prg/test_data/"};
    QString customers_dir{"customers"};
    QString data_dir{"data"};
    QString help_dir{"help"};

public:
    static settings& GetInstance(){
        static settings instance;
        return instance;
    }
    QString get_data_patch() const {return  data_patch;}
    QString get_customers_dir() const {return customers_dir;}
    QString get_data_dir() const {return data_dir;}
    QString get_help_dir() const {return help_dir;}
};

#endif // SETTINGS_H
