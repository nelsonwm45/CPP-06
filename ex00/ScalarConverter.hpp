#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <iostream>
#include <iomanip>
#include <string>

#include <cstdlib>   // strtol, strtod
#include <cerrno>    // errno, ERANGE
#include <climits>   // INT_MIN, INT_MAX
#include <cfloat>    // FLT_MAX
#include <cctype>    // isprint, isdigit
#include <cmath>     // std::isnan, std::isinf

// Optional colors
# define RED "\033[31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define MAGENTA "\033[35m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

class ScalarConverter
{
	private:
		// Not instantiable
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		ScalarConverter &operator=(const ScalarConverter &other);

		// Type tag
		enum LiteralType
		{
			TYPE_CHAR,
			TYPE_INT,
			TYPE_FLOAT,     // has trailing 'f'
			TYPE_DOUBLE,    // no trailing 'f'
			TYPE_PSEUDO_F,  // nanf, +inff, -inff
			TYPE_PSEUDO_D,  // nan, +inf, -inf
			TYPE_INVALID
		};

		// Classify
		static LiteralType classify(const std::string &literal);
		static bool isPseudoFloat(const std::string &literal);
		static bool isPseudoDouble(const std::string &literal);
		static bool isChar(const std::string &literal);
		static bool isInt(const std::string &literal);
		static bool isFloat(const std::string &literal);
		static bool isDouble(const std::string &literal);

		// Handling
		static void handlePseudoFloat(const std::string &literal);
		static void handlePseudoDouble(const std::string &literal);
		static void handleChar(const std::string &literal);
		static void handleInt(const std::string &literal);
		static void handleFloat(const std::string &literal);
		static void handleDouble(const std::string &literal);
		static void handleInvalid(const std::string &literal);

		// Parser
		static bool parseIntStrict(const std::string &literal, int &out);
		static bool parseDoubleStrict(const std::string &literal, double &out);
		static bool parseFloatStrict(const std::string &literal, float &out);

		// Helper
		static bool isDisplayable(unsigned char c);
		static int  countChar(const std::string &s, char c);
		static bool isPrintableAscii(int v);

		// Printer
		static void printFormattedLine(const std::string &front, const std::string &back);
		static void printCharFromDouble(double d);
		static void printIntFromDouble(double d);
		static void printFloatFromDouble(double d);
		static void printDoubleFromDouble(double d);

	public:
		static void convert(const std::string &literal);
};

#endif
