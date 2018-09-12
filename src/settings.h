#ifndef SETTINGS_H
#define SETTINGS_H
#include <QMessageBox>
#include <QDir>
#include <QString>
class settings
{
    settings(){
        data_patch = QDir::homePath() + "/.protocol/";
        QDir tmpd;
        if (!tmpd.exists(data_patch)){
            QMessageBox::information(nullptr, "Внимание", "Невозможно найти или сохранить путь к директории с данными");
        }
    }
    settings(const settings&) = default;
    settings& operator=(const settings&) = default;

    QString data_patch{QDir::homePath() + "/.protocol/"};
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
