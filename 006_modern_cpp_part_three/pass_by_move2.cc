// Example of passing an lvalue to a function
// which takes an rvalue reference
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Pass by move
// The object passed by the caller is moved into arg
void func(std::vector<std::string>&& arg)
{
	std::cout << "Argument vector has " << arg.size() << " elements" << std::endl;
}

int main()
{
	std::vector<std::string> vec(1000000);

	std::cout << "Before calling func, vector has " << vec.size() << " elements\n";
	
	// Casts vec to an rvalue
	func(std::move(vec));
	std::cout << "After calling func, vector has " << vec.size() << " elements\n";
}