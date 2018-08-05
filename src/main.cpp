#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDir>
#include <QStyleFactory>
#include "laboratory.h"
#include "directory_app.h"
#include "logger.h"
#include "const_loader.h"

#include <string>
#include <vector>

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    QSplashScreen splash(QPixmap(":/pic/images/st0.png"));
    splash.show();
// ----------------------------------------------------------------
    a.setStyle(QStyleFactory::create("motif"));
    QDir* tmpd = new QDir();
    if (!tmpd->exists("data")){
        tmpd->mkdir("data");
    }
    if (!tmpd->exists("customers")){
        tmpd->mkdir("customers");
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
