#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <stdint.h>
#include "Data.hpp"

class Serializer
{
    Serializer();
    ~Serializer();
    Serializer& operator=(const Serializer &other);
    Serializer(const Serializer &other);
    
    public:
    static uintptr_t    serialize(Data* ptr);
    static Data*        deserialize(uintptr_t raw);
    
};

#endif

// uintptr_t is an unsigned integer type that is capable of storing a data pointer