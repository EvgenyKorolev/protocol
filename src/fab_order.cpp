#include "fab_order.h"
#include "order.h"

fab_order::fab_order(){}
order* fab_order::create()
{
    return new order();
}
