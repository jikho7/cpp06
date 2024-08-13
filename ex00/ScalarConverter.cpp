#include "ScalarConverter.hpp"
   
    ScalarConverter::ScalarConverter() : _isPseudoLiteral(false), _isInputValid(false){}
    ScalarConverter::~ScalarConverter(){}
    ScalarConverter::ScalarConverter(const ScalarConverter &other)
    {
        *this = other;
    }

    ScalarConverter& ScalarConverter::operator=(const ScalarConverter &other)
    {
        if (this != &other)
        {
            this->_isInputValid = other._isInputValid;
            this->_isPseudoLiteral = other._isPseudoLiteral;
        }
        return *this;
    }

    void ScalarConverter::convert(std::string literalString)
    {
        ScalarConverter converter;
        int intResult = 0;
        float floatResult = 0;
        double doubleResult = 0;
        char charResult;
        const char *str = literalString.c_str();

        if(converter.isPseudoLiteral(literalString))
        {
            doubleResult =  std::atof(str); 
            floatResult =  static_cast<float>(doubleResult);
        }
        else if (converter.isInputValid(literalString))
        {
            doubleResult =  std::atof(str); 
            intResult = static_cast<int>(doubleResult);
            charResult = intResult;
            floatResult =  static_cast<float>(doubleResult);

        }
        converter.printOutput(str, charResult, intResult, floatResult, doubleResult);
    }

    bool ScalarConverter::isInputValid(std::string literalString)
    {               
        int isDouble = 0;
        int isFloat = 0;
        
        for (std::string::iterator it = literalString.begin(); it != literalString.end(); ++it)
        {
            if (*it == '.')
                isDouble++;
            if (*it == 'f')
                isFloat++;
            if ((!isdigit(*it) && *it != '.' && *it != 'f' && *it != '-' ) || isDouble > 1 || isFloat > 1)
            {
                return (false);
            }
        }
        this->_isInputValid = true;
        return (true);
    }

    void ScalarConverter::printOutput(const char *str, char charResult, int intResult, float floatResult, double doubleResult)
    {
        if (this->_isPseudoLiteral)
        {
            std::cout << "char: impossible" << std::endl;
            std::cout << "int: impossible" << std::endl;
            std::cout << "float: " << floatResult << "f" << std::endl;
            std::cout << "double: " << doubleResult << std::endl;
        }
        else if (this->_isInputValid)
        {
            if (intResult > 3 && intResult < 127)
                std::cout << "char: " << charResult << std::endl;
            else
            {
                std::cout << "char: No displayable" << std::endl;
            }
            std::cout << "int: " << intResult << std::endl;
            std::cout << "float: " << floatResult << ".0f" << std::endl;
            std::cout << "double: " << doubleResult << ".0" << std::endl;
        }
        else
            std::cerr << "Input not valid: " << str << std::endl;
    }

    bool ScalarConverter::isPseudoLiteral(std::string literalString)
    {
        if (literalString == "nan" || literalString == "nanf" || literalString == "-inff" || literalString == "+inff" 
            || literalString == "-inf" || literalString == "+inf")
        {
            this->_isPseudoLiteral = true;
            return (true);
        }
        else
            return (false);
    }