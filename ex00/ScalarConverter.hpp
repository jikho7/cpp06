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
    long    _intResult;
    float   _floatResult;
    double  _doubleResult;
    char    _charResult;

    // Constructor and destructor
    ScalarConverter();
    ~ScalarConverter();

    // Copy constructor and assignement copy
    ScalarConverter(const ScalarConverter &other);
    ScalarConverter &operator=(const ScalarConverter &other);
    
    public :

    // Methodes
    static void convert(std::string literalString);
    void        findType(std:: string literalString);
    void        convertFromStringToType(std::string literalString);
    void        explicitConversion();
    bool        isInputValid(std::string literalString);
    void        printOutput(std::string literalString);
    bool        isPseudoLiteral(std::string literalString);
    void        printPseudoLiteral(std::string literalString);

    int         getType()const;

    void        printChar();
    void        printInt();
    void        printFloat();
    void        printDouble();
};


#endif