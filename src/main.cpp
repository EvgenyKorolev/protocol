#include "mainwindow.h"
#include "laboratory.h"
#include "directory_app.h"
#include "logger.h"
#include "const_loader.h"
#include "settings.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDir>
#include <QStyleFactory>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    QSplashScreen splash(QPixmap(":/pic/images/st0.png"));
    splash.show();
// ----------------------------------------------------------------
    a.setStyle(QStyleFactory::create("motif"));
    settings& tmps = settings::GetInstance();
    QDir* tmpd = new QDir();
    if (!tmpd->exists(tmps.get_data_patch() + tmps.get_data_dir())){
        tmpd->mkdir(tmps.get_data_patch() + tmps.get_data_dir());
    }
    if (!tmpd->exists(tmps.get_data_patch() + tmps.get_customers_dir())){
        tmpd->mkdir(tmps.get_data_patch() + tmps.get_customers_dir());
    }
    delete tmpd;
    type_const_loader::getInstance();
    directory_app::getInstance();
    const_loader::getInstance();
    logger::getInstance();
    laboratory::getInstance();
    MainWindow w;
    splash.finish(&w);
// ----------------------------------------------------------------
    w.show();
    return a.exec();
}
