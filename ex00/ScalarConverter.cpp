#include "ScalarConverter.hpp"

// =============================================================================
// CLASSIFY
// =============================================================================

bool ScalarConverter::isPseudoFloat(const std::string &literal)
{
	if (literal == "nanf")
	{
		return (true);
	}
	if (literal == "+inff")
	{
		return (true);
	}
	if (literal == "-inff")
	{
		return (true);
	}
	return (false);
}

bool ScalarConverter::isPseudoDouble(const std::string &literal)
{
	if (literal == "nan")
	{
		return (true);
	}
	if (literal == "+inf")
	{
		return (true);
	}
	if (literal == "-inf")
	{
		return (true);
	}
	return (false);
}

// single printable non-digit character
bool ScalarConverter::isChar(const std::string &literal)
{
	if (literal.size() != 1)
	{
		return (false);
	}
	unsigned char c = static_cast<unsigned char>(literal[0]);

	if (std::isprint(c) == 0)
	{
		return (false);
	}
	if (std::isdigit(c) != 0)
	{
		return (false);
	}
	return (true);
}

bool ScalarConverter::isInt(const std::string &literal)
{
	if (literal.empty())
	{
		return (false);
	}
	size_t i = 0;

	if (literal[i] == '+' || literal[i] == '-')
	{
		i++;
	}
	if (i >= literal.size())
	{
		return (false);
	}
	while (i < literal.size())
	{
		unsigned char c = static_cast<unsigned char>(literal[i]);
		if (std::isdigit(c) == 0)
		{
			return (false);
		}
		i++;
	}
	return (true);
}

// float: optional sign, digits + one '.', ending with 'f'
bool ScalarConverter::isFloat(const std::string &literal)
{
	if (literal.size() < 2)
	{
		return (false);
	}
	if (literal[literal.size() - 1] != 'f')
	{
		return (false);
	}

	std::string core = literal.substr(0, literal.size() - 1);

	if (core.empty())
	{
		return (false);
	}

	size_t i = 0;
	if (core[i] == '+' || core[i] == '-')
	{
		i++;
	}
	if (i >= core.size())
	{
		return (false);
	}

	int dots = 0;
	bool hasDigit = false;

	while (i < core.size())
	{
		unsigned char ch = static_cast<unsigned char>(core[i]);

		if (ch == '.')
		{
			dots++;
			i++;
			continue;
		}
		if (std::isdigit(ch) != 0)
		{
			hasDigit = true;
			i++;
			continue;
		}
		return (false);
	}

	if (dots != 1)
	{
		return (false);
	}
	if (hasDigit == false)
	{
		return (false);
	}
	return (true);
}

// double: optional sign, digits + one '.', no trailing 'f'
bool ScalarConverter::isDouble(const std::string &literal)
{
	if (literal.empty())
	{
		return (false);
	}

	if (literal[literal.size() - 1] == 'f')
	{
		return (false);
	}

	size_t i = 0;
	if (literal[i] == '+' || literal[i] == '-')
	{
		i++;
	}
	if (i >= literal.size())
	{
		return (false);
	}

	int dots = 0;
	bool hasDigit = false;

	while (i < literal.size())
	{
		unsigned char ch = static_cast<unsigned char>(literal[i]);

		if (ch == '.')
		{
			dots++;
			i++;
			continue;
		}
		if (std::isdigit(ch) != 0)
		{
			hasDigit = true;
			i++;
			continue;
		}
		return (false);
	}

	if (dots != 1)
	{
		return (false);
	}
	if (hasDigit == false)
	{
		return (false);
	}
	return (true);
}

ScalarConverter::LiteralType ScalarConverter::classify(const std::string &literal)
{
	if (isPseudoFloat(literal) == true)
	{
		return (TYPE_PSEUDO_F);
	}
	if (isPseudoDouble(literal) == true)
	{
		return (TYPE_PSEUDO_D);
	}
	if (isChar(literal) == true)
	{
		return (TYPE_CHAR);
	}
	if (isInt(literal) == true)
	{
		return (TYPE_INT);
	}
	if (isFloat(literal) == true)
	{
		return (TYPE_FLOAT);
	}
	if (isDouble(literal) == true)
	{
		return (TYPE_DOUBLE);
	}
	return (TYPE_INVALID);
}

// =============================================================================
// HANDLING
// =============================================================================

void ScalarConverter::handlePseudoFloat(const std::string &literal)
{
	printFormattedLine("char", "impossible");
	printFormattedLine("int", "impossible");
	printFormattedLine("float", literal);

	if (literal == "nanf")
	{
		printFormattedLine("double", "nan");
		return;
	}
	if (literal == "+inff")
	{
		printFormattedLine("double", "+inf");
		return;
	}
	printFormattedLine("double", "-inf");
	return;
}

