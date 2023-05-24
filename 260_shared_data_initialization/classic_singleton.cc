// Classic Singleton class implementation
#include "classic_singleton.h"

// Static member function to obtain the Singleton object
Singleton* Singleton::get_Singleton()
{
    if (single == nullptr)
        single = new Singleton;
    return single;
}
