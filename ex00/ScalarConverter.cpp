#include "ScalarConverter.hpp"

// ##################################################################
//                    Constructor && Destructor                     #
// ##################################################################
  
ScalarConverter::ScalarConverter(){
    this->_type = 0;
    this->_intResult = 0;
    this->_floatResult = 0;
    this->_doubleResult = 0;
    this->_charResult = 0;
}

ScalarConverter::~ScalarConverter(){}

// ##################################################################
//		constructeur par copie et operateur d'affectation		   #
// ##################################################################

ScalarConverter::ScalarConverter(const ScalarConverter &other){
    *this = other;}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter &other)
{
    if (this != &other){}
    return *this;
}

// ##################################################################
//                           GETTERS                                #
// ##################################################################

int ScalarConverter::getType()const
{
    return (this->_type);
}

// ##################################################################
//                           SETTERS                                #
// ##################################################################


// ##################################################################
//                            Methodes                              #
// ##################################################################

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
            {
                this->_type = CHAR;
            }
        }
    }
    std::cout << "type : " << this->_type << std::endl;
}

bool ScalarConverter::isInputValid(std::string literalString)
{
    int     isDouble = 0;
    int     isFloat = 0;
    int     isAlpha = 0;
    bool    hasDecimal = false;
    bool    hasDigitAfterDecimal = false;

    for (std::string::iterator it = literalString.begin(); it != literalString.end(); ++it)
    {
        if (std::isalpha(*it))
            isAlpha++;
        if (*it == '.')
        {
            isDouble++;
            hasDecimal = true;
        }
        else if (hasDecimal && isdigit(*it))
            hasDigitAfterDecimal = true;
        if ((*it != '-') && (isDouble > 1 || isFloat > 1 || isAlpha > 1))
        {
            std::cerr << "Input is not valid." << std::endl;
            return false;
        }
        if (std::isalpha(*it) && (it + 1) == literalString.end())
            return true;
        if (*it == 'f')
        {
            isFloat++;
            if (it != literalString.end() - 1 || !hasDecimal || !hasDigitAfterDecimal)
            {
                std::cerr << "Input is not valid." << std::endl;
                return false;
            }
        }
    }
    return true;
}

void ScalarConverter::printChar()
{
    if (this->_intResult > 31 && this->_intResult < 127)
        std::cout << "char: " << static_cast<char>(this->_intResult) << std::endl;
    else
        std::cout << "char: No displayable" << std::endl;
}

void ScalarConverter::printInt()
{
    if (this->_intResult >= std::numeric_limits<int>::max() || this->_intResult <= -std::numeric_limits<int>::max())
        std::cout << "int: Out of range" << std::endl;
    else
        std::cout << "int: " << this->_intResult << std::endl;
}

void ScalarConverter::printFloat()
{
    if (this->_floatResult >= std::numeric_limits<float>::max() || this->_floatResult <= -std::numeric_limits<float>::max())
        std::cout << "float: Out of range" << std::endl;
    else {
        if (this->_floatResult == static_cast<int>(this->_floatResult))
            std::cout << "float: " << this->_floatResult << ".0f" << std::endl;
        else
            std::cout << "float: " << this->_floatResult << "f" << std::endl;
    }
}

void ScalarConverter::printDouble()
{
    if (this->_doubleResult >= std::numeric_limits<double>::max() || this->_doubleResult <= -std::numeric_limits<double>::max())
        std::cout << "double: Out of range" << std::endl;
    else {
        if (this->_doubleResult == static_cast<int>(this->_doubleResult))
            std::cout << "double: " << this->_doubleResult << ".0" << std::endl;
        else
            std::cout << "double: " << this->_doubleResult << std::endl;
    }
}

void ScalarConverter::printOutput(std::string literalString)
{
    if (isPseudoLiteral(literalString))
    {
        printPseudoLiteral(literalString);
    }
    else
    {
        printChar();
        printInt();
        printFloat();
        printDouble();
    }
}

void ScalarConverter::convertFromStringToType(std::string literalString)
{
    const char *str = literalString.c_str();

    switch(this->_type)
    {
        case(INT):
            this->_intResult = std::atol(str);
            break;
        case(FLOAT):
            this->_floatResult =  std::atof(str);
            break;
        case(DOUBLE):
            this->_doubleResult =  std::strtod(str, NULL);
            break;
        case(CHAR):
            this->_intResult = str[0];
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
            this->_charResult = static_cast<char>(this->_intResult);
            this->_doubleResult =  static_cast<double>(this->_intResult);
            break;
        case(FLOAT):
            this->_intResult = static_cast<long>(this->_floatResult);
            this->_doubleResult = static_cast<double>(this->_floatResult);
            this->_charResult = static_cast<char>(this->_intResult);
            break;
        case(DOUBLE):
            this->_intResult =  static_cast<long>(this->_doubleResult);
            this->_floatResult = static_cast<float>(this->_doubleResult);
            this->_charResult = static_cast<char>(this->_intResult);
            break;
        case(CHAR):
            this->_floatResult = static_cast<float>(this->_intResult);
            this->_doubleResult = static_cast<double>(this->_intResult);
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