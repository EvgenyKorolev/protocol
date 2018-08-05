#include "fab_item.h"

fab_item::fab_item(){}
tree_item* fab_item::create()
{
    return new tree_item("NULL");
}