void ScalarConverter::handlePseudoDouble(const std::string &literal)
{
	printFormattedLine("char", "impossible");
	printFormattedLine("int", "impossible");

	if (literal == "nan")
	{
		printFormattedLine("float", "nanf");
		printFormattedLine("double", "nan");
		return;
	}
	if (literal == "+inf")
	{
		printFormattedLine("float", "+inff");
		printFormattedLine("double", "+inf");
		return;
	}
	if (literal == "-inf")
	{
		printFormattedLine("float", "-inff");
		printFormattedLine("double", "-inf");
		return;
	}
	// Fallback (should not reach)
	printFormattedLine("float", "impossible");
	printFormattedLine("double", literal);
	return;
}

void ScalarConverter::handleChar(const std::string &literal)
{
	char c = literal[0];

	std::cout << "char: '" << c << "'" << std::endl;

	int iv = static_cast<int>(static_cast<unsigned char>(c));
	std::cout << "int: " << iv << std::endl;

	std::cout.setf(std::ios::fixed);
	std::cout << std::setprecision(1);

	std::cout << "float: " << static_cast<float>(iv) << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(iv) << std::endl;
	return;
}

void ScalarConverter::handleInt(const std::string &literal)
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

void ScalarConverter::handleFloat(const std::string &literal)
{
	// strip trailing 'f', then parse
	std::string core = literal.substr(0, literal.size() - 1);

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

void ScalarConverter::handleDouble(const std::string &literal)
{
	double d = 0.0;
	bool ok = parseDoubleStrict(literal, d);

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

void ScalarConverter::handleInvalid(const std::string &literal)
{
	(void)literal;
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
	return;
}

// =============================================================================
// CONVERT
// =============================================================================

void ScalarConverter::convert(const std::string &literal)
{
	LiteralType type = classify(literal);

	if (type == TYPE_PSEUDO_F)
	{
		handlePseudoFloat(literal);
		return;
	}
	if (type == TYPE_PSEUDO_D)
	{
		handlePseudoDouble(literal);
		return;
	}
	if (type == TYPE_CHAR)
	{
		handleChar(literal);
		return;
	}
	if (type == TYPE_INT)
	{
		handleInt(literal);
		return;
	}
	if (type == TYPE_FLOAT)
	{
		handleFloat(literal);
		return;
	}
	if (type == TYPE_DOUBLE)
	{
		handleDouble(literal);
		return;
	}
	handleInvalid(literal);
	return;
}

// =============================================================================
// PARSER
// =============================================================================

bool ScalarConverter::parseIntStrict(const std::string &literal, int &out)
{
	char *end = 0;
	errno = 0;

	long v = std::strtol(literal.c_str(), &end, 10);

	if (end == literal.c_str())
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

bool ScalarConverter::parseDoubleStrict(const std::string &literal, double &out)
{
	char *end = 0;
	errno = 0;

	double v = std::strtod(literal.c_str(), &end);

	if (end == literal.c_str())
		return (false);
	if (*end != '\0')
		return (false);
	if (errno == ERANGE)
		return (false);
	out = v;
	return (true);
}

bool ScalarConverter::parseFloatStrict(const std::string &literal, float &out)
{
	double d = 0.0;
	bool ok = parseDoubleStrict(literal, d);

	if (ok == false)
		return (false);
	if (std::isinf(d) != 0 || std::isnan(d) != 0)
	{
		out = static_cast<float>(d);
		return (true);
	}
	if (d < -FLT_MAX || d > FLT_MAX)
	{
		return (false);
	}
	out = static_cast<float>(d);
	return (true);
}

// =============================================================================
// HELPER
// =============================================================================

bool ScalarConverter::isDisplayable(unsigned char c)
{
	int isDisp = std::isprint(c);

	if (isDisp != 0)
		return (true);
	else
		return (false);
}

int ScalarConverter::countChar(const std::string &s, char c)
{
	int count = 0;
	size_t i = 0;

	while (i < s.size())
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

bool ScalarConverter::isPrintableAscii(int v)
{
	if (v >= 32 && v <= 126)
		return (true);
	return (false);
}

// =============================================================================
// PRINTERS
// =============================================================================

void ScalarConverter::printFormattedLine(const std::string &front, const std::string &back)
{
	std::cout << front << ": " << back << std::endl;
}

void ScalarConverter::printCharFromDouble(double d)
{
	std::cout << "char: ";

	if (std::isnan(d) != 0 || std::isinf(d) != 0)
	{
		std::cout << "impossible" << std::endl;
		return;
	}
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
	return;
}

void ScalarConverter::printFloatFromDouble(double d)
{
	if (std::isnan(d) != 0)
	{
		std::cout << "float: nanf" << std::endl;
		return;
	}
	if (std::isinf(d) != 0)
	{
		if (d > 0.0)
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

void ScalarConverter::printDoubleFromDouble(double d)
{
	if (std::isnan(d) != 0)
	{
		std::cout << "double: nan" << std::endl;
		return;
	}
	if (std::isinf(d) != 0)
	{
		if (d > 0.0)
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
	return;
}
