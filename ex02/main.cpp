#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <typeinfo>
#include <cstdlib>
#include <ctime>

Base * generate(void)
{
    Base *newObject = NULL;
    time_t timer;
    unsigned int res = time(&timer);
    unsigned int random = (rand() * res) % 100;

    if (random < 33)
        newObject = new A();
    else if (random < 66)
        newObject = new B();
    else
        newObject = new C();
    return (newObject);
}

void identify(Base* p)
{
    A *a = dynamic_cast<A*>(p);
    if (a != NULL)
        std::cout << "A" << std::endl;
    else
    {
        B *b = dynamic_cast<B*>(p);
        if (b != NULL)
            std::cout << "B" << std::endl;
        else
        {
            C *c = dynamic_cast<C*>(p);
            if (c != NULL)
                std::cout << "C" << std::endl;
        }      
    }
}

void identify(Base& p)
{
    try
    {
        A &a = dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        (void)a;

    }
    catch (std::bad_cast &bc){}
    try
    {
        B &b = dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        (void)b;
    }
    catch (std::bad_cast &bc){}
    try
    {
        C &c = dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        (void)c;

    }
    catch (std::bad_cast &bc){}
}

int main()
{
    Base *test = generate();

    identify(test);
    identify(*test);
    delete test;
    return (0);
}