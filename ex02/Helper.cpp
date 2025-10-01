#include "Helper.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib> // srand, rand
#include <ctime> // time
#include <iostream>

Base	*generate(void)
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	int	index = std::rand() % 3;

	if (index == 0)
		return (new A());
	else if (index == 1)
		return (new B());
	else if (index == 2)
		return (new C());
	else
		return (NULL);
}


/*
	Dynamic cast
		runtime-checked cast for class hierarchies
		safely downcast / cross-cast a pointer/reference to a polymorphic type(class with at least 1 virtual function)
		Adjusts pointers correctly in multiple inheritance.

	Downcast: Base* → Derived*
		Potentially unsafe; needs a runtime check
	
	Upcast: Derived* → Base*
		Always safe; usually implicit (no cast needed)

*/


// Pointer cast: returns target pointer on success, NULL on failure (C++98)
// Reference version: use try/catch because failed dynamic_cast on references throws
// Pointer version: check for null result from dynamic_cast
void	identify(Base *p)
{
	if (p == 0)
	{
		std::cout << "NULL" << std::endl;
		return ;
	}
	if (dynamic_cast<A*>(p) != 0)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p) != 0)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p) != 0)
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

// Reference cast: succeeds, or throws std::bad_cast on failure.
void	identify(Base &p)
{
	// Check for A
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	}
	catch(const std::exception& e)
	{}

	// Check for B
	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	}
	catch(const std::exception& e)
	{}
	
	// Check for C
	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	}
	catch(const std::exception& e)
	{}

	std::cout << "Unknown Type" << std::endl;
	return ;
}
