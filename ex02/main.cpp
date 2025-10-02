#include "Helper.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

int main()
{
	Base *p = generate();

	std::cout << "identify(Base*): ";
	identify(p);

	std::cout << "identify(Base&): ";
	identify(*p);

	delete p;
	return 0;
}


// #include "Helper.hpp"
// #include "A.hpp"
// #include "B.hpp"
// #include "C.hpp"
// #include <iostream>
// #include <cstdlib>  // std::rand, std::srand
// #include <ctime>    // std::time

// int main( void )
// {
// 	// Seed randomness (deterministic enough for repeated runs)
// 	std::srand( static_cast<unsigned int>( std::time( 0 ) ) );

// 	// -------------------------------------------------------------------------
// 	// Case 1: NULL pointer for identify(Base*)
// 	// -------------------------------------------------------------------------
// 	std::cout << "[Case 1] identify(Base* = NULL): ";
// 	Base * nullPtr = 0;
// 	identify( nullPtr );            // should handle NULL gracefully
// 	std::cout << std::endl;

// 	// -------------------------------------------------------------------------
// 	// Case 2: Explicit objects A, B, C via pointer
// 	// -------------------------------------------------------------------------
// 	std::cout << "[Case 2] Explicit objects (pointer):" << std::endl;
// 	A a;
// 	B b;
// 	C c;

// 	std::cout << "  A* -> ";
// 	identify( &a );
// 	std::cout << "  B* -> ";
// 	identify( &b );
// 	std::cout << "  C* -> ";
// 	identify( &c );
// 	std::cout << std::endl;

// 	// -------------------------------------------------------------------------
// 	// Case 3: Explicit objects A, B, C via reference
// 	// -------------------------------------------------------------------------
// 	std::cout << "[Case 3] Explicit objects (reference):" << std::endl;
// 	std::cout << "  A& -> ";
// 	identify( a );
// 	std::cout << "  B& -> ";
// 	identify( b );
// 	std::cout << "  C& -> ";
// 	identify( c );
// 	std::cout << std::endl;

// 	// -------------------------------------------------------------------------
// 	// Case 4: Random generation several times; test both pointer and reference
// 	//         Also track that we’ve actually seen each real type at least once.
// 	// -------------------------------------------------------------------------
// 	std::cout << "[Case 4] Random generate 12 times (pointer + reference):" << std::endl;

// 	bool seenA = false;
// 	bool seenB = false;
// 	bool seenC = false;

// 	int i = 0;
// 	while ( i < 12 )
// 	{
// 		Base * p = generate();

// 		std::cout << "  Iter " << ( i + 1 ) << " pointer   -> ";
// 		identify( p );

// 		std::cout << "  Iter " << ( i + 1 ) << " reference -> ";
// 		identify( *p );

// 		// Track which concrete type we got (allowed here; only <typeinfo> is forbidden)
// 		if ( dynamic_cast< A * >( p ) != 0 )
// 		{
// 			seenA = true;
// 		}
// 		else if ( dynamic_cast< B * >( p ) != 0 )
// 		{
// 			seenB = true;
// 		}
// 		else if ( dynamic_cast< C * >( p ) != 0 )
// 		{
// 			seenC = true;
// 		}

// 		delete p;
// 		i = i + 1;
// 	}

// 	std::cout << std::endl;
// 	std::cout << "[Summary] Seen types -> ";
// 	if ( seenA )
// 	{
// 		std::cout << "A: yes  ";
// 	}
// 	else
// 	{
// 		std::cout << "A: no   ";
// 	}
// 	if ( seenB )
// 	{
// 		std::cout << "B: yes  ";
// 	}
// 	else
// 	{
// 		std::cout << "B: no   ";
// 	}
// 	if ( seenC )
// 	{
// 		std::cout << "C: yes";
// 	}
// 	else
// 	{
// 		std::cout << "C: no";
// 	}
// 	std::cout << std::endl << std::endl;

// 	// -------------------------------------------------------------------------
// 	// Case 5: Deletion through Base* (checks that Base has a virtual destructor)
// 	// -------------------------------------------------------------------------
// 	std::cout << "[Case 5] Delete through Base*: ";
// 	Base * poly = new A();
// 	delete poly;
// 	std::cout << "ok" << std::endl;

// 	return 0;
// }
