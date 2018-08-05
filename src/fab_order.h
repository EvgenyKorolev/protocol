#ifndef FAB_ORDER_H
#define FAB_ORDER_H
#include "order.h"
// Класс создающий order и выделяющий под него память

class order;
class fab_order
{
public:
    fab_order();
    order* create();
};

#endif // FAB_ORDER_H
