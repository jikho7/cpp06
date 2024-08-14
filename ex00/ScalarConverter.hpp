#ifndef SCALAR_HPP
#define SCALAR_HPP

#include <string>
#include <cctype>
#include <stdlib.h>
#include <iostream>
#include <ostream>
#include <limits>

#define INT 0
#define FLOAT 1
#define DOUBLE 2
#define CHAR 3
#define PSEUDOLITERALNAN 4
#define PSEUDOLITERALINF 5


class ScalarConverter
{
        int     _type;
        long     _intResult;
        float   _floatResult;
        double  _doubleResult;
        char    _charResult;
        bool    _outOfRange;

        ScalarConverter();
        ~ScalarConverter();

    public :
        ScalarConverter(const ScalarConverter &other);
        ScalarConverter &operator=(const ScalarConverter &other);

        static void convert(std::string literalString);
        bool        isInputValid(std::string literalString);
        void        printOutput(std::string literalString);
        void        printPseudoLiteral(std::string literalString);

        bool        isPseudoLiteral(std::string literalString);
        void        findType(std:: string literalString);
        void        convertFromStringToType(std::string literalString);
        void        explicitConversion();
        int         getType()const;
        void        printChar();
        void        printInt();
        void        printFloat();
        void        printDouble();
};


#endif