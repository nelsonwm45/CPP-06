#include "Serializer.hpp"
#include "Data.hpp"

/*
	Reinterpret_cast(raw bit/pointer reinterpretation)
		allows you to convert any pointer type to any other pointer type
			(Dangerous and doesn't perform safety check)
			avoid for class hierarchies
		no runtime checks and almost no compile-time safety
		does not change the underlying bytes in a meaningful way
		only changes how those bytes are interpreted.

	uniptr_t -> size is big enough to store a pointer without data loss
	
	serialize() -> stores the pointer value (the address) into an integer.
	unserialize() -> turns that integer back into the same pointer.
*/
int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	Data	data1;
	data1.name = "Michael";
	data1.num = 68;

	uintptr_t	raw1;
	raw1 = Serializer::serialize(&data1);

	std::cout << "\n=================================================\n";
	std::cout << BLUE << "Deserializing raw1 into data1" << RESET << std::endl;
	Data *data_ptr = Serializer::deserialize(raw1);
	if (data_ptr)
	{
		std::cout << "Original (Address)        : " << &data1 << std::endl;
		std::cout << "Reinterpret Cast (Address): " << data_ptr << std::endl;
		std::cout << "Original (Name)           : " << data1.name << std::endl;
		std::cout << "Reinterpret Cast (Name)   : " << data_ptr->name << std::endl;
		std::cout << "Original (Num)            : " << data1.num << std::endl;
		std::cout << "Reinterpret Cast (Num)    : " << data_ptr->num << std::endl;
		std::cout << "Successfully Reinterpret Cast!\n";
	}
	else
		std::cout << "Failed\n";
}

// #include <iostream>
// #include <iomanip>   // std::hex, std::setw, std::setfill
// #include <stdint.h>  // uintptr_t in C++98 (or <cstdint> in C++11+)
// #include "Serializer.hpp"
// #include "Data.hpp"

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;

// 	Data data1;
// 	data1.name = "Michael";
// 	data1.num  = 68;

// 	std::cout << "=================================================\n";
// 	std::cout << "Original pointer: " << static_cast<const void*>(&data1) << "\n";

// 	// Serialize (pointer -> integer)
// 	uintptr_t raw1 = Serializer::serialize(&data1);

// 	std::cout << "Serialized (uintptr_t value): 0x"
// 			<< std::hex << std::setw(sizeof(uintptr_t)*2) << std::setfill('0') << raw1
// 			<< std::dec << "\n";
// 	// Show the same bits viewed as a pointer (without “deserializing” function)
// 	std::cout << "Serialized as pointer again: "
// 			<< reinterpret_cast<void*>(raw1) << "\n";

// 	std::cout << "\n=================================================\n";
// 	std::cout << "Deserializing back...\n";

// 	Data* data_ptr = Serializer::deserialize(raw1);

// 	std::cout << "Deserialized pointer: " << static_cast<const void*>(data_ptr) << "\n";
// 	if (data_ptr)
// 	{
// 		std::cout << "Name: " << data_ptr->name << "\n";
// 		std::cout << "Num : " << data_ptr->num  << "\n";
// 	}
// 	else
// 		std::cout << "Failed to deserialize\n";

// 	std::cout << "=================================================\n";
// 	return (0);
// }
