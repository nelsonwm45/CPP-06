#include "ScalarConverter.hpp"

// =============================================================================
// CONSTRUCTOR && DESTRUCTOR
// -----------------------------------------------------------------------------

// ScalarConverter::ScalarConverter() {};

// ScalarConverter::ScalarConverter(const ScalarConverter &other)
// {
// 	(void)other;
// }

// ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
// {
// 	(void)other;
// 	return (*this);
// }

// ScalarConverter::~ScalarConverter() {};

// =============================================================================
// CLASSIFY
// -----------------------------------------------------------------------------

// Check Pseudo Float: nanf, +inff, -inff
bool	ScalarConverter::isPseudoFloat(const std::string &literal)
{
	if (literal == "nanf")
		return (true);
	if (literal == "+inff")
		return (true);
	if (literal == "-inff")
		return (true);
	return (false);
}

// Check Pseudo Double: nan, +inf, -inf
bool	ScalarConverter::isPseudoDouble(const std::string &literal)
{
	if (literal == "nan")
		return (true);
	if (literal == "+inf")
		return (true);
	if (literal == "-inf")
		return (true);
	return (false);
}

// Check Char : single , printable, non-digit
// std::isprint returns non-zero if the character is printable (including space)
// std::digit returns zero if the character not digit
bool	ScalarConverter::isChar(const std::string &literal)
{
	if (literal.size() != 1)
		return (false);
	unsigned char	c = static_cast<unsigned cast>(literal[0]);
	if (std::isprint(c) == 0)
		return (false);
	if (std::isdigit(c) != 0) // if return more than zero means, it's digits
		return (false);
	return (true);
}

// Check Int : All Digits, with optional signs
bool	ScalarConverter::isInt(const std::string &literal)
{
	if (literal.empty())
		return (false);
	size_t	i = 0;
	if (literal[i] == '+' || literal[i] == '-')
		i++;
	if (i >= literal.size()) // means it only contains "sign"
		return (false);
	while (i < literal.size())
	{
		unsigned char c = static_cast<int>(literal[i]);
		if (std::isdigit(c) == 0) // 0 means non-digits
			return (false);
		i++;
	}
	return (true);

}

// Check Float form: must have 2 char (2f), exactly one dot and trailing 'f'
bool	ScalarConverter::isFloat(const std::string &literal)
{
	if (literal.empty())
		return (false);
	if (literal.size() < 2)
		return (false);
	char	trailing_f = literal[literal.size() - 1];
	if (trailing_f != 'f')
		return (false);
	if (countchar(literal, '.') != 1)
		return (false);
}

// Check Double form: has ONE dot and NO trailing 'f'
bool	ScalarConverter::isDouble(const std::string &literal)
{
	if (literal.empty())
		return (false);
	if (countChar(literal, '.') != 1)
		return (false);
	char	trailing_f = literal[literal.size() - 1];
	if (trailing_f == 'f')
		return (false);
}

LiteralType	ScalarConverter::classify(const std::string &literal)
{
	// Check Pseudo Float: nanf, +inff, -inff
	if (isPseudoFloat(literal) == true)
		return (TYPE_PSEUDO_F);
	// Check Pseudo Double: nan, +inf, -inf
	if (isPseudoDouble(literal) == true)
		return (TYPE_PSEUDO_D);
	// Check Char : single , printable, non-digit
	if (isChar(literal) == true)
		return (TYPE_CHAR);
	// Check Int : All Digits, with optional signs
	if (isInt(literal) == true)
		return (TYPE_INT);
	// Check Float form: exactly one dot and ONE trailing 'f'
	if (isFloat(literal) == true)
		return (TYPE_FLOAT);
	// Check Double form: has ONE dot and NO trailing 'f'
	if (isDouble(literal) == true)
		return (TYPE_DOUBLE);
	return (TYPE_INVALID);
}

// =============================================================================
// HANDLING
// -----------------------------------------------------------------------------

// Pseudo float input (nanf, +inff, -inff)
void	ScalarConverter::handlePseudoFloat(const std::string &literal)
{
	printFormattedLine("char", "impossible");
	printFormattedLine("int", "impossible");
	printFormattedLine("float", literal);
	if (literal == "nanf")
	{
		printFormattedLine("double", "nan")
		return 
	}
	if (literal == "+inff")
	{
		printFormattedLine("double", "+inf")
		return 
	}
	printFormattedLine("double", "-inf")
	return;
}

