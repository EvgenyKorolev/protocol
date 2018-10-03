#ifndef SETTINGS_H
#define SETTINGS_H
#include <QDir>
#include <QString>
class settings
{
    settings();
    settings(const settings&) = default;
    settings& operator=(const settings&) = default;

    QString data_patch{QDir::homePath() + "/.protocol/"};
    QString ext_editor{""};
    QString customers_dir{"customers"};
    QString data_dir{"data"};
    QString help_dir{"help"};
    QString tmp_dir{"temp"};
    QString main_ini{QDir::homePath() + "/.pr_set.conf"};
    unsigned int nm{0};
public:
    static settings& GetInstance(){
        static settings instance;
        return instance;
    }
    QString get_data_patch() const {return  data_patch;}
    QString get_customers_dir() const {return customers_dir;}
    QString get_data_dir() const {return data_dir;}
    QString get_help_dir() const {return help_dir;}
    QString get_temp_dir() const {return tmp_dir;}
    QString get_ext_editor() const {return ext_editor;}
    void set_ext_editor(const QString& arg){ext_editor = arg;}
    void set_data_patch(const QString& arg){data_patch = arg;}
    void save_ini() const;
    unsigned int getnum() {return nm++;}
};

#endif // SETTINGS_H
