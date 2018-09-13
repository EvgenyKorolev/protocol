#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QString>
#include <QVariant>
#include <memory>
#include "klient.h"
#include "order.h"
#include "obj.h"
#include "cp.h"
#include "ktp.h"
#include "protocol.h"
#include <cstring>
#include "fab_item.h"
#include "fab_klient.h"
#include "fab_order.h"
#include "fab_obj.h"

// Базовый элимент главного дерева. Он инкапсулирует клиента или заявку или цп или ктп или протокол
class tree_item
{
public:
     tree_item(klient *data, tree_item *parent);
     tree_item(order *data, tree_item *parent);
     tree_item(cp *data, tree_item *parent);
     tree_item(ktp *data, tree_item *parent);
     tree_item(obj *data, tree_item *parent);
     tree_item(protocol *data, tree_item *parent);
     tree_item();
     tree_item(QString arg);
     ~tree_item();

     int appendChild(tree_item *child);                     // Добавляет дочерний элемент (устанавливает родиительский у добавляемого)
     int create_cild(klient* arg);                          // Создаёт дочерний элимент со всей соотвествующей подветкой
     int create_cild(order* arg);                           // Создаёт дочерний элимент со всей соотвествующей подветкой
     int create_cild(cp* arg);                              // Создаёт дочерний элимент со всей соотвествующей подветкой
     int create_cild(ktp* arg);                             // Создаёт дочерний элимент со всей соотвествующей подветкой
     int create_cild(obj* arg);                             // Создаёт дочерний элимент со всей соотвествующей подветкой
     int create_cild(protocol* arg);
     tree_item* child(int row);                             // Возвращает ссылку на дочерний элемент под номером row в child_items
     int childCount() const;                                // Возвращает колличество дочерних элементов
     int columnCount() const;                               // Число столбцов данных в элементе
     QVariant data(int section, int role = Qt::DisplayRole);                       // Возвращает данные содержащиеся в элементе в виде .... в разном виде :)
     int row() const;                                       // Возвращает номер элимента в списке элементов своего родителя
     tree_item *parent();                                   // Возвращает ссылку на родительский элемент
     int set_parent(tree_item *item);                       // Устанавливает переданный по ссылке элемент в качестве родительского
     int add_chaild(tree_item *item);                       // Устанавливает переданный по ссылке элемент в качестве дочернего (не изменяя родителя добавляемого элимента)
     QString get_status();                                  // Узнать статус (что хронит) элимента данных
     bool is_child(tree_item *item);                        // Является ли элимент переданный в параметре дочерним
     bool setData(QVariant &value);                 // Заполняет итем данными.
     bool remove_child(int row);                    // Удаляет дочерний элимент... наверное?
     bool is_child_at(int row);                // Проверяет есть ли дочерний элимент с таким индексом
     int chaild_nom(tree_item *item);                         // Возвращает номер дочернего элимента

     klient* ret_k();
     order* ret_o();
     obj* ret_c();
     obj* ret_ktp();
     protocol *ret_prot();

 private:  
     void set_kli(klient *data);
     void set_ord(order *data);
     void set_cp(cp *data);
     void set_obj(obj* data);
     void set_ktp(ktp *data);
     void set_cp(obj *data);
     void set_ktp(obj *data);
     void set_prot(protocol *data);

     QList<tree_item*> child_items;
     klient* item_data_k;
     order* item_data_o;
     obj* item_data_c;
     obj* item_data_ktp;
     protocol* item_data_prot;
     tree_item *parent_item;
     QString type;
};
Q_DECLARE_METATYPE(tree_item*)
Q_DECLARE_METATYPE(const tree_item*)
#endif // TREEITEM_H
