#ifndef FAB_ITEM_H
#define FAB_ITEM_H
#include "treeitem.h"
class tree_item;
// Класс создающий tree_item и выделяющий под него память
class fab_item
{
public:
    fab_item();
    tree_item* create();
};

#endif // FAB_ITEM_H
