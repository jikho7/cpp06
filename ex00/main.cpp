#include "ScalarConverter.hpp"
#include <iostream>
#include <string>

int main()
{
    std::string intTest = "-458";

    std::string doubleTest = "3.2";
    std::string negDoubleTest = "-3.2";

    std::string floatTest = "4.34f";
    std::string negFloatTest = "-4.34f";

    ScalarConverter::convert(intTest);

    // ScalarConverter::convert(doubleTest);
    // ScalarConverter::convert(negDoubleTest);

    // ScalarConverter::convert(floatTest);
    // ScalarConverter::convert(negFloatTest);

    return (0);
}