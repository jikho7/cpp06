#include "Serializer.hpp"
#include <iostream>

int main()
{
    Data data = {1, 'c', 4.5f, 4.2, "hello"};

    std::cout << "Avant serialize   >>" << "    data adresse :      " << &data << "    i : " << data.i << " c: " << data.c << " f : " << data.f << " d : " << data.d << " str : " << data.str << std::endl;
    
    uintptr_t res = Serializer::serialize(&data);
    std::cout << "Apres serialize   >>" << "    adresse resultat :  " << res << std::endl;

    Data *ptr = Serializer::deserialize(res);
    std::cout << "Apres deserialize >>" << "    ptr adresse :      " << ptr << std::endl;


    std::cout << "check contenu     >>" << "    ptr adresse :       " << ptr << "   i : " << ptr->i << " c: " << ptr->c << " f : " << ptr->f << " d : " << ptr->d << " str : " << ptr->str << std::endl;


    return(0);
}