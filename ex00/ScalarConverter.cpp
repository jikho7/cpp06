#include "ScalarConverter.hpp"
   
    ScalarConverter::ScalarConverter() : _type(0){}
    ScalarConverter::~ScalarConverter(){}

    ScalarConverter::ScalarConverter(const ScalarConverter &other){
        *this = other;}

    ScalarConverter& ScalarConverter::operator=(const ScalarConverter &other)
    {
        if (this != &other){}
        return *this;
    }

    void ScalarConverter::convert(std::string literalString)
    {
        ScalarConverter converter;

        converter.findType(literalString);

        if((converter.getType() != PSEUDOLITERALNAN && converter.getType() != PSEUDOLITERALINF) && converter.isInputValid(literalString))
        {
            converter.convertFromStringToType(literalString);
            converter.explicitConversion();
            converter.printOutput(literalString);
        }
        if((converter.getType() == PSEUDOLITERALNAN || converter.getType() == PSEUDOLITERALINF))
        {
            converter.printOutput(literalString);
        }
    }

    void ScalarConverter::findType(std::string literalString)
    {
        this->_type = INT;
        if (!isPseudoLiteral(literalString))
        {
            for (std::string::iterator it = literalString.begin(); it != literalString.end(); ++it)
            {
                if (*it == '.')
                {
                    this->_type = DOUBLE;
                }
                if (*it == 'f' && isdigit(*(it - 1 )))
                {
                    this->_type = FLOAT;
                }
                else if (isalpha(*it))
                    this->_type = CHAR;
            }
        }
        std::cout << "type : " << this->_type << std::endl;
    }

bool ScalarConverter::isInputValid(std::string literalString)
{
    int isDouble = 0;
    int isFloat = 0;
    bool hasDecimal = false;
    bool hasDigitAfterDecimal = false;

    for (std::string::iterator it = literalString.begin(); it != literalString.end(); ++it)
    {
        if (std::isalpha(*it) && (it + 1) == literalString.end())
            return true;
        if (*it == '.')
        {
            isDouble++;
            hasDecimal = true;
        }
        else if (hasDecimal && isdigit(*it))
        {
            hasDigitAfterDecimal = true;
        }
        if (*it == 'f')
        {
            isFloat++;
            if (it != literalString.end() - 1 || !hasDecimal || !hasDigitAfterDecimal)
            {
                std::cerr << "Input is not valid.." << std::endl;
                return false;
            }
        }
        if ((*it != '-') && (isDouble > 1 || isFloat > 1))
        {
            std::cerr << "Input is not valid." << std::endl;
            return false;
        }
    }
    return true;
}

    void ScalarConverter::printOutput(std::string literalString)
    {
        if (isPseudoLiteral(literalString))
            ScalarConverter::printPseudoLiteral(literalString);
        else
        {
            if (isprint(this->_charResult))
                std::cout << "char: " << this->_charResult << std::endl;
            else
                std::cout << "char: No displayable" << std::endl;
            std::cout << "int: " << this->_intResult << std::endl;
            if (this->_floatResult == static_cast<int>(this->_floatResult))
                std::cout << "float: " << this->_floatResult << ".0f" << std::endl;
            else
                std::cout << "float: " << this->_floatResult << "f" << std::endl;

            if (this->_doubleResult == static_cast<int>(this->_doubleResult))
                std::cout << "double: " << this->_doubleResult << ".0" << std::endl;
            else
                std::cout << "double: " << this->_doubleResult << std::endl;
        }
    }


    void ScalarConverter::convertFromStringToType(std::string literalString)
    {
        const char *str = literalString.c_str();
 
        switch(this->_type)
        {
            case(INT):
                this->_intResult = std::atoi(str);
                break;
            case(FLOAT):
                this->_floatResult =  std::atof(str);
                break;
            case(DOUBLE):
                this->_doubleResult =  std::strtod(str, NULL);
                break;
            default:
                break;
        }
    }

    void ScalarConverter::explicitConversion()
    {
        switch(this->_type)
        {
            case(INT):
                this->_floatResult = static_cast<float>(this->_intResult);
                this->_charResult = this->_intResult;
                this->_doubleResult =  static_cast<double>(this->_intResult);
                break;
            case(FLOAT):
                this->_intResult = static_cast<int>(this->_floatResult);
                this->_doubleResult = static_cast<double>(this->_floatResult);
                this->_charResult = this->_intResult;
                break;
            case(DOUBLE):
                this->_intResult =  static_cast<double>(this->_doubleResult);
                this->_floatResult = static_cast<float>(this->_doubleResult);
                this->_charResult = this->_intResult;
            default:
                break;
        }
    }

    bool ScalarConverter::isPseudoLiteral(std::string literalString)
    {
        if (literalString == "nan" || literalString == "nanf")
        {
            this->_type = PSEUDOLITERALNAN;
            return true;
        }
        else if (literalString == "-inff" || literalString == "+inff" 
            || literalString == "-inf" || literalString == "+inf")
        {
            this->_type = PSEUDOLITERALINF;
            return true;
        }
        return false;
    }

    void ScalarConverter::printPseudoLiteral(std::string literalString)
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;

        if (this->_type == PSEUDOLITERALNAN)
        {
            std::cout << "float: nanf" << std::endl;
            std::cout << "double: nan" << std::endl;
        }
        if (this->_type == PSEUDOLITERALINF)
        {
            std::cout << "float: " << literalString << std::endl;
            std::cout << "double: " << literalString << std::endl;
        }
    }

    int ScalarConverter::getType()const
    {
        return (this->_type);
    }