#ifndef JSTEXTEDIT_H
#define JSTEXTEDIT_H

#include <QMainWindow>
#include <QtWidgets>
QT_BEGIN_NAMESPACE
class QWebEngineView;
class QLineEdit;
QT_END_NAMESPACE

class JStextedit : public QMainWindow
{
    Q_OBJECT
public:
    explicit JStextedit(const QUrl& url);

protected slots:

private:
    QWebEngineView *view;
};

#endif // JSTEXTEDIT_H
