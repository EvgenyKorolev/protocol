#include "logger.h"

logger::logger()
{
    settings& tmps = settings::GetInstance();

    log = new QFile(tmps.get_data_patch() + tmps.get_data_dir() + "/prt.log");
    log_writer.setCodec("UTF-8");
    if(!log->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) QMessageBox::information(nullptr, "Отладка", "Не открывается файл с логами");
    log_writer.setDevice(log);
}
logger::~logger()
{
   this->log->close();
   delete log;
}
void logger::add_log(QString my_log)
{
    this->log_writer << QDateTime::currentDateTime().toString(Qt::SystemLocaleShortDate) << " : "<< my_log  << ('\n');
}