void	ScalarConverter::handlePseudoDouble(const std::string &literal)
{
	printFormattedLine("char", "impossible");
	printFormattedLine("int", "impossible");
	if (literal == "nan")
	{
		printFormattedLine("double", "nanf")
		return 
	}
	if (literal == "+inf")
	{
		printFormattedLine("double", "+inff")
		return 
	}
	if (literal == "-inf")
	{
		printFormattedLine("double", "-inff")
		return 
	}
	printFormattedLine("double", literal);
	return ;
}

/*
	std::cout.setf(std::ios::fixed)
		Sets the floatfield of cout to fixed notation.
		It affects how all floating-point values (float, double, long double) are printed on this stream.
	
	std::cout << std::setprecision(1)
		Sets cout’s precision to 1.
		With fixed active, that means 1 digit after the decimal point (e.g., 3.1).
		Without fixed/scientific, precision means total significant digits.
*/
void	ScalarConverter::handleChar(const std::string &literal)
{
	char c = literal[0];

	// char
	std::cout << "char: '" << c << "'" << std::endl;

	// int
	int iv = static_cast<int>(static_cast<unsigned char>(c));
	std::cout << "int: " << iv << std::endl;

	// float / double with one decimal
	std::cout.setf(std::ios::fixed); // Sets the floatfield of cout to fixed notation
	std::cout << std::setprecision(1); // With fixed active, the precision is set to 1

	std::cout << "float: " << static_cast<float>(iv) << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(iv) << std::endl;

	return;
}

void	ScalarConverter::handleInt(const std::string &literal)
{
	int iv = 0;
	bool ok = parseIntStrict(literal, iv);

	if (ok == false)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	double d = static_cast<double>(iv);

	printCharFromDouble(d);
	printIntFromDouble(d);
	printFloatFromDouble(d);
	printDoubleFromDouble(d);
	return;
}

void	ScalarConverter::handleFloat(const std::string &literal)
{
	// s has trailing 'f'. Strip it, then parse as double.
	std::string core = s.substr(0, s.size() - 1);

	double d = 0.0;
	bool ok = parseDoubleStrict(core, d);

	if (ok == false)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	printCharFromDouble(d);
	printIntFromDouble(d);
	printFloatFromDouble(d);
	printDoubleFromDouble(d);
	return;
}

void	ScalarConverter::handleDouble(const std::string &literal)
{
	double d = 0.0;
	bool ok = parseDoubleStrict(s, d);
	if (ok == false)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	printCharFromDouble(d);
	printIntFromDouble(d);
	printFloatFromDouble(d);
	printDoubleFromDouble(d);
	return;
}

// =============================================================================
// CONVERT
// -----------------------------------------------------------------------------
static void	ScalarConverter::convert(const std::string &literal)
{
	LiteralType	type = classify(literal);
	if (type == TYPE_PSEUDO_F)
		handlePseudoFloat(literal);
	if (type == TYPE_PSEUDO_D)
		handlePseudoDouble(literal);
	if (type == TYPE_CHAR)
		handleChar(literal);
	if (type == TYPE_INT)
		handleInt(literal);
	if (type == TYPE_FLOAT)
		handleFloat(literal);
	if (type == TYPE_DOUBLE);
		handleDouble(literal);
	handleInvalid(literal);
}

// =============================================================================
// PARSER
// -----------------------------------------------------------------------------

/*
	str to long
	long strtol(const char* nptr, char** endptr, int base)
		in <cstdlib>
		nptr: C-string to parse (may start with whitespace).
		endptr:
			If non-NULL, set to point at the first char after the parsed number.
			If no conversion happens, endptr == nptr.
		base:
			0 → auto-detect: 0x/0X → hex, leading 0 → octal, else decimal.
			2 … 36 → explicit base.
			Digits beyond 9 use letters a…z/A…Z = 10…35.
	
	Behaviour
		Skips leading whitespace, accepts optional +/-.
		Parses as many valid digits as possible in the given base.
		Stops at first invalid char and sets *endptr there (if provided).
		No exceptions; uses errno for range errors.
	
	Return & errors
		Returns the converted long.
		On overflow/underflow:
		Sets errno = ERANGE, returns LONG_MAX / LONG_MIN.
		If no digits: endptr == nptr; return value is 0 (no error in errno).

*/
bool	ScalarConverter::parseIntStrict(const std::string &s, int &out)
{
	char *end = 0;
	errno = 0;

	long v = std::strtol(s.c_str(), &end, 10);
	if (end == s.c_str())
		return (false);
	if (*end != '\0')
		return (false);
	if (errno == ERANGE)
		return (false);
	if (v < INT_MIN || v > INT_MAX)
		return (false);
	out = static_cast<int>(v);
	return (true);
}

