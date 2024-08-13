#ifndef SCALAR_HPP
#define SCALAR_HPP

#include <string>
#include <cctype>
#include <stdlib.h>
#include <iostream>
#include <ostream>

class ScalarConverter
{
        bool _isPseudoLiteral;
        bool _isInputValid;
        ScalarConverter();
        ~ScalarConverter();

    public :
        ScalarConverter(const ScalarConverter &other);
        ScalarConverter &operator=(const ScalarConverter &other);

        static void convert(std::string literalString);
        bool isInputValid(std::string literalString);
        void printOutput(const char *str, char charResult, int intResult, float floatResult, double doubleResult);
        bool isPseudoLiteral(std::string literalString);

};


#endif