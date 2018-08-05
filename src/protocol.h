#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <memory>
#include "obj.h"

class obj;
// Этот класс базовый для всех протоколов или единственный - надо будет решить
class protocol
{
public:
    protocol(obj* par);
    ~protocol();
    protocol(protocol& prt);
    protocol(protocol&& prt);
    protocol& operator=(protocol& prt);
    protocol&& operator=(protocol&& prt);
    void set_parent(obj* par);
    obj* get_parent();
    QDomElement make_xml();
    int load_xml(QDomDocument *arg, obj *obt);
private:
    obj* parent;
};

#endif // PROTOCOL_H
