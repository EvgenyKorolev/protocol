#ifndef ASK_VIEW_H
#define ASK_VIEW_H

#include <QObject>
#include <QMouseEvent>
#include <QMenu>
#include <QTableView>
#include <QVariant>
// Класс представления для диалога ввода значений недоступных автоматически
class ask_view : public QTableView
{
    Q_OBJECT
public:
    ask_view();
};

#endif // ASK_VIEW_H
