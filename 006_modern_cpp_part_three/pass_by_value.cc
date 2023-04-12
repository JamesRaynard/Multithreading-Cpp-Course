// Program which passes a large object by value
#include <iostream>
#include <vector>
#include <string>

// Pass by value
// arg will be a copy of the object passed by the caller
void func(std::vector<std::string> arg)
{
	std::cout << "Argument vector has " << arg.size() << " elements" << std::endl;
}

int main()
{
	std::vector<std::string> vec(1000000);
	
	std::cout << "Before calling func, vector has " << vec.size() << " elements\n";
	func(vec);
	std::cout << "After calling func, vector has " << vec.size() << " elements\n";
}