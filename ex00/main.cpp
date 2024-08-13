#include "ScalarConverter.hpp"
#include <iostream>
#include <string>

int main(int ac, char** av)
{
    if (ac != 2)
    {
        std::cerr << "Argument error" << std::endl;
        return (1);
    }
    else
    {
        std::string intTest = av[1];
        ScalarConverter::convert(intTest);
    }
    return (0);
}