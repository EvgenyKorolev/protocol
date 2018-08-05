#ifndef FAB_OBJ_H
#define FAB_OBJ_H
#include "cp.h"
#include "ktp.h"
// Класс создающий obj и выделяющий под него память

class fab_obj
{
public:
    fab_obj();
    obj* create_cp();
    obj* create_ktp();
};

#endif // FAB_OBJ_H
