#ifndef LOGGER_H
#define LOGGER_H

#include "settings.h"
#include <QObject>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QTextStream>
#include <QDate>
// Этот класс принимает строку в слот и записывает её в файл лога
// Надо сделать ему виртуальный конструктор и тогда получится одиночка :)
class logger : public QObject
{
private:
    logger();
    logger(const logger&);
    logger& operator=(logger&);
public:
    static logger& getInstance(){
        static logger instance;
        return instance;
    }
    ~logger();
    void add_log(QString my_log);
private:
    QFile *log;
    QTextStream log_writer;
};

#endif // LOGGER_H
