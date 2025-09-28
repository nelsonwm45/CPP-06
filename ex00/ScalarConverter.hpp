#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <iostream>
#include <stdexcept> // for std::exception

# define RED "\033[31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define MAGENTA "\033[35m"
# define WHITE "\033[37m"
# define RESET "\033[0m"

# include <cctype>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib> // strtol, strtod
#include <cerrno> // errno, ERANGE
#include <climits> // INT_MIN, INT_MAX
#include <cfloat> // FLT_MAX
#include <cctype> // isprint
#include <cmath> // std::isnan, std::isinf


/*
	Non-static member function has a hidden this pointer and therefore requires an object
	Static member function has no this pointer and does not require an object
		ScalarConverter::convert();
*/
class	ScalarConverter
{
	private:
	// this class must not be instanciable by users, so hide in private
		ScalarConverter(); // Declaration Only
		~ScalarConverter(); // Declaration Only
		ScalarConverter	&operator=(const ScalarConverter &other); // Declaration Only
		ScalarConverter(const ScalarConverter &other); // Declaration Only

		// Classify
		enum LiteralType
		{
			TYPE_CHAR,
			TYPE_INT,
			TYPE_FLOAT, // with trailing 'f'
			TYPE_DOUBLE, // without trailing 'f'
			TYPE_PSEUDO_F, // nanf, +inff, -inff
			TYPE_PSEUDO_D, // nan, +inf, -inf
			TYPE_INVALID
		};
		LiteralType	classify(const std::string &literal);
		bool	isPseudoFloat(const std::string &literal);
		bool	isPseudoDouble(const std::string &literal);
		bool	isChar(const std::string &literal);
		bool	isInt(const std::string &literal);
		bool	isFloat(const std::string &literal);
		bool	isDouble(const std::string &literal);

		// Handling
		void	handlePseudoFloat(const std::string &literal);
		void	handlePseudoDouble(const std::string &literal);
		void	handleChar(const std::string &literal);
		void	handleInt(const std::string &literal);
		void	handleFloat(const std::string &literal);
		void	handleDouble(const std::string &literal);

		// Helper
		bool	isDisplayable(unsigned char c);
		int		countChar(const std::string &s, char c);
		void	printFormattedLine(const std::string &front, const std::string &back);


		

	public:
		static void	convert(const std::string &literal); 

};

std::ostream	&operator<<(std::ostream &output, const Bureaucrat &other);

#endif