/*
	str to double
	double strtod(const char* nptr, char** endptr)
		nptr: C-string to parse (may start with whitespace).
		endptr:
			If non-NULL, set to the first character after the parsed number.
			If no conversion occurs, *endptr == nptr.
	Returns the converted double.
		If no digits were parsed: returns 0.0 and endptr == nptr.
	Overflow: sets errno = ERANGE, returns HUGE_VAL (with sign).
	Underflow: sets errno = ERANGE, returns a value with magnitude very close to 0 (often subnormal, possibly 0.0).

*/
bool	ScalarConverter::parseDoubleStrict(const std::string &s, double &out)
{
	char *end = 0;
	errno = 0;

	double v = std::strtod(s.c_str(), &end);
	if (end == s.c_str())
		return (false);
	if (*end != '\0')
		return (false);
	if (errno == ERANGE)
		return (false);
	out = v;
	return (true);
}

bool	ScalarConverter::parseFloatStrict(const std::string &s, float &out)
{
	// parse as double first, then narrow to float with range checks.
	double d = 0.0;
	bool ok = parseDoubleStrict(s, d);

	if (ok == false)
		return (false);
	if (std::isinf(d) != 0 || std::isnan(d) != 0)
	{
		out = static_cast<float>(d);
		return (true);
	}
	if (d < -FLT_MAX || d > FLT_MAX)
		return (false);
	out = static_cast<float>(d);
	return (true);
}

// =============================================================================
// HELPER
// -----------------------------------------------------------------------------


// Cast to unsigned char to avoid UB when char is signed and negative
// Space considered printable
bool	ScalarConverter::isDisplayable(unsigned char c)
{
	int	isDisplayable = std::isprint(c);

	if (isDisplayable != 0)
		return (true);
	else
		return (false);
}

// count the number of characters
int	ScalarConverter::countChar(const std::string &s, char c)
{
	int	count = 0;
	size_t	i = 0;
	
	while (i < s.size())
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}


bool	ScalarConverter::isPrintableAscii(int v)
{
	if (v >= 32 && v <= 126)
	{
		return (true);
	}
	return (false);
}

void	ScalarConverter::printFormattedLine(const std::string &front, const std::string &back)
{
	std::cout << front
				<< ": "
				<< back
				<< std::endl;
}

/*
	std::isnan() return non-zero if it is nan
	std::isinf() return non-zero if it is inf
*/
void ScalarConverter::printCharFromDouble(double d)
{
	std::cout << "char: ";

	if (std::isnan(d) != 0 || std::isinf(d) != 0)
	{
		std::cout << "impossible" << std::endl;
		return;
	}
	// ascii number only has 0 - 127
	if (d < 0.0 || d > 127.0)
	{
		std::cout << "impossible" << std::endl;
		return;
	}
	char c = static_cast<char>(d);
	if (isPrintableAscii(static_cast<unsigned char>(c)) == true)
	{
		std::cout << "'" << c << "'" << std::endl;
		return;
	}
	else
	{
		std::cout << "Non displayable" << std::endl;
		return;
	}
}

void ScalarConverter::printIntFromDouble(double d)
{
	std::cout << "int: ";

	if (std::isnan(d) != 0 || std::isinf(d) != 0)
	{
		std::cout << "impossible" << std::endl;
		return;
	}
	if (d < static_cast<double>(INT_MIN) || d > static_cast<double>(INT_MAX))
	{
		std::cout << "impossible" << std::endl;
		return;
	}
	int v = static_cast<int>(d);
	std::cout << v << std::endl;
	return ;
}

void	ScalarConverter::printFloatFromDouble(double d)
{
	if (std::isnan(d) != 0) // is nan
	{
		std::cout << "float: nanf" << std::endl;
		return;
	}
	if (std::isinf(d) != 0) // is inf
	{
		if (d > 0)
		{
			std::cout << "float: +inff" << std::endl;
			return;
		}
		else
		{
			std::cout << "float: -inff" << std::endl;
			return;
		}
	}
	float f = static_cast<float>(d);
	std::cout.setf(std::ios::fixed);
	std::cout << std::setprecision(1);
	std::cout << "float: " << f << "f" << std::endl;
	return;
}

void	ScalarConverter::printDoubleFromDouble(double d)
{
	if (std::isnan(d) != 0)
	{
		std::cout << "double: nan" << std::endl;
		return;
	}
	if (std::isinf(d) != 0)
	{
		if (d > 0)
		{
			std::cout << "double: +inf" << std::endl;
			return;
		}
		else
		{
			std::cout << "double: -inf" << std::endl;
			return;
		}
	}
	std::cout.setf(std::ios::fixed);
	std::cout << std::setprecision(1);
	std::cout << "double: " << d << std::endl;
	return ;
}
