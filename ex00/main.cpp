#include "ScalarConverter.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "This program needs at least 2 output, example: ./convert 0";
		return (-1);
	}
	ScalarConverter::convert(av[1]);
	return (0);
}