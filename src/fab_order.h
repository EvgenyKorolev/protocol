#ifndef FAB_ORDER_H
#define FAB_ORDER_H

// Класс создающий order и выделяющий под него память

class order;
class fab_order
{
public:
    fab_order();
    static order* create();
};

#endif // FAB_ORDER_H
