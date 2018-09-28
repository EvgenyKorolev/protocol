#include "jstextedit.h"

#include <QtWidgets>
#include <QtWebEngineWidgets>
#include "mainwindow.h"

JStextedit::JStextedit(const QUrl& url)
{
    this->setWindowTitle("Редактор протокола");
    this->setWindowIcon(QIcon(":pic/images/KlogoS.png"));
    setAttribute(Qt::WA_DeleteOnClose, true);
    view = new QWebEngineView(this);
    view->load(url);
    setCentralWidget(view);
}
