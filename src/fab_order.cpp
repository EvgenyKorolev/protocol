#include "fab_order.h"

fab_order::fab_order(){}
order* fab_order::create()
{
    return new order();
}
