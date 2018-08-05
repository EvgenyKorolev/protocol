#include "fab_obj.h"

fab_obj::fab_obj(){}
obj* fab_obj::create_cp()
{
    return new cp();
}
obj* fab_obj::create_ktp()
{
    return new ktp();
}
