#include "Helper.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

int main()
{
	Base * p = generate();

	std::cout << "identify(Base*): ";
	identify(p);

	std::cout << "identify(Base&): ";
	identify(*p);

	delete p;
	return 0;
}
